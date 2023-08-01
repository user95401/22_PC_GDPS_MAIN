#include "Gameplay.hpp"

/*
██████╗░██╗░░░░░░█████╗░██╗░░░██╗██╗░░░░░░█████╗░██╗░░░██╗███████╗██████╗░
██╔══██╗██║░░░░░██╔══██╗╚██╗░██╔╝██║░░░░░██╔══██╗╚██╗░██╔╝██╔════╝██╔══██╗
██████╔╝██║░░░░░███████║░╚████╔╝░██║░░░░░███████║░╚████╔╝░█████╗░░██████╔╝
██╔═══╝░██║░░░░░██╔══██║░░╚██╔╝░░██║░░░░░██╔══██║░░╚██╔╝░░██╔══╝░░██╔══██╗
██║░░░░░███████╗██║░░██║░░░██║░░░███████╗██║░░██║░░░██║░░░███████╗██║░░██║
╚═╝░░░░░╚══════╝╚═╝░░╚═╝░░░╚═╝░░░╚══════╝╚═╝░░╚═╝░░░╚═╝░░░╚══════╝╚═╝░░╚═╝
*/
void PlayLayerMod::updateByGamePlayOptins(PlayLayer* self) {
    //sai mod pack settings
    GameManager::sharedState()->setGameVariable("showLvlInfo", GameManager::sharedState()->getGameVariable("0109"));//showLvlInfo 0109
    GameManager::sharedState()->setGameVariable("practiceMusic", GameManager::sharedState()->getGameVariable("0125"));//practiceMusic 0125
    GameManager::sharedState()->setGameVariable("hideAttempt", GameManager::sharedState()->getGameVariable("0135"));//hideAttempt 0135
    if (self->m_isPracticeMode && GameManager::sharedState()->getGameVariable("0134")) self->m_attemptLabel->setVisible(false);

    if (GameManager::sharedState()->getGameVariable("0136")) {
        //No Glow
        ModUtils::write_bytes(base + 0xCFF35, { 0x90 , 0x90 });
        ModUtils::write_bytes(base + 0xF02A4, { 0xe9 , 0xc0, 0x00, 0x00, 0x00, 0x90 });
        ModUtils::write_bytes(base + 0xF0434, { 0xe9 , 0xc0, 0x00, 0x00, 0x00, 0x90 });
    }
    else {
        //return Glow
        ModUtils::write_bytes(base + 0xCFF35, { 0x74 , 0x0D });
        ModUtils::write_bytes(base + 0xF02A4, { 0x0F , 0x84 , 0xBF , 0x00 , 0x00 , 0x00 });
        ModUtils::write_bytes(base + 0xF0434, { 0x0F , 0x84 , 0xBF , 0x00 , 0x00 , 0x00 });
    }
}
bool(__thiscall* PlayLayer_init)(PlayLayer*, GJGameLevel*);
bool __fastcall PlayLayer_init_H(PlayLayer* self, int edx, GJGameLevel* level) {
    if (!PlayLayer_init(self, level)) return false;
    PlayLayerMod::PlayLayerFromINit = (PlayLayer*)self;
    auto gm = gd::GameManager::sharedState();
    //smoothFix
    if (gm->getGameVariable("0023") == true) {
        gm->setGameVariable("0023", false);
        self->onQuit();
        AchievementNotifier::sharedState()->notifyAchievement("Do not enable Smooth Fix!", "just dont pls", "exMark_001.png", true);
        GameSoundManager::sharedState()->playEffect("door001.ogg");
    }
    PlayLayerMod::updateByGamePlayOptins(self);

    GameManager::sharedState()->setPlayerShip(GameManager::sharedState()->getIntGameVariable("oldShipIcon"));//bring up by oldShipIcon
    if (GameManager::sharedState()->getPlayerShip() != 170) GameManager::sharedState()->setIntGameVariable("oldShipIcon", GameManager::sharedState()->getPlayerShip());//save oldShipIcon
    
    PlayLayerMod::enableTheCameraYFolow = false;
    return true;
}

