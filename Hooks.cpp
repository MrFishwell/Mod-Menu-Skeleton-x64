#include "framework.h"
#include <detours.h>
#include <iostream>
#include "Hooks.h"

// Original functions. ~~~~~~~~~~~~~~~~~~~~~~~~

BOOL(WINAPI* Hooks::originalWriteFile)(HANDLE, LPCVOID, DWORD, LPDWORD, LPOVERLAPPED) = WriteFile;

// end of original functions. ~~~~~~~~~~~~~~~~~~~~~~~~


// Detoured functions. ~~~~~~~~~~~~~~~~~~~~~~~~

BOOL WINAPI Hooks::detouredWriteFile(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped)
{
    if (swWriteFile)
    {
        const char* hookedBuff = "Fishwell is here!";
        DWORD buffSize = (DWORD)strlen(hookedBuff);
        return originalWriteFile(hFile, hookedBuff, buffSize, lpNumberOfBytesWritten, lpOverlapped);
    }

    return originalWriteFile(hFile, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, lpOverlapped);
}

// end of detoured functions. ~~~~~~~~~~~~~~~~~~~~~~~~