#pragma once
#include "functions.c"

#define checksum(key, key_length, data, data_length, chksumUsage, keyUsage, result, size) \
    checksum_impl(key, key_length, data, data_length, chksumUsage, keyUsage, result, (DWORD *)(size))

BOOL checksum_impl(byte* key, int key_length, byte* data, int data_length, int chksumUsage, int keyUsage, byte** result, DWORD* size) {
    PKERB_CHECKSUM pCheckSum;
    PVOID pContext;

    if (!NT_SUCCESS(CDLocateCheckSum(chksumUsage, &pCheckSum))) {
        PRINT_OUT("[x] Failed to call CDLocateCSystem");
        return TRUE;
    }

    if (!NT_SUCCESS(pCheckSum->InitializeEx(key, key_length, keyUsage, &pContext))) {
        PRINT_OUT("[x] Failed to initialize crypto system");
        return TRUE;
    }

    *size = pCheckSum->CheckSumSize;
    *result = MemAlloc(*size);

    pCheckSum->Sum(pContext, data_length, data);
    pCheckSum->Finalize(pContext, *result);
    pCheckSum->Finish(&pContext);

    return FALSE;
}
