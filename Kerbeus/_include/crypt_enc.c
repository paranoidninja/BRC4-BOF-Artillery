#pragma once
#include "functions.c"

#define encrypt(rawBytes, rawSize, key, eType, keyUsage, result, size) \
    encrypt_impl(rawBytes, rawSize, key, eType, keyUsage, result, (DWORD *)(size))

BOOL encrypt_impl(byte* rawBytes, int rawSize, byte* key, DWORD eType, int keyUsage, byte** result, DWORD* size) {
    PKERB_ECRYPT pCSystem;
    PVOID pContext;
    BOOL status = FALSE;

    if (!NT_SUCCESS(CDLocateCSystem(eType, &pCSystem))) {
        PRINT_OUT("[x] Failed to call CDLocateCSystem");
        return TRUE;
    }

    if (!NT_SUCCESS(pCSystem->Initialize(key, pCSystem->KeySize, keyUsage, &pContext))) {
        PRINT_OUT("[x] Failed to initialize crypto system");
        return TRUE;
    }
    *size = rawSize;

    DWORD modulo = *size % pCSystem->BlockSize;
    if (modulo)
        *size += pCSystem->BlockSize - modulo;

    *size += pCSystem->HeaderSize;
    *result = MemAlloc(*size);

    if (*result) {
        if (!NT_SUCCESS(pCSystem->Encrypt(pContext, rawBytes, rawSize, *result, size))) {
            PRINT_OUT("[x] Failed to encrypt data");
            status = TRUE;
        }
    }
    else {
        PRINT_OUT("[x] Failed alloc memory");
        status = TRUE;
    }

    pCSystem->Finish(&pContext);
    return status;
}
