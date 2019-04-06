#include <Windows.h>
#include <string>
#include "dllmain.h"
#include <filesystem>

namespace fs = std::experimental::filesystem;

const std::string poxyPath = "uclib";
std::vector<std::experimental::filesystem::path> proxies;

void MBox(const LPCWSTR msg, const LPCWSTR caption) {
    MessageBox(nullptr, msg, caption, MB_OK);
}

extern "C" __declspec(dllexport)  HRESULT __stdcall DirectInput8Create(
    HINSTANCE hinst,
    DWORD dwVersion,
    REFIID riidltf,
    LPVOID *ppvOut,
    LPUNKNOWN punkOuter) {

    char realLib[MAX_PATH] = { 0 };
    GetSystemDirectoryA(realLib, sizeof(realLib));
    strcat_s(realLib, MAX_PATH, "\\dinput8.dll");
    const auto hLibrary = LoadLibraryA(realLib);

    if(hLibrary)  {
        const auto originalProc = GetProcAddress(hLibrary, "DirectInput8Create");
        if(originalProc)  {
            return reinterpret_cast<HRESULT(WINAPI *)(HINSTANCE, DWORD, REFIID, LPVOID *, LPUNKNOWN)>(originalProc)(hinst, dwVersion, riidltf, ppvOut, punkOuter);
        }
    }

    return E_FAIL;
}

void ListProxies() {
    for(const auto &entry : fs::directory_iterator(poxyPath)) proxies.push_back(entry.path());
}

typedef int(__stdcall *f_postAttach)();

void LoadProxies() {
    for(const auto &proxy : proxies) {
        const auto hres = LoadLibrary(proxy.c_str());

        if(!hres) {
            MBox(L"Failed to load lib", L"Error");
        }

        const auto postAttach = reinterpret_cast<f_postAttach>(GetProcAddress(hres, "postAttach"));
        if(postAttach) {
            postAttach();
        }
    }
}


BOOL WINAPI DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
    switch(ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        ListProxies();
        LoadProxies();
        break;
    }
    return TRUE;
}