PlayLayer* (__cdecl* PlayLayer_resetLevel)(PlayLayer*);
void __fastcall PlayLayer_resetLevel_H(PlayLayer* self) {
    PlayLayer_resetLevel(self);
    PlayLayerMod::updateByGamePlayOptins(self);
    if (PlayLayerMod::isSwingCopterMode && !self->m_isPracticeMode || !self->m_pPlayer1->m_isShip) {
        GameManager::sharedState()->setPlayerShip(GameManager::sharedState()->getIntGameVariable("oldShipIcon"));//bring up by oldShipIcon
        PlayLayerMod::isSwingCopterMode = false;
    }
    self->m_pObjectLayer->setScale(1.0);
    self->m_bottomGround->setScale(1.0);
    self->m_topGround->setScaleX(1.0);
    PlayLayerMod::enableTheCameraYFolow = false;
}

PlayLayer* (__cdecl* PlayLayer_levelComplete)(PlayLayer*);
bool __fastcall PlayLayer_levelComplete_H(PlayLayer* self) {
    if (!PlayLayer_levelComplete(self)) return false;
    GJGameLevel* level = self->m_level;
    if (level->m_nLevelID == 1070) {
        GameManager::sharedState()->setUGV("LevelAreaInnerLayer_level1", true);
        if (GameManager::sharedState()->getUGV("LevelAreaInnerLayer_level1")) { AchievementNotifier::sharedState()->notifyAchievement("Completed #1", "You completed level of The Tower.", "GJ_completesIcon_001.png", true); }
    }
    if (level->m_nLevelID == 2049) {
        GameManager::sharedState()->setUGV("LevelAreaInnerLayer_level2", true);
        if (GameManager::sharedState()->getUGV("LevelAreaInnerLayer_level2")) { AchievementNotifier::sharedState()->notifyAchievement("Completed #2", "You completed level of The Tower.", "GJ_completesIcon_001.png", true); }
    }
    if (level->m_nLevelID == 632) {
        GameManager::sharedState()->setUGV("LevelAreaInnerLayer_level3", true);
        if (GameManager::sharedState()->getUGV("LevelAreaInnerLayer_level3")) { AchievementNotifier::sharedState()->notifyAchievement("Completed #3", "You completed level of The Tower.", "GJ_completesIcon_001.png", true); }
    }
    if (level->m_nLevelID == 21) {
        GameManager::sharedState()->setUGV("LevelAreaInnerLayer_level4", true);
        if (GameManager::sharedState()->getUGV("LevelAreaInnerLayer_level4")) { AchievementNotifier::sharedState()->notifyAchievement("Completed #4", "You completed level of The Tower.", "GJ_completesIcon_001.png", true); }
    }
    return true;
}

PlayLayer* (__cdecl* PlayLayer_onQuit)(PlayLayer*);
void __fastcall PlayLayer_onQuit_H(PlayLayer* self) {
    PlayLayer_onQuit(self);
    PlayLayerMod::updateByGamePlayOptins(self);
    if (PlayLayerMod::isSwingCopterMode) {
        GameManager::sharedState()->setPlayerShip(GameManager::sharedState()->getIntGameVariable("oldShipIcon"));//bring up by oldShipIcon
    }
    PlayLayerMod::isSwingCopterMode = false;
    PlayLayerMod::enableTheCameraYFolow = false;
}

void CreatePlayLayerHooks() {
    HOOK(base + 0x1FB780, PlayLayer_init, true);
    HOOK(base + 0x20BF00, PlayLayer_resetLevel, true);
    HOOK(base + 0x1FD3D0, PlayLayer_levelComplete, true);
    HOOK(base + 0x20D810, PlayLayer_onQuit, true);
}


//██████╗░██╗░░░░░░█████╗░██╗░░░██╗███████╗██████╗░░█████╗░██████╗░░░░░░██╗███████╗░█████╗░████████╗
//██╔══██╗██║░░░░░██╔══██╗╚██╗░██╔╝██╔════╝██╔══██╗██╔══██╗██╔══██╗░░░░░██║██╔════╝██╔══██╗╚══██╔══╝
//██████╔╝██║░░░░░███████║░╚████╔╝░█████╗░░██████╔╝██║░░██║██████╦╝░░░░░██║█████╗░░██║░░╚═╝░░░██║░░░
//██╔═══╝░██║░░░░░██╔══██║░░╚██╔╝░░██╔══╝░░██╔══██╗██║░░██║██╔══██╗██╗░░██║██╔══╝░░██║░░██╗░░░██║░░░
//██║░░░░░███████╗██║░░██║░░░██║░░░███████╗██║░░██║╚█████╔╝██████╦╝╚█████╔╝███████╗╚█████╔╝░░░██║░░░
//╚═╝░░░░░╚══════╝╚═╝░░╚═╝░░░╚═╝░░░╚══════╝╚═╝░░╚═╝░╚════╝░╚═════╝░░╚════╝░╚══════╝░╚════╝░░░░╚═╝░░░
inline void(__thiscall* PlayerObject_ringJump)(PlayerObject*, GameObject*);
void __fastcall PlayerObject_ringJump_H(gd::PlayerObject* self, int, gd::GameObject* ring) {
    PlayerObject_ringJump(self, ring);
    if (ring->m_nObjectID == 3004 && ring->m_bHasBeenActivated) {
        self->spiderTestJump(true);
        if (ring->m_bRandomisedAnimStart) ring->m_bHasBeenActivated = false;
        if (ring->m_bRandomisedAnimStart) ring->m_bHasBeenActivatedP2 = false;
    }
}

