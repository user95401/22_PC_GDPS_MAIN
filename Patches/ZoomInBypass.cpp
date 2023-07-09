#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "mod_utils.hpp"

DWORD WINAPI thread_func(void* hModule) {
    //ZoomInBypass
    ModUtils::write_bytes(base + 0x87801, { 0x90, 0x90, 0x90 });
    ModUtils::write_bytes(base + 0x87806, { 0x90, 0x90, 0x90 });
    //ZoomOutBypass(unsafe)
    /*ModUtils::write_bytes(base + 0x87871, { 0x90, 0x90, 0x90 });
    ModUtils::write_bytes(base + 0x87876, { 0x90, 0x90, 0x90 });*/
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
        CreateThread(0, 0, thread_func, hModule, 0, 0);
    return TRUE;
}