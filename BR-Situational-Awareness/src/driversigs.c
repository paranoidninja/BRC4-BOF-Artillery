#include "common.h"

#ifndef OBJ_CASE_INSENSITIVE
#define OBJ_CASE_INSENSITIVE                0x00000040L
#endif

DWORD intstrlen(const char * s, BOOL u) {
    DWORD i = 0;
    if(u)
    {
    while(s[i] || s[i+1])
    {
        i++;
    }
    return i + i%2;
    }
    else 
    while(s[i])
    {
        i++;
    }
    return i;
}

void makestr(PUNICODE_STRING ustr, const wchar_t * string)
{

    ustr->Buffer = (wchar_t *)string;
    ustr->Length = (USHORT)intstrlen((const char *)string, TRUE);
    ustr->MaximumLength = ustr->Length + 2;
}

BOOL validate_driver(wchar_t * file_path) {
	BOOL success = FALSE;
	NTSTATUS status = ERROR_SUCCESS;
	wchar_t mypath[512] = {0};
	wchar_t *  drivers[8]; // make sure you update this if you change the list below
	PCCERT_CONTEXT certificate_context = NULL;
	LPWIN_CERTIFICATE certificate = NULL;
	LPWIN_CERTIFICATE certificate_header = NULL;
	HANDLE file_handle = 0;
	UNICODE_STRING file_path_us = { 0 };
	OBJECT_ATTRIBUTES object_attributes = { 0 };
	IO_STATUS_BLOCK io_status_block = { 0 };
	unsigned long certificate_count = 0;
	unsigned long certificate_length = 0;
	CRYPT_VERIFY_MESSAGE_PARA verify_params = { 0 };
	wchar_t certificate_name[MAX_PATH] = { 0 };
	
	drivers[0] = L"Carbon Black, Inc.";
	drivers[1] = L"CrowdStrike, Inc.";
	drivers[2] = L"Cylance, Inc.";
	drivers[3] = L"FireEye, Inc.";
	drivers[4] = L"McAfee, Inc.";
	drivers[5] = L"Sentinel Labs, Inc.";
	drivers[6] = L"Symantec Corporation";
	drivers[7] = L"Tanium Inc."; 
	// drivers[8] = L"Vmware, Inc.";

	if (file_path == NULL || *file_path == 0)
	{
		EPRINT("[-] Invalid file_path\n");
		return ERROR_BAD_ARGUMENTS;
	}

	if((*file_path) != '\\')
	{
		wcscat(mypath, L"\\SystemRoot\\");
		wcscat(mypath, file_path);
	}
	else{
		wcscat(mypath, file_path);
	}


	makestr(&file_path_us, mypath);
	
	object_attributes.Length = sizeof(OBJECT_ATTRIBUTES);
	object_attributes.RootDirectory = NULL;
	object_attributes.ObjectName = &file_path_us;
	object_attributes.Attributes = OBJ_CASE_INSENSITIVE;
	object_attributes.SecurityDescriptor = NULL;
	object_attributes.SecurityQualityOfService = NULL;

	status = NtCreateFile(&file_handle, GENERIC_READ, &object_attributes, &io_status_block, NULL, FILE_ATTRIBUTE_NORMAL, FILE_SHARE_READ, FILE_OPEN, FILE_NON_DIRECTORY_FILE, NULL, 0);
	if (!NT_SUCCESS(status)) {
		NTEPRINT("NtCreateFile", status);
		return FALSE;
	}

	do {
		if (!file_handle) {
			EPRINT("[-] %S -> cannot obtain handle (insufficient privs?)\n", mypath);
			status = ERROR_INVALID_HANDLE;
			break;
		}
		
		// Count certificates in file.
		if(!ImageEnumerateCertificates(file_handle, CERT_SECTION_TYPE_ANY, &certificate_count, NULL, 0)) {
			ERR_PRINT("ImageEnumerateCertificates");
			status = (NTSTATUS)-1;
			break;
		}

		for (unsigned long i = 0; i < certificate_count; i++) {
			// Determine the length for the ImageGetCertificateData call.
			certificate_header = (LPWIN_CERTIFICATE)intAlloc(sizeof(WIN_CERTIFICATE));

			if (NULL == certificate_header) {
				INTALLOC_E;
				goto clear;
        	}

			if(!ImageGetCertificateHeader(file_handle, i, certificate_header)) { 		
				EPRINT("ImageGetCertificateHeader");
				goto clear;
			}

			// Get the buffer for the certificate.
			certificate_length = certificate_header->dwLength;
			certificate = (LPWIN_CERTIFICATE)intAlloc(certificate_length);
	        if (NULL == certificate) {
				INTALLOC_E;
				goto clear;
	        }

			if(!ImageGetCertificateData(file_handle, i, certificate, &certificate_length)) { 		
				EPRINT("ImageGetCertificateData");
				goto clear;
			}

			verify_params.cbSize = sizeof(CRYPT_VERIFY_MESSAGE_PARA);
			verify_params.dwMsgAndCertEncodingType = X509_ASN_ENCODING | PKCS_7_ASN_ENCODING;

			if(!CryptVerifyMessageSignature(&verify_params, i, certificate->bCertificate, certificate->dwLength, NULL, NULL, &certificate_context)) { 		
				EPRINT("CryptVerifyMessageSignature");
				goto clear;
			}

			// Get the name string for the certificate.
			CertGetNameStringW(certificate_context, CERT_NAME_SIMPLE_DISPLAY_TYPE, 0, NULL, (LPWSTR)&certificate_name, MAX_PATH);
			for(unsigned int j = 0; j < (sizeof(drivers) / sizeof(wchar_t*)); j++)
			{	
				if (BadgerWcscmp(drivers[j], certificate_name) == 0)
				{
					PRINT("[+] FOUND: %S -> %S\n", file_path, certificate_name);
					success = TRUE;
				}
			}

			clear:
				if (certificate_context) CertFreeCertificateContext(certificate_context);
				if (certificate) intFree(certificate);
				if (certificate_header) intFree(certificate_header);
		}

	} while(FALSE);

	if (file_handle) NtClose(file_handle);
	
	return success;
}