inline void(__thiscall* bumpPlayer)(GJBaseGameLayer*, PlayerObject*, GameObject*);
void __fastcall bumpPlayer_H(GJBaseGameLayer* self, int, gd::PlayerObject* Player, gd::GameObject* bumper) {
    bumpPlayer(self, Player, bumper);
    if (bumper->m_nObjectID == 3005) {
        Player->spiderTestJump(true);
        if (bumper->m_bRandomisedAnimStart) bumper->m_bHasBeenActivated = false;
        if (bumper->m_bRandomisedAnimStart) bumper->m_bHasBeenActivatedP2 = false;
    }
    if (bumper->m_bRandomisedAnimStart && bool(bumper->m_nObjectID == 3005 || bumper->m_nObjectID == 35 || bumper->m_nObjectID == 140 || bumper->m_nObjectID == 1332 || bumper->m_nObjectID == 67)) {
        bumper->m_bHasBeenActivated = false;
        bumper->m_bHasBeenActivatedP2 = false;
    }
}

inline void(__thiscall* PlayerObject_update)(PlayerObject* self, float);
void __fastcall PlayerObject_update_H(PlayerObject* self, void*, float dtidk) {
    PlayerObject_update(self, dtidk);
    if (PlayLayerMod::enableTheCameraYFolow && self->m_isInPlayLayer && PlayLayerMod::PlayLayerFromINit->m_pPlayer1->m_position.y >= 180.0) {
        PlayLayerMod::PlayLayerFromINit->m_cameraYLocked = true;
        PlayLayerMod::PlayLayerFromINit->m_cameraY = PlayLayerMod::PlayLayerFromINit->m_pPlayer1->m_position.y - 140;
        PlayLayerMod::PlayLayerFromINit->m_cameraX = PlayLayerMod::PlayLayerFromINit->m_cameraX - 210;
    }
}

static inline void update_swing_copter(gd::PlayerObject* __this, const float delta) {
    __this->setScaleY((fabs(__this->getScaleY())));
    __this->deactivateParticle();
    *reinterpret_cast<double*>(reinterpret_cast<uintptr_t>(__this) + 0x528) = 0.8;

    const auto _direction = __this->m_isUpsideDown ? -1.f : 1.f;
    const auto _size = (__this->m_vehicleSize != true) ? .85f : 1.f;
    const auto _gravity = (std::fabs(__this->m_yAccel) > 6.) ? __this->m_gravity + 1. : __this->m_gravity;

    const auto modifier = -.5 * _gravity * delta * _direction / _size;
    const auto y_acceleration = __this->m_yAccel + modifier;

    if (std::fabs(__this->m_yAccel) <= 6. || std::fabs(y_acceleration) <= std::fabs(__this->m_yAccel))
        __this->m_yAccel = y_acceleration;

    if (__this->m_isHolding && __this->m_hasJustHeld) {
        __this->m_hasJustHeld = false;
        __this->flipGravity(!__this->m_isUpsideDown, true);
    }
}
void(__thiscall* updateJump) (gd::PlayerObject* __this, float delta);
void  __fastcall  updateJump_H(gd::PlayerObject* __this, void*) {
    auto delta = 0.f;
    __asm movss[delta], xmm1;
    if (!PlayLayerMod::isSwingCopterMode) {
        return updateJump(__this, delta);
    }
    return update_swing_copter(__this, delta);
}

void CreatePlayerObjectHooks() {
    HOOK(base + 0x1E8F80, updateJump, true);
    HOOK(base + 0x1f4ff0, PlayerObject_ringJump, true);
    HOOK(base + 0x10ed50, bumpPlayer, true);
    HOOK(base + 0x1E8200, PlayerObject_update, true);//fk
}