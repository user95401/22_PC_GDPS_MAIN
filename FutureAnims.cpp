#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <cocos2d.h>
#include <gd.h>
#include "mod_utils.hpp"
#include "hooks.hpp"
#include <MinHook.h>
std::string lastAnimation;
PlayerObject* PlayerObj;
inline void(__thiscall* PlayerObject_update)(PlayerObject* self, float);
void __fastcall PlayerObject_update_H(PlayerObject* self, void*, float dtidk) {
    PlayerObject_update(self, dtidk);
    PlayerObj = self;
    if (PlayerObj->m_playerSpeed > 1.290 && PlayerObj->m_isRobot && lastAnimation != std::string("run2")) PlayerObj->RobotSprite->runAnimation("run2");
    if (PlayerObj->m_playerSpeed > 1.590 && PlayerObj->m_isRobot && lastAnimation != std::string("run3")) PlayerObj->RobotSprite->runAnimation("run3");
}
inline void(__thiscall* runAnimation)(CCAnimatedSprite*, std::string);
void __fastcall runAnimation_H(CCAnimatedSprite* self, void*, std::string name) {
    runAnimation(self, name);
    lastAnimation = name;
}
DWORD WINAPI thread_func(void* hModule) {
    MH_Initialize();
    HOOK(base + 0x1E8200, PlayerObject_update, false);//fk
    //HOOK(base + 0x14f60, runAnimation, false);//fk
    MH_EnableHook(MH_ALL_HOOKS);
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
        CreateThread(0, 0, thread_func, hModule, 0, 0);
    return TRUE;
}