void enumerate_loaded_drivers() {
    DWORD dwResult = ERROR_SUCCESS;
	LSTATUS lstatus = ERROR_SUCCESS;
	SC_HANDLE scm_handle = NULL;
	unsigned long bytes_needed = 0;
	unsigned long services_returned = 0;
	PBYTE services = NULL;
	PWCHAR registry_path = NULL;
	HKEY key_handle = NULL;
	unsigned long length = MAX_PATH * 2;
	PWCHAR driver_path = NULL;


	// Allocate memory for registry path buffer.
	registry_path = (PWCHAR)intAlloc(MAX_PATH * 2);
	if (NULL == registry_path)
	{
	    INTALLOC_E;
		return;
	}

	do {

		// Allocate memory for registry path buffer.
		driver_path = (PWCHAR)intAlloc(MAX_PATH * 2);
		if (NULL == driver_path)
		{
			INTALLOC_E;
			break;
		}
		
		// Create a handle to the service manager for calls to EnumServicesStatusExW.
		scm_handle = OpenSCManagerA(NULL, NULL, SC_MANAGER_ENUMERATE_SERVICE);
		if (!scm_handle)
		{
			ERR_PRINT("OpenSCManagerA");
			break;
		}

		EnumServicesStatusExW(scm_handle, SC_ENUM_PROCESS_INFO, SERVICE_DRIVER, SERVICE_ACTIVE, NULL, 0, &bytes_needed, &services_returned, NULL, NULL);
		dwResult = GetLastError();
		if (ERROR_MORE_DATA != dwResult) {
			BadgerDispatch(g_dispatch, "[-] %s() failed at %s:%d with error: %ld\n","EnumServicesStatusExW", __FILE__, __LINE__, GetLastError());
			break;
		}

		// Allocate memory for the services buffer.
		services = (PBYTE)intAlloc(bytes_needed);
		if (NULL == services)
		{
			INTALLOC_E;
			break;
		}

		// Retrieve a buffer of active driver services.
		if (!EnumServicesStatusExW(scm_handle, SC_ENUM_PROCESS_INFO, SERVICE_DRIVER , SERVICE_ACTIVE, services, bytes_needed, &bytes_needed, &services_returned, NULL, NULL))
		{
			ERR_PRINT("EnumServicesStatusExW");
			break;
		}

		LPENUM_SERVICE_STATUS_PROCESSW service = (LPENUM_SERVICE_STATUS_PROCESSW)services;
		for (unsigned long i = 0; i < services_returned; i++) {
			memset(driver_path, 0, (MAX_PATH * 2));
			memset(registry_path, 0, (MAX_PATH * 2));
			wcsncat(registry_path,  L"SYSTEM\\CurrentControlSet\\Services\\", MAX_PATH);
			wcsncat(registry_path, service->lpServiceName, MAX_PATH);

			// Open the registry key
			lstatus = RegOpenKeyExW(HKEY_LOCAL_MACHINE, registry_path, 0, KEY_QUERY_VALUE, &key_handle);
			if (ERROR_SUCCESS != lstatus)
			{
				BadgerDispatch(g_dispatch, "[-] RegOpenKeyExW() failed at %s:%d with error: %ld\n", __FILE__, __LINE__, lstatus);
				break;
			}

			length = MAX_PATH * 2;

			// Actually query the IMagePath and fill in the buffer
			lstatus = RegQueryValueExW(key_handle, L"ImagePath", NULL, NULL, (LPBYTE)driver_path, &length);
			if (ERROR_SUCCESS != lstatus)
			{
				//BeaconPrintf(CALLBACK_ERROR, "ADVAPI32$RegQueryValueExW failed. (%lu)\n", dwResult);
				//goto fail;
				EPRINT("[-] Failed to get ImagePath for %S [RegQueryValueExW() failed at %s:%d with error: %ld]\n", service->lpServiceName, __FILE__, __LINE__, lstatus);
				dwResult = ERROR_SUCCESS;
			}
			else
			{
				// Validate the driver
				if (!validate_driver(driver_path))
				{
					// EPRINT("[-] validate_driver() failed for %S\n", driver_path);
				}
			}

			if (NULL != key_handle) {
				CloseHandle(key_handle);
				key_handle = NULL;
			}
			service++;

		}

	} while (FALSE);

	if (services) intFree(services);
	if (scm_handle) CloseServiceHandle(scm_handle);
	if (driver_path) intFree(driver_path);
	if (registry_path) intFree(registry_path);
}

void coffee(char** argv, int argc, WCHAR** dispatch) {
    g_dispatch = dispatch;
    enumerate_loaded_drivers();
}
