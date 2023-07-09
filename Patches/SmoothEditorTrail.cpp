#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "mod_utils.hpp"

DWORD WINAPI thread_func(void* hModule) {
    //SmoothEditorTrail
    ModUtils::write_bytes(base + 0x16AB0D, { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 });
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
        CreateThread(0, 0, thread_func, hModule, 0, 0);
    return TRUE;
}