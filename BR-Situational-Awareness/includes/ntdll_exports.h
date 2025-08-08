#pragma once
#include "common.h"

#ifndef     NT_SUCCESS
#define 	NT_SUCCESS(Status)   (((NTSTATUS)(Status)) >= 0)
#endif

#define NtQueryInformationProcess           Ntdll$NtQueryInformationProcess
#define NtCreateFile                        Ntdll$NtCreateFile
#define NtClose                             Ntdll$NtClose

// NT Function headers
__declspec(dllimport) __stdcall NTSTATUS Ntdll$NtOpenProcessToken(HANDLE ProcessHandle, ACCESS_MASK DesiredAccess, PHANDLE TokenHandle);
__declspec(dllimport) __stdcall NTSTATUS Ntdll$NtAdjustPrivilegesToken(HANDLE TokenHandle, BOOLEAN DisableAllPrivileges, PTOKEN_PRIVILEGES NewState, ULONG BufferLength, PTOKEN_PRIVILEGES PreviousState, PULONG ReturnLength);
__declspec(dllimport) __stdcall NTSTATUS Ntdll$NtClose(HANDLE Handle);
__declspec(dllimport) __stdcall NTSTATUS Ntdll$NtSetInformationThread(HANDLE ThreadHandle, THREADINFOCLASS ThreadInformationClass, PVOID ThreadInformation, ULONG ThreadInformationLength);
__declspec(dllimport) __stdcall NTSTATUS Ntdll$NtQueryInformationProcess(HANDLE ProcessHandle, PROCESSINFOCLASS ProcessInformationClass, PVOID ProcessInformation, ULONG ProcessInformationLength, PULONG ReturnLength OPTIONAL);
__declspec(dllimport) __stdcall NTSTATUS Ntdll$NtQueryInformationToken(HANDLE TokenHandle, TOKEN_INFORMATION_CLASS TokenInformationClass, PVOID TokenInformation, ULONG TokenInformationLength, PULONG ReturnLength);
__declspec(dllimport) __stdcall NTSTATUS Ntdll$NtQuerySystemInformation(SYSTEM_INFORMATION_CLASS SystemInformationClass, PVOID  SystemInformation, ULONG  SystemInformationLength, PULONG ReturnLength);
__declspec(dllimport) __stdcall NTSTATUS Ntdll$NtOpenProcess(PHANDLE ProcessHandle,ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES ObjectAttributes, PCLIENT_ID ClientId);
__declspec(dllimport) __stdcall NTSTATUS Ntdll$NtOpenThread(PHANDLE ThreadHandle, ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES ObjectAttributes, PCLIENT_ID ClientId);
__declspec(dllimport) __stdcall NTSTATUS Ntdll$NtQueryInformationThread(HANDLE ThreadHandle, THREADINFOCLASS ThreadInformationClass, PVOID  ThreadInformation, ULONG  ThreadInformationLength, PULONG ReturnLength);
__declspec(dllimport) __stdcall NTSTATUS Ntdll$NtResumeThread(HANDLE ThreadHandle, PULONG SuspendCount);  
__declspec(dllimport) __stdcall NTSTATUS Ntdll$NtSuspendThread(HANDLE ThreadHandle, PULONG SuspendCount);  
__declspec(dllimport) __stdcall NTSTATUS Ntdll$NtTerminateThread(HANDLE ThreadHandle, NTSTATUS ExitStatus );
__declspec(dllimport) __stdcall NTSTATUS Ntdll$NtUpdateWnfStateData(void* StateName, void* Buffer, unsigned long Length, void* TypeId, void* ExplicitScope, unsigned long MatchingChangeStamp, unsigned long CheckStamp);
__declspec(dllimport) __stdcall NTSTATUS Ntdll$NtCreateFile(PHANDLE FileHandle, ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES ObjectAttributes, PIO_STATUS_BLOCK   IoStatusBlock, PLARGE_INTEGER AllocationSize, ULONG FileAttributes, ULONG ShareAccess, ULONG CreateDisposition, ULONG CreateOptions, PVOID EaBuffer, ULONG EaLength);

// typedef ULONG(__stdcall* Etw_Event_Write_No_Registration)(_In_ LPCGUID ProviderId, _In_ PCEVENT_DESCRIPTOR EventDescriptor, _In_ ULONG UserDataCount, _In_reads_opt_(UserDataCount) PEVENT_DATA_DESCRIPTOR UserData);
typedef struct in6_addr in6_addr;
__declspec(dllimport) __stdcall ULONG    Ntdll$EtwEventWriteNoRegistration(GUID const* ProviderId, EVENT_DESCRIPTOR const* EventDescriptor, ULONG UserDataCount, EVENT_DATA_DESCRIPTOR* UserData);
__declspec(dllimport) PSTR Ntdll$RtlIpv6AddressToStringA(const in6_addr *Addr, PSTR S);

// __declspec(dllimport) __stdcall  VOID Ntdll$EventDescCreate(PEVENT_DESCRIPTOR EventDescriptor, USHORT  Id, UCHAR   Version, UCHAR   Channel, UCHAR   Level, USHORT  Task, UCHAR Opcode, ULONGLONG Keyword);
