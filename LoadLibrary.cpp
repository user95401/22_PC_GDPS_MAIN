#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <iostream>
#include <random>
#include <iostream>
using namespace std;

DWORD WINAPI thread_func(void* hModule) {
    
    LoadLibrary("modloaderit.dll");
    LoadLibrary("xinput9_1_0.dll");
    LoadLibrary("rainsystem.dll");

    //modsth().extension() == ".so" || it->path().extension() == ".dylib")) {
    LoadLibrary("Libs\\22_PC_GDPS_MAIN.dll");
    LoadLibrary("C:\\Users\\Lenovo\\source\\22_PC_GDPS_MAIN\\Release\\22_PC_GDPS_MAIN.dll");
    LoadLibrary("Libs\\gdPlatformerMode-minimal.dll");
    LoadLibrary("Libs\\absolute_lm.By-Absolute.dll");
    LoadLibrary("Libs\\Patches.dll");
    LoadLibrary("Libs\\rgb-color-input.dll");
    LoadLibrary("Libs\\msvcr180.dll");
    LoadLibrary("Libs\\cocosTrailBugFix.dll");
    LoadLibrary("Libs\\MenuMusicToggle.dll");
    LoadLibrary("Libs\\SaiModPack.dll");
    //other
    LoadLibrary("Libs\\shell32.dll");
    LoadLibrary("Libs\\kernel32.dll");
    LoadLibrary("Libs\\opengl32.dll");
    LoadLibrary("Libs\\advapi32.dll");
    LoadLibrary("Libs\\api-ms-win-core-path-l1-1-0.dll"); //!!!!!!
    LoadLibrary("Libs\\api-ms-win-crt-runtime-l1-1-0.dll"); //!!!!!!
    LoadLibrary("Libs\\advapi32res.dll");
    LoadLibrary("Libs\\ucrtbased.dll");
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
        CreateThread(0, 0, thread_func, hModule, 0, 0);
    return TRUE;
}