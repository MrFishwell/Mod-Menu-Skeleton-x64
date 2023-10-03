// precompiled headers
#include "framework.h"
#include <cstdio>
#include <iostream>
#include <detours.h>
#include "Hooks.h"

void cheatMain(HMODULE hModule)
{
    bool isMenuVisable = false; // imgui with dx12. [not yet implemanted]

    AllocConsole();
    SetConsoleTitle("[~Logger~] Discord @ Fishwell");
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);

    std::cout << "Dll injected successfully!\n";

    // dll msg.
    MessageBox(NULL, "Dll injected successfully!", "Discord @ Fishwell Menu", MB_ICONINFORMATION | MB_OK);

    // main cheat loop.
    while (true)
    {
        // stop the loop.
        if (GetAsyncKeyState(VK_INSERT) & 1)
        {
            //MessageBox(NULL, "Exit!", "Discord @ Fishwell Menu", MB_ICONINFORMATION | MB_OK);
            std::cout << "Exit!\n";
            break;
        }

        // activate hook.
        if (GetAsyncKeyState(VK_HOME) & 1)
        {
            //MessageBox(NULL, "swWriteFile hook!", "Discord @ Fishwell Menu", MB_ICONINFORMATION | MB_OK
            Hooks::swWriteFile = !Hooks::swWriteFile;
            std::cout << "swWriteFile hook is " << Hooks::swWriteFile << '\n';
        }
    }

    // eject dll and free lib.
    if (f)
        fclose(f);
    FreeConsole();
    FreeLibraryAndExitThread(hModule, 0);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        // init-ms-detours.
        DetourRestoreAfterWith();
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());

        /* all hooks goes here. */
        DetourAttach(&(PVOID&)Hooks::originalWriteFile, Hooks::detouredWriteFile);
        /* end of hooks */

        /*DetourTransactionCommit();*/

        HANDLE cheatThread = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)cheatMain, hModule, 0, nullptr);

        // clear the handle, dll is being ejected.
        if (cheatThread)
            CloseHandle(cheatThread);
        break;
    }

    case DLL_PROCESS_DETACH:
    {
        // exit-ms-detours.
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());

        /* all hooks goes here. */
        DetourDetach(&(PVOID&)Hooks::originalWriteFile, Hooks::detouredWriteFile);
        /* end of hooks */

        DetourTransactionCommit();

        break;
    }
    }
    return TRUE;
}