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
    LoadLibrary("adaf-dll\\Release\\22_PC_GDPS_MAIN.dll");
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
        CreateThread(0, 0, thread_func, hModule, 0, 0);
    return TRUE;
}