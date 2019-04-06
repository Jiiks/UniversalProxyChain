// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

void MBox(LPCWSTR msg, LPCWSTR caption) {
    MessageBox(0, msg, caption, MB_OK);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        MBox(L"Test Lib", L"Test Lib");
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

