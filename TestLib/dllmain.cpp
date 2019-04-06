extern "C" {
    int __declspec(dllexport) __stdcall postAttach() {
        // Do whatever post attach
        return 0;
    }
}

BOOL APIENTRY DllMain( 
    HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
) {
    return TRUE;
}

