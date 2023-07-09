#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "mod_utils.hpp"

DWORD WINAPI thread_func(void* hModule) {
    //Rotation Hack
    ModUtils::write_bytes(base + 0x85CBC, { 0xB8, 0x01, 0x00, 0x00, 0x00, 0x90 });
    ModUtils::write_bytes(base + 0x8BDDD, { 0xB8, 0x01, 0x00, 0x00, 0x00, 0x90 });
    ModUtils::write_bytes(base + 0x8BE16, { 0xB8, 0x01, 0x00, 0x00, 0x00, 0x90 });
    ModUtils::write_bytes(base + 0xECA3D, { 0xB8, 0x01, 0x00, 0x00, 0x00, 0x90 });
    ModUtils::write_bytes(base + 0xEE5A9, { 0xB8, 0x01, 0x00, 0x00, 0x00, 0x90 });
    ModUtils::write_bytes(base + 0x20181E, { 0xB8, 0x01, 0x00, 0x00, 0x00, 0x90 });
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
        CreateThread(0, 0, thread_func, hModule, 0, 0);
    return TRUE;
}