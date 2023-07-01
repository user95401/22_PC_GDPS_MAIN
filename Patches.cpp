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
    //Allows you to scroll out the editor
    ModUtils::write_bytes(base + 0x8FAAC, { 0xEB });
    ModUtils::write_bytes(base + 0x8FA95, { 0xEB });
    ModUtils::write_bytes(base + 0x8FAC5, { 0xEB });
    ModUtils::write_bytes(base + 0x8FADC, { 0xEB });
    //DefaultSongBypass
    ModUtils::write_bytes(base + 0x174407, { 0x90, 0x90 });
    ModUtils::write_bytes(base + 0x174411, { 0x90, 0x90, 0x90 });
    ModUtils::write_bytes(base + 0x174456, { 0x90, 0x90 });
    ModUtils::write_bytes(base + 0x174460, { 0x90, 0x90, 0x90 });
    //ZoomBypass
    ModUtils::write_bytes(base + 0x87801, { 0x90, 0x90, 0x90 });
    ModUtils::write_bytes(base + 0x87806, { 0x90, 0x90, 0x90 });
    ModUtils::write_bytes(base + 0x87871, { 0x90, 0x90, 0x90 });
    ModUtils::write_bytes(base + 0x87876, { 0x90, 0x90, 0x90 });
    //PlaytestZoomBypass
    ModUtils::write_bytes(base + 0x1697A9, { 0x90, 0x90 });
    //SmoothEditorTrail
    ModUtils::write_bytes(base + 0x16AB0D, { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 });

    //Soooo.. Instant Mirror Portal Patch?
    ModUtils::write_bytes(base + 0x20ACA3, { 0xC7, 0x04, 0x24, 0x00, 0x00, 0x00, 0x00 });
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
        CreateThread(0, 0, thread_func, hModule, 0, 0);
    return TRUE;
}