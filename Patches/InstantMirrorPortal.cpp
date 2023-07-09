#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "mod_utils.hpp"

DWORD WINAPI thread_func(void* hModule) {
    //Soooo.. Instant Mirror Portal Patch?
    ModUtils::write_bytes(base + 0x20ACA3, { 0xC7, 0x04, 0x24, 0x00, 0x00, 0x00, 0x00 });
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
        CreateThread(0, 0, thread_func, hModule, 0, 0);
    return TRUE;
}