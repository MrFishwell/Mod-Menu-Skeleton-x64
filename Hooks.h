#pragma once

#include <Windows.h>

namespace Hooks
{
	// hooks switches.
	static bool swWriteFile = false;

	// Original functions.
	extern BOOL(WINAPI* originalWriteFile)(HANDLE, LPCVOID, DWORD, LPDWORD, LPOVERLAPPED);

	// Detoured functions.
	BOOL WINAPI detouredWriteFile(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped);
}

