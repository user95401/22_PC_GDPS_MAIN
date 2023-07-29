// 22_PC_GDPS_MAIN.cpp: определяет точку входа для приложения.
//
#include "22_PC_GDPS_MAIN.h"

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace gd;

class idontgiveashit {
public:
    void ondontgiveashit(cocos2d::CCObject*) {
        idontgiveashitbro = (!idontgiveashitbro);
        CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5f, MenuLayer::scene(0)));
        GameSoundManager::sharedState()->playEffect("quitSound_01.ogg");
    }
};
//msg(self);
void msg(CCLayer* self, const char* redText = "", const char* customMsg = "") {
    CCLabelTTF* msg = CCLabelTTF::create(
        "OBJECT HASN'T FOUNDED\nseems u delete or add some mods\n\n that prevent getting objects\n in this layer",
        "Comic Sans MS",
        120.0f);
    if(customMsg!="") msg = CCLabelTTF::create(customMsg, "Comic Sans MS", 80.0f);
    msg->setPosition(ModUtils::getCenterPoint());
    msg->setScale(0.150f);//120.0f for lbl fontSize
    CCLabelTTF* msg2 = CCLabelTTF::create(redText, "Comic Sans MS", 120.0f);
    msg2->setPosition({ msg->getContentSize().width / 2,  msg->getContentSize().height / 2 });
    msg2->setColor({ 255, 70, 70 });
    msg->addChild(msg2);
    if(!idontgiveashitbro) self->removeAllChildren(); //:trollface:
    if (!idontgiveashitbro) self->addChild(msg,666,666);
    if (!idontgiveashitbro) GameManager::sharedState()->fadeInMusic("shop3.mp3");
    CCMenu* dontgiveashit = CCMenu::createWithItem(
        CCMenuItemSpriteExtra::create(
            ButtonSprite::create("i dont give a shit, bro", 80, false, "gjFont06.fnt", "GJ_button_05.png", 30, 5.0f),
            self,
            menu_selector(idontgiveashit::ondontgiveashit)
        )
    );
    dontgiveashit->setPositionY(dontgiveashit->getPositionY() - 120.0f);
    if (!idontgiveashitbro) self->addChild(dontgiveashit);
}

void updateByGamePlayOptins(PlayLayer* self) {
    //sai mod pack settings
    GameManager::sharedState()->setGameVariable("showLvlInfo", GameManager::sharedState()->getGameVariable("0109"));//showLvlInfo 0109
    GameManager::sharedState()->setGameVariable("practiceMusic", GameManager::sharedState()->getGameVariable("0125"));//showLvlInfo 0125
    GameManager::sharedState()->setGameVariable("hideAttempt", GameManager::sharedState()->getGameVariable("0135"));//showLvlInfo 0135
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

inline PlayLayer* (__cdecl* PlayLayer_levelComplete)(PlayLayer*);
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

inline bool(__thiscall* PlayLayer_init)(PlayLayer*, GJGameLevel*);
bool __fastcall PlayLayer_init_H(PlayLayer* self, int edx, GJGameLevel* level) {
    if (!PlayLayer_init(self, level)) return false;
    PlayLayerFromINit = (PlayLayer*)self;
    auto gm = gd::GameManager::sharedState();
    //smoothFix
    if (gm->getGameVariable("0023") == true) {
        gm->setGameVariable("0023", false);
        self->onQuit();
        AchievementNotifier::sharedState()->notifyAchievement("Do not enable Smooth Fix!", "just dont pls", "exMark_001.png", true);
        GameSoundManager::sharedState()->playEffect("door001.ogg");
    }
    updateByGamePlayOptins(self);

    GameManager::sharedState()->setPlayerShip(GameManager::sharedState()->getIntGameVariable("oldShipIcon"));//bring up by oldShipIcon
    if (GameManager::sharedState()->getPlayerShip() != 170) GameManager::sharedState()->setIntGameVariable("oldShipIcon", GameManager::sharedState()->getPlayerShip());//save oldShipIcon

    return true;
}

inline PlayLayer* (__cdecl* PlayLayer_resetLevel)(PlayLayer*);
void __fastcall PlayLayer_resetLevel_H(PlayLayer* self) {
    PlayLayer_resetLevel(self);
    updateByGamePlayOptins(self);
    if (isSwingCopterMode && !self->m_isPracticeMode || !self->m_pPlayer1->m_isShip) {
        GameManager::sharedState()->setPlayerShip(GameManager::sharedState()->getIntGameVariable("oldShipIcon"));//bring up by oldShipIcon
        isSwingCopterMode = false;
    }
}

inline PlayLayer* (__cdecl* PlayLayer_onQuit)(PlayLayer*);
void __fastcall PlayLayer_onQuit_H(PlayLayer* self) {
    PlayLayer_onQuit(self);
    updateByGamePlayOptins(self);
    if (isSwingCopterMode) {
        GameManager::sharedState()->setPlayerShip(GameManager::sharedState()->getIntGameVariable("oldShipIcon"));//bring up by oldShipIcon
    }
    isSwingCopterMode = false;
}

inline void(__thiscall* animateInGround)(PlayLayer*, bool idk);//0x209b20
void __fastcall animateInGround_H(PlayLayer* self, void*, bool idk) {
    //if(!PlayerObj->m_lastActivatedPortal->m_bIsGroupParent) 
        animateInGround(self , idk);
}

inline void(__thiscall* animateOutGround)(PlayLayer*, bool idk);//0x209e60
void __fastcall animateOutGround_H(PlayLayer* self, void*, bool idk) {
    //if(!PlayerObj->m_lastActivatedPortal->m_bIsGroupParent) 
    animateOutGround(self, idk);
}

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
void __fastcall bumpPlayer_H(GJBaseGameLayer* self, int, gd::PlayerObject* Player,  gd::GameObject* bumper) {
    bumpPlayer(self, Player, bumper);
    if (bumper->m_nObjectID == 3005) {
        Player->spiderTestJump(true);
        if(bumper->m_bRandomisedAnimStart) bumper->m_bHasBeenActivated = false;
        if (bumper->m_bRandomisedAnimStart) bumper->m_bHasBeenActivatedP2 = false;
    }
}

inline void(__thiscall* PlayerObject_update)(PlayerObject* self, float);
void __fastcall PlayerObject_update_H(PlayerObject* self, void*, float dtidk) {
    PlayerObject_update(self, dtidk);
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
    if (!isSwingCopterMode) {
        return updateJump(__this, delta);
    }
    return update_swing_copter(__this, delta);
}

inline void(__thiscall* GameObject_activateObject)(GameObject*, PlayerObject*);
void __fastcall GameObject_activateObject_H(GameObject* self, int, PlayerObject* player) {
    GameObject_activateObject(self, player);
    if("SwingCopter"){
        if (self->m_nObjectID == 1933) {
            isSwingCopterMode = true;
            if (GameManager::sharedState()->getPlayerShip() != 170) GameManager::sharedState()->setIntGameVariable("oldShipIcon", GameManager::sharedState()->getPlayerShip());//save oldShipIcon
            GameManager::sharedState()->setPlayerShip(170);
            player->toggleRobotMode(true);
            player->toggleFlyMode(true);
        }
        else if (self->m_nObjectType != kGameObjectTypeNormalGravityPortal && self->m_nObjectType != kGameObjectTypeInverseGravityPortal && self->m_nObjectType != kGameObjectTypeTeleportPortal) {
            GameManager::sharedState()->setPlayerShip(GameManager::sharedState()->getIntGameVariable("oldShipIcon"));//bring up by oldShipIcon
            if (self->m_nObjectID == 13 && isSwingCopterMode) {
                player->toggleRobotMode(true);
                player->toggleFlyMode(true);
            }
            isSwingCopterMode = false;
        }
    }
    //noGround
    if (self->m_nObjectType == kGameObjectTypeShipPortal || self->m_nObjectType == kGameObjectTypeCubePortal || self->m_nObjectType == kGameObjectTypeBallPortal || self->m_nObjectType == kGameObjectTypeUfoPortal || self->m_nObjectType == kGameObjectTypeWavePortal || self->m_nObjectType == kGameObjectTypeRobotPortal || self->m_nObjectType == kGameObjectTypeSpiderPortal) {
        if (self->m_bRandomisedAnimStart && player->m_isInPlayLayer) animateOutGround(PlayLayerFromINit, false);
    }
}

inline void(__thiscall* triggerObject)(GameObject*, GJBaseGameLayer*);//0xd1790
void __fastcall triggerObject_H(GameObject* self, void*, GJBaseGameLayer* baseGameLayer) {
    triggerObject(self, baseGameLayer);
    auto PlayerObj = baseGameLayer->m_pPlayer1;
    if (self->m_nObjectID == 1917) {
        if (PlayerObj->m_playerSpeed > 0.0) {
            //goleft
            PlayerObj->m_playerSpeed = -fabs(PlayerObj->m_playerSpeed);
            //negative scaleX if plr is not dart
            if (!PlayerObj->m_isDart && !PlayerObj->m_isShip) PlayerObj->setScaleX(-PlayerObj->m_vehicleSize);
            //ship flipping
            if (PlayerObj->m_isShip) {
                if (!PlayerObj->m_isUpsideDown) PlayerObj->setScaleY(-PlayerObj->m_vehicleSize);
                else PlayerObj->setScaleY(fabs(PlayerObj->m_vehicleSize));
            }
            //negative rot patch by sai 1E9CD8: org b4 00 00 00 // patch 4c ff ff ff
            ModUtils::write_bytes(base + 0x1E9CD8, { 0x4c, 0xff, 0xff, 0xff });
            //ModUtils::write_bytes(base + 0x1E9CD8, { 0xb4, 0x00, 0x00, 0x00 });
        }
    }
    if (self->m_nObjectID == 1931 && PlayLayerFromINit) {
        PlayLayerFromINit->levelComplete();
        PlayLayerFromINit->m_hasCompletedLevel = true;
        PlayLayerFromINit->moveCameraToPos({self->m_obStartPosition.x - (CCDirector::sharedDirector()->getWinSize().width / 2), self->m_obStartPosition.y - (CCDirector::sharedDirector()->getWinSize().height / 2) });
        PlayLayerFromINit->m_pPlayer1->m_playerSpeed = 0.0;
        PlayLayerFromINit->m_pPlayer1->deactivateParticle();
        PlayLayerFromINit->playExitDualEffect(PlayLayerFromINit->m_pPlayer1);
    }
}

inline void(__thiscall* GameObject_customSetup)(GameObject*);
void __fastcall GameObject_customSetup_H(GameObject* self, int) {
    GameObject_customSetup(self);
    //orb guide
    if (GameManager::sharedState()->getGameVariable("0130")) {
        if (self->m_nObjectType == kGameObjectTypeDropRing) {
            CCSprite* darkblade_03_color_001 = CCSpritePlus::createWithSpriteFrameName("darkblade_03_color_001.png");
            darkblade_03_color_001->setPosition({ 16.200, 16.200 });
            self->addChild(darkblade_03_color_001);
        }
        if (self->m_nObjectType == kGameObjectTypeGreenRing) {
            CCSprite* rod_ball_02_001 = CCSpritePlus::createWithSpriteFrameName("rod_ball_02_001.png");
            rod_ball_02_001->setPosition({ 14.700, 14.700 });
            rod_ball_02_001->setScale(0.400);
            self->addChild(rod_ball_02_001);
        }
        if (self->m_nObjectType == kGameObjectTypeRedJumpRing) {
            CCSprite* d_arrow_02_001 = CCSpritePlus::createWithSpriteFrameName("d_arrow_02_001.png");
            d_arrow_02_001->setPosition({ 15.600, 15.600 });
            d_arrow_02_001->setScale(0.400);
            d_arrow_02_001->setRotation(-90.000);
            self->addChild(d_arrow_02_001);
        }
        if (self->m_nObjectType == kGameObjectTypeGravityRing) {
            CCSprite* GravityRingGuide = CCSpritePlus::createWithSpriteFrameName("d_arrow_02_001.png");
            GravityRingGuide->setPosition({ 15.000, 15.000 });
            GravityRingGuide->setScale(0.400);
            GravityRingGuide->setRotation(-90.000);
            self->addChild(GravityRingGuide);
        }
    }
    //free mode :skull:
    /*if (self->m_nObjectType == kGameObjectTypeShipPortal || self->m_nObjectType == kGameObjectTypeCubePortal || self->m_nObjectType == kGameObjectTypeBallPortal || self->m_nObjectType == kGameObjectTypeUfoPortal || self->m_nObjectType == kGameObjectTypeWavePortal || self->m_nObjectType == kGameObjectTypeRobotPortal || self->m_nObjectType == kGameObjectTypeSpiderPortal) {
        if (self->m_bIsGroupParent) self->m_nObjectType=kGameObjectTypeCubePortal;
    }*/
    //noGround
    if (self->m_nObjectType == kGameObjectTypeShipPortal || self->m_nObjectType == kGameObjectTypeCubePortal || self->m_nObjectType == kGameObjectTypeBallPortal || self->m_nObjectType == kGameObjectTypeUfoPortal || self->m_nObjectType == kGameObjectTypeWavePortal || self->m_nObjectType == kGameObjectTypeRobotPortal || self->m_nObjectType == kGameObjectTypeSpiderPortal) {
        self->m_bIsEffectObject = true;
        //self->m_bActive = true;
    }
    if (self->m_nObjectID == 3004) {
        //main setups
        self->m_nObjectType = kGameObjectTypePinkJumpRing;
        self->m_pBaseColor->defaultColorID = 1011;
        self->m_bIsEffectObject = true;
        
    }
    if (self->m_nObjectID == 3005) {
        //main setups
        self->m_nObjectType = kGameObjectTypePinkJumpPad;//type
        self->m_pBaseColor->defaultColorID = 1011;//defaultColor
        self->m_bIsEffectObject = true;//IsEffectObject (for multiactive feature:smiling_face_with_tear:)
        
        //box setups
        self->setAnchorPoint(CCPoint(self->getAnchorPoint().x, 1.4));// totally :smiling_face_with_tear:
        auto frame = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(self->m_sTextureName.c_str());
        self->m_obObjectSize = cocos2d::CCSizeMake(frame->getRect().size.width, frame->getRect().size.height);
        self->m_obBoxOffset = CCPoint(0, -10);
        self->m_obBoxOffset2 = CCPoint(0, -10);
    }
    if (self->m_sTextureName.find("pixelart_") != self->m_sTextureName.npos) {
        self->m_nObjectType = kGameObjectTypeDecoration;
    }

    if (self->m_nObjectID == 1814) self->setDisplayFrame(cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(
        "edit_eCameraBtn_001.png"));
    if (self->m_nObjectID == 1817) self->setDisplayFrame(cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(
        "edit_e2.2Btn_001.png"));
}

inline void(__thiscall* GameObject_addGlow)(GameObject* self);
void __fastcall GameObject_addGlow_H(GameObject* self) {
    GameObject_addGlow(self);
    if (self->m_nObjectID == 3004) {
    }
}

class CreatorLayerMod : public cocos2d::CCLayer {
public:
    void onMultiplayer(cocos2d::CCObject*) {
    }
    void onEventLevel(cocos2d::CCObject* pSender) {
        EventLevelPage* alert = EventLevelPage::create();
        alert->m_bNoElasticity = true;//HJfod
        alert->show();
    }
    void onAdventureMap(cocos2d::CCObject*) {
        auto layer = LevelAreaLayer::create();
        auto scene = CCScene::create();
        scene->addChild(layer);
        CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5f, scene));
    }
    void onTopLists(cocos2d::CCObject*) {
        auto layer = LevelBrowserLayer::create(GJSearchObject::create(kGJSearchTypeTopListsIDK));
        auto scene = CCScene::create();
        scene->addChild(layer);
        CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5f, scene));
    }
    void onPaths(cocos2d::CCObject*) {
    }
};
void addclbtn(const char* name, cocos2d::SEL_MenuHandler sus, const CCPoint& pos, CCMenu* menu) {
    CCSprite* btn = ModUtils::createSprite(name);
    btn->setScale(0.8f);
    auto btnItem = CCMenuItemSpriteExtra::create(btn, menu, sus);
    btnItem->setPosition(pos);
    menu->addChild(btnItem);
}
inline bool(__thiscall* CreatorLayer_init)(CreatorLayer*);
bool __fastcall CreatorLayer_init_H(CreatorLayer* self) {
    if (!CreatorLayer_init(self)) return false;

    CCMenu* menu = (CCMenu*)self->getChildren()->objectAtIndex(2);
    if (menu->getChildrenCount() == 2) {
        //row1
        addclbtn("GJ_createBtn_001.png", menu_selector(CreatorLayer::onMyLevels),{ -180,90 }, menu);
        addclbtn("GJ_savedBtn_001.png", menu_selector(CreatorLayer::onSavedLevels), { -90,90 }, menu);
        addclbtn("GJ_highscoreBtn_001.png", menu_selector(CreatorLayer::onLeaderboards), { 0,90 }, menu);
        addclbtn("GJ_challengeBtn_001.png", menu_selector(CreatorLayer::onChallenge), { 90,90 }, menu);
        addclbtn("GJ_versusBtn_001.png", nullptr, { 180,90 }, menu);
        //row2
        addclbtn("GJ_mapBtn_001.png", menu_selector(CreatorLayerMod::onAdventureMap), { -180,0 }, menu);
        addclbtn("GJ_dailyBtn_001.png", menu_selector(CreatorLayer::onDailyLevel), { -90,0 }, menu);
        addclbtn("GJ_weeklyBtn_001.png", menu_selector(CreatorLayer::onWeeklyLevel), { 0,0 }, menu);
        addclbtn("GJ_eventBtn_001.png", menu_selector(CreatorLayerMod::onEventLevel), { 90,0 }, menu);
        addclbtn("GJ_gauntletsBtn_001.png", menu_selector(CreatorLayer::onGauntlets), { 180,0 }, menu);
        //row3
        addclbtn("GJ_featuredBtn_001.png", menu_selector(CreatorLayer::onFeaturedLevels), { -180,-90 }, menu);
        addclbtn("GJ_listsBtn_001.png", menu_selector(CreatorLayerMod::onTopLists), { -90,-90 }, menu);
        addclbtn("GJ_pathsBtn_001.png", menu_selector(CreatorLayerMod::onPaths), { 0,-90 }, menu);
        addclbtn("GJ_mapPacksBtn_001.png", menu_selector(CreatorLayer::onMapPacks), { 90,-90 }, menu);
        addclbtn("GJ_searchBtn_001.png", menu_selector(CreatorLayer::onOnlineLevels), { 180,-90 }, menu);
    }
    //remove sai's btns
    CCLayer* shit = (CCLayer*)self->getChildren()->objectAtIndex(0);
    if (shit->getZOrder() == 100) self->removeChild(shit);
    else msg(self, "msvcr180.dll (or Sai.dll by old version)");
    return true;
}

class MenuLayerMod {
public:
    void onTwitch(cocos2d::CCObject* pSender) { CCApplication::sharedApplication()->openURL("https://www.twitch.tv/robtopgames"); }
    void onDiscord(cocos2d::CCObject* pSender) { CCApplication::sharedApplication()->openURL("https://discord.com/invite/geometrydash"); }
    void onPlay(cocos2d::CCObject* pSender) {
        auto scene = CCScene::create();
        scene->addChild(LevelSelectLayer::create(1));
        CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5f, scene));
    }
    void onUpdateHttpResponse(CCHttpClient* client, CCHttpResponse* response) {
        std::vector<char>* responseData = response->getResponseData();
        std::string responseString(responseData->begin(), responseData->end());
        if (responseString != version) {
            AchievementNotifier::sharedState()->notifyAchievement("Update available!", ("You can download actual " + responseString + " version on the website.").c_str(), "GJ_downloadsIcon_001.png", true);
        }
    }
};
inline bool(__thiscall* MenuLayer_init)(MenuLayer*);
bool __fastcall MenuLayer_init_H(MenuLayer* self) {
    if (!MenuLayer_init(self)) return false;

    CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    //self->runAction(CCSequence::create(CCDelayTime::create(0.1f), CCCallFuncO::create(self, callfuncO_selector(MenuLayerMod::termsOfUseLayerShow), self), nullptr));
    
    auto versionLabel = CCLabelBMFont::create(version, "chatFont.fnt");
    versionLabel->setPosition({ winSize.width, 0 });
    versionLabel->setAnchorPoint({ 1.1f, 0 });
    versionLabel->setOpacity({ 130 });
    versionLabel->setScale({ 0.5f });
    self->addChild(versionLabel);
    auto fadeTo200 = CCFadeTo::create(5, 200);
    auto fadeTo130 = CCFadeTo::create(5, 130);
    auto versionLabelseq = CCSequence::create(fadeTo200, fadeTo130, nullptr);
    auto versionLabelrepeat = CCRepeatForever::create(versionLabelseq);
    versionLabel->runAction(versionLabelrepeat);

    //udate if sddso herer
    CCHttpRequest* request = new CCHttpRequest;
    request->setUrl("http://gdps22pc.webq2e.ru/lastUpdate.php");
    request->setRequestType(CCHttpRequest::HttpRequestType::kHttpPost);
    request->setResponseCallback(self, httpresponse_selector(MenuLayerMod::onUpdateHttpResponse));
    CCHttpClient::getInstance()->send(request);
    request->release();

    CCMenu* aFirstMenu = (CCMenu*)self->m_profileBtn->getParent();
    CCMenuItemSpriteExtra* playBtn = (CCMenuItemSpriteExtra*)aFirstMenu->getChildren()->objectAtIndex(0);
    //playBtn->removeFromParent();
    playBtn->setTarget(self, menu_selector(MenuLayerMod::onPlay));

    auto socialsMenu = CCMenu::create();
    self->addChild(socialsMenu, 2);
    socialsMenu->setPosition({ 50, 30 - 6 });

    auto robtopLogo = ModUtils::createSprite("robtoplogo_small.png");
    robtopLogo->setScale(0.8f);
    auto robtopExtra = CCMenuItemSpriteExtra::create(robtopLogo, self, menu_selector(MenuLayer::onRobTop));
    socialsMenu->addChild(robtopExtra);

    auto facebookIcon = ModUtils::createSprite("gj_fbIcon_001.png");
    facebookIcon->setScale(0.8f);
    auto facebookExtra = CCMenuItemSpriteExtra::create(facebookIcon, self, menu_selector(MenuLayer::onFacebook));
    facebookExtra->setSizeMult(1.5f);
    socialsMenu->addChild(facebookExtra);

    auto twitterIcon = ModUtils::createSprite("gj_twIcon_001.png");
    twitterIcon->setScale(0.8f);
    auto twitterExtra = CCMenuItemSpriteExtra::create(twitterIcon, self, menu_selector(MenuLayer::onTwitter));
    twitterExtra->setSizeMult(1.5f);
    socialsMenu->addChild(twitterExtra);

    auto youtubeIcon = ModUtils::createSprite("gj_ytIcon_001.png");
    youtubeIcon->setScale(0.8f);
    auto youtubeExtra = CCMenuItemSpriteExtra::create(youtubeIcon, self, menu_selector(MenuLayer::onYouTube));
    youtubeExtra->setSizeMult(1.5f);
    socialsMenu->addChild(youtubeExtra);

    auto twitchIcon = ModUtils::createSprite("gj_twitchIcon_001.png");
    twitchIcon->setScale(0.8f);
    auto twitchExtra = CCMenuItemSpriteExtra::create(twitchIcon, self, menu_selector(MenuLayerMod::onTwitch));
    twitchExtra->setSizeMult(1.5f);
    socialsMenu->addChild(twitchExtra);

    auto discordIcon = ModUtils::createSprite("gj_discordIcon_001.png");
    discordIcon->setScale(0.8f);
    auto discordExtra = CCMenuItemSpriteExtra::create(discordIcon, self, menu_selector(MenuLayerMod::onDiscord));
    discordExtra->setSizeMult(1.5f);
    socialsMenu->addChild(discordExtra);

    facebookExtra->setPosition(socialsMenu->convertToNodeSpace(CCPoint({ CCDirector::sharedDirector()->getScreenLeft() + 22, CCDirector::sharedDirector()->getScreenBottom() + 55 })));
    twitterExtra->setPosition(facebookExtra->getPosition() + CCPoint({ 30, 0 }));
    youtubeExtra->setPosition(twitterExtra->getPosition() + CCPoint({ 30, 0 }));
    twitchExtra->setPosition(youtubeExtra->getPosition() + CCPoint({ 29, 0 }));
    discordExtra->setPosition(youtubeExtra->getPosition() + CCPoint({ 29, -29 }));

    //the mana principal from msvcr180.dll
    CCLayer* manaprincipalfrommsvcr180sonyx114promax = (CCLayer*)self->getChildren()->objectAtIndex(0);
    if (manaprincipalfrommsvcr180sonyx114promax->getZOrder() == 100) manaprincipalfrommsvcr180sonyx114promax->removeFromParent();
    else msg(self, "msvcr180.dll (or Sai.dll by old version)");
    //and then otrer shit from SaiModPack.dll
    CCLayer* SaiModPackThings = (CCLayer*)self->getChildren()->objectAtIndex(0);
    if (SaiModPackThings->getZOrder() == 100) SaiModPackThings->removeFromParent();
    else msg(self, "SaiModPack.dll");
    //gdshare noitce
    if (CCFileUtils::sharedFileUtils()->isFileExist("mods/GDShare-v0.3.4.dll") ||
        CCFileUtils::sharedFileUtils()->isFileExist("mods/GDShare.dll") ||
        CCFileUtils::sharedFileUtils()->isFileExist("GDShare-v0.3.4.dll")
        ) msg(self, "Seems you installed GDShare\nGDShare is unstable with sai's mods,\nyou can get game crash", " ");
    
    GameManager::sharedState()->setPlayerShip(GameManager::sharedState()->getIntGameVariable("oldShipIcon"));//bring up by oldShipIcon
    return true;
}

inline bool (__cdecl* GJGarageLayer_init)(GJGarageLayer*);
bool __fastcall GJGarageLayer_init_H(GJGarageLayer* self) {
    if (!GJGarageLayer_init(self)) return false;
    self->removeChild((CCLayer*)self->getChildren()->objectAtIndex(0)); //remove some idk nn random corners
    CCLayer* saimodpacklayer = (CCLayer*)self->getChildren()->objectAtIndex(7); //this is carazy shit 7
    if(saimodpacklayer->getZOrder()==1000) saimodpacklayer->getChildren()->removeLastObject();//remove socials 
    else msg(self, "SaiModPack.dll");
    CCMenu* menu = (CCMenu*)self->getChildren()->objectAtIndex(19); //this is carazy shit 19
    if (menu->getChildrenCount() == 5) {
        menu->getChildren()->removeLastObject();//remove infbtn
        menu->getChildren()->removeLastObject();//and remove colorsBtn
    }
    else msg(self);
    return true;
}

inline void(__thiscall* GJGarageLayer_onBack)(GJGarageLayer*, cocos2d::CCObject*);
void __fastcall GJGarageLayer_onBack_H(GJGarageLayer* self, void*, cocos2d::CCObject* bruh) {
    GJGarageLayer_onBack(self, bruh);
    if (GameManager::sharedState()->getPlayerShip() != 170) GameManager::sharedState()->setIntGameVariable("oldShipIcon", GameManager::sharedState()->getPlayerShip());//save oldShipIcon
}

inline bool(__thiscall* KeysLayer_init)(KeysLayer*);
bool __fastcall KeysLayer_init_H(KeysLayer* self) {
    if (!KeysLayer_init(self)) return false;

    auto winSize = CCDirector::sharedDirector()->getWinSize();

    auto treasureRoomGround_001 = ModUtils::createSprite("treasureRoomGround_001.png");
    treasureRoomGround_001->setBlendFunc({ GL_SRC_ALPHA, GL_ONE });
    auto size = treasureRoomGround_001->getContentSize();
    treasureRoomGround_001->setScaleX(winSize.width / size.width);
    treasureRoomGround_001->setScaleY(2.5);
    treasureRoomGround_001->setPosition({ winSize.width / 2, 0 });
    treasureRoomGround_001->setZOrder(-1);
    treasureRoomGround_001->setOpacity({ 150 });
    self->addChild(treasureRoomGround_001);

    auto cornerUL = ModUtils::createSprite("treasureRoomSpiderweb_001.png");
    cornerUL->setColor({ 0,0,0 }); cornerUL->setOpacity(100);
    cornerUL->setPosition({ 0, winSize.height });
    cornerUL->setScale(1.2);
    cornerUL->setAnchorPoint({ 0.05,0.05 });
    cornerUL->setFlipX(1); cornerUL->setFlipY(1);
    cornerUL->setRotation(90);
    self->addChild(cornerUL, -1);

    auto cornerUR = ModUtils::createSprite("treasureRoomSpiderweb_001.png");
    cornerUR->setColor({ 0,0,0 }); cornerUR->setOpacity(100);
    cornerUR->setPosition({ winSize.width,winSize.height });
    cornerUR->setScale(1.2);
    cornerUR->setAnchorPoint({ 0.05,0.05 });
    cornerUR->setFlipX(1); cornerUR->setFlipY(1);
    cornerUR->setRotation(180);
    self->addChild(cornerUR, -1);

    return true;
}

inline bool(__thiscall* MoreOptionsLayer_init)(MoreOptionsLayer*);
bool __fastcall MoreOptionsLayer_init_H(gd::MoreOptionsLayer* self) {
    if (!MoreOptionsLayer_init(self)) return false;
    //ревёрс инженередсер
    self->addToggle("Music in Practice", "0125", "Normal music is played in sync when playing created levels in practice mode.");//org is 0125
    self->addToggle("Detailed Info", "0109", "More info in level"); //org is 0109
    self->addToggle("Hide Attempts", "0135", nullptr);
    self->addToggle("Hide Attempts Practice", "0134", nullptr);
    self->addToggle("Extra LDM", "0136", "LDM also removes glow and enter effects. Levels without LDM show the option LDM Lite.");
    self->addToggle("Hide Portal Guide", "0129", "Toggles OFF the extra indicators on portals");
    self->addToggle("Show Orb Guide", "0130", "Toggles ON the extra indicators on orbs");
    return true;
}

inline GJDropDownLayer* (__cdecl* SupportLayer_customSetup)(GJDropDownLayer*);
void __fastcall SupportLayer_customSetup_H(GJDropDownLayer* self) {
    SupportLayer_customSetup(self);

    self->m_pLayer->removeChild((CCSprite*)self->m_pLayer->getChildren()->objectAtIndex(6), false);//developedBy
    self->m_pLayer->removeChild((CCSprite*)self->m_pLayer->getChildren()->objectAtIndex(6), false);//poweredBy

    CCMenu* menu = (CCMenu*)self->m_pLayer->getChildren()->objectAtIndex(8);
    menu->removeAllChildren();

    auto developersLabel = CCMenuItemSpriteExtra::create(ModUtils::createSprite("developersLabel.png"), self, menu_selector(customLayerxd::switchcustomLayerxdbtn));
    developersLabel->m_bAnimationEnabled = false;
    developersLabel->m_bColorEnabled = true;//yo
    developersLabel->setPosition({ 0, -20 });
    menu->addChild(developersLabel);
}

inline bool(__thiscall* LevelEditorLayer_init)(LevelEditorLayer*, GJGameLevel*);
bool __fastcall LevelEditorLayer_init_H(LevelEditorLayer* self, int edx, GJGameLevel* level) {
    if (!LevelEditorLayer_init(self, level)) return false;
    CCLayerColor* THE_LINE = CCLayerColor::create({ 255,255,255,55 });
    THE_LINE->setAnchorPoint({ 0.f,0.f });
    THE_LINE->setPosition({ 0, CCDirector::sharedDirector()->getScreenTop() - 115 });
    THE_LINE->setScaleX({ 50 }); THE_LINE->setScaleY({ 0.002f });
    self->addChild(THE_LINE, -1);
    return true;
}

inline void(__thiscall* LevelEditorLayer_onStopPlaytest)(LevelEditorLayer*, CCObject*);
void __fastcall LevelEditorLayer_onStopPlaytest_H(LevelEditorLayer* self, void*, CCObject* sender) {
    LevelEditorLayer_onStopPlaytest(self, sender);
    if (isSwingCopterMode) {
        GameManager::sharedState()->setPlayerShip(GameManager::sharedState()->getIntGameVariable("oldShipIcon"));//bring up by oldShipIcon
    }
    isSwingCopterMode = false;
}

inline void(__thiscall* LevelEditorLayer_onPlaytest)(LevelEditorLayer*);
void __fastcall LevelEditorLayer_onPlaytest_H(LevelEditorLayer* self, void*) {
    LevelEditorLayer_onPlaytest(self);
    if (isSwingCopterMode) {
        GameManager::sharedState()->setPlayerShip(GameManager::sharedState()->getIntGameVariable("oldShipIcon"));//bring up by oldShipIcon
    }
    isSwingCopterMode = false;
}

inline bool(__thiscall* EditorPauseLayer_init)(EditorPauseLayer*, LevelEditorLayer*);
bool __fastcall EditorPauseLayer_init_H(EditorPauseLayer* self, int edx, LevelEditorLayer* levelEditorLayer) {
    if (!EditorPauseLayer_init(self, levelEditorLayer)) return false;
    if (isSwingCopterMode) {
        GameManager::sharedState()->setPlayerShip(GameManager::sharedState()->getIntGameVariable("oldShipIcon"));//bring up by oldShipIcon
    }
    isSwingCopterMode = false;
    return true;
}

inline void(__thiscall* EditorUI_setupCreateMenu)(EditorUI*);
void __fastcall EditorUI_setupCreateMenu_H(EditorUI* self, void*) {
    EditorUI_setupCreateMenu(self);
    //tab6
    auto tab6 = (EditButtonBar*)(self->m_pCreateButtonBars->objectAtIndex(6));
    tab6->m_pButtonArray->insertObject(self->getCreateBtn(3004, 4), 13);
    tab6->m_pButtonArray->insertObject(self->getCreateBtn(3005, 4), 5);
    tab6->loadFromItems(tab6->m_pButtonArray, GameManager::sharedState()->getIntGameVariable("0049"), GameManager::sharedState()->getIntGameVariable("0050"), true);
    //tab7
    auto tab7 = (EditButtonBar*)(self->m_pCreateButtonBars->objectAtIndex(7));
    //lava nad other animated blocks
    tab7->m_pButtonArray->addObject(self->getCreateBtn(1591, 4));
    tab7->m_pButtonArray->addObject(self->getCreateBtn(1593, 4));
    tab7->m_pButtonArray->addObject(self->getCreateBtn(1849, 4));
    tab7->m_pButtonArray->addObject(self->getCreateBtn(1850, 4));
    tab7->m_pButtonArray->addObject(self->getCreateBtn(1851, 4));
    tab7->m_pButtonArray->addObject(self->getCreateBtn(1852, 4));
    tab7->m_pButtonArray->addObject(self->getCreateBtn(1853, 4));
    tab7->m_pButtonArray->addObject(self->getCreateBtn(1854, 4));
    tab7->m_pButtonArray->addObject(self->getCreateBtn(1855, 4));
    tab7->m_pButtonArray->addObject(self->getCreateBtn(1858, 4));
    tab7->m_pButtonArray->addObject(self->getCreateBtn(1856, 4));
    tab7->m_pButtonArray->addObject(self->getCreateBtn(1697, 4));
    tab7->m_pButtonArray->addObject(self->getCreateBtn(1698, 4));
    tab7->m_pButtonArray->addObject(self->getCreateBtn(1699, 4));
    tab7->m_pButtonArray->addObject(self->getCreateBtn(1857, 4));
    tab7->m_pButtonArray->addObject(self->getCreateBtn(1860, 4));
    tab7->m_pButtonArray->addObject(self->getCreateBtn(1516, 4));
    tab7->m_pButtonArray->addObject(self->getCreateBtn(1518, 4));
    tab7->m_pButtonArray->addObject(self->getCreateBtn(1517, 4));
    //reload tab7 i think
    tab7->loadFromItems(tab7->m_pButtonArray, GameManager::sharedState()->getIntGameVariable("0049"), GameManager::sharedState()->getIntGameVariable("0050"), true);

    //tab8
    //auto tab8 = (EditButtonBar*)(self->m_pCreateButtonBars->objectAtIndex(8));
    //tab8->m_pButtonArray->addObject(self->getCreateBtn(2140, 4));
    //tab8->loadFromItems(tab8->m_pButtonArray, GameManager::sharedState()->getIntGameVariable("0049"), GameManager::sharedState()->getIntGameVariable("0050"), true);
    //tab14
    auto tab14 = (EditButtonBar*)(self->m_pCreateButtonBars->objectAtIndex(14));
    auto timeWarp = tab14->m_pButtonArray->objectAtIndex(4);
    tab14->m_pButtonArray->removeObjectAtIndex(4);
    tab14->m_pButtonArray->insertObject(self->getCreateBtn(2701, 5), 4);
    tab14->m_pButtonArray->insertObject(self->getCreateBtn(2702, 5), 5);
    tab14->m_pButtonArray->insertObject(self->getCreateBtn(2067, 5), 11);
    tab14->m_pButtonArray->insertObject(self->getCreateBtn(1912, 5), 20);
    tab14->m_pButtonArray->insertObject(self->getCreateBtn(2068, 5), 21);
    tab14->m_pButtonArray->insertObject(self->getCreateBtn(1913, 5), 22);
    tab14->m_pButtonArray->insertObject(self->getCreateBtn(1914, 5), 23);
    tab14->m_pButtonArray->insertObject(self->getCreateBtn(1916, 5), 24);
    tab14->m_pButtonArray->insertObject(self->getCreateBtn(1917, 4), 25);
    tab14->m_pButtonArray->insertObject(self->getCreateBtn(1934, 5), 26);
    tab14->m_pButtonArray->insertObject(timeWarp, 27);
    tab14->m_pButtonArray->insertObject(self->getCreateBtn(1931, 4), 38);
    tab14->m_pButtonArray->insertObject(self->getCreateBtn(1932, 5), 39);
    tab14->loadFromItems(tab14->m_pButtonArray, GameManager::sharedState()->getIntGameVariable("0049"), GameManager::sharedState()->getIntGameVariable("0050"), true);

    return;
}
inline void(__thiscall* EditorUI_selectObject)(EditorUI*, GameObject* obj, bool filter);//win 0x86250;
void __fastcall EditorUI_selectObject_H(EditorUI* self, void*, GameObject* obj, bool filter) {
    EditorUI_selectObject(self, obj, filter);
    lastSelectedObj = obj->m_nObjectID;
}

bool DailyLevelIsWeekly;
class DailyLevelPageMod {
public:
    void onSafe(cocos2d::CCObject*) {
        CCScene* browserLayerScene = CCScene::create();
        browserLayerScene->addChild(LevelBrowserLayer::create(gd::GJSearchObject::create(DailyLevelIsWeekly ? SearchType::kSearchTypeWeekly : SearchType::kSearchTypeDaily)));
        CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5, browserLayerScene));
    }
};
inline bool(__thiscall* DailyLevelPage_init)(DailyLevelPage*, bool);
bool __fastcall DailyLevelPage_init_H(DailyLevelPage* self, void*, bool isWeekly) {
    if (!DailyLevelPage_init(self, isWeekly)) return false;
    //isWeekly thing
    DailyLevelIsWeekly = isWeekly;
    //remove corner
    CCLayer* layer = (CCLayer*)self->getChildren()->objectAtIndex(0);
    layer->removeChild((CCSprite*)layer->getChildren()->objectAtIndex(4));
    //safeBtn
    CCMenu* menu = self->m_pButtonMenu;
    auto safeBtn = gd::CCMenuItemSpriteExtra::create(ModUtils::createSprite("GJ_safeBtn_001.png"), self, menu_selector(DailyLevelPageMod::onSafe));
    safeBtn->setPosition({ 380, -20 });
    menu->addChild(safeBtn);
    return true;
}

inline void(__thiscall* ProfilePage_loadPageFromUserInfo)(ProfilePage*, GJUserScore*);
void __fastcall ProfilePage_loadPageFromUserInfo_H(ProfilePage* self, void*, gd::GJUserScore* a2) {
    ProfilePage_loadPageFromUserInfo(self, a2);
    CCLayer* layer = dynamic_cast<CCLayer*>(self->getChildren()->objectAtIndex(0));
    auto winSize = CCDirector::sharedDirector()->getWinSize();

    auto tohideSwing = ModUtils::createSprite("square02b_001.png");
    tohideSwing->setPosition({ (winSize.width / 2) + 146, (winSize.height / 2) + 40 });
    tohideSwing->setScale(0.5f);
    tohideSwing->setColor({ 191, 114, 62 });
    layer->addChild(tohideSwing, 12);

    auto swing = SimplePlayer::create(170);
    swing->updatePlayerFrame(170, kIconTypeShip);
    swing->setFrames("swing_for_simplePLayer_001.png", "swing_for_simplePLayer_2_001.png", nullptr, "swing_for_simplePLayer_glow_001.png", "swing_for_simplePLayer_extra_001.png");
    swing->setColor({ GameManager::sharedState()->colorForIdx(a2->getPlayerColor1()) });
    swing->setSecondColor({ GameManager::sharedState()->colorForIdx(a2->getPlayerColor2()) });
    swing->setGlowOutline(a2->getGlowEnabled());
    swing->setPosition({ (winSize.width / 2) + 146, (winSize.height / 2) + 34 });
    layer->addChild(swing, 13);
}

inline LoadingLayer* (__cdecl* LoadingLayer_loadAssets)(LoadingLayer*);
void __fastcall LoadingLayer_loadAssets_H(LoadingLayer* self) {
    LoadingLayer_loadAssets(self);
    auto winSize = CCDirector::sharedDirector()->getWinSize();

    CCSprite* fmodLogo = ModUtils::createSprite("fmodLogo.png");
    self->removeChildByTag(9230);
    fmodLogo->setTag(9230);
    fmodLogo->setPosition({ winSize.width - 35, 30 });
    fmodLogo->setColor(ccc3(1, 1, 1));
    fmodLogo->setScale({ 0.7f });
    self->addChild(fmodLogo);

    CCSprite* cocos2DxLogo = ModUtils::createSprite("cocos2DxLogo.png");
    self->removeChildByTag(1086);
    fmodLogo->setTag(1086);
    cocos2DxLogo->setPosition({ winSize.width - 35, 12 });
    cocos2DxLogo->setScale({ 0.7f });
    self->addChild(cocos2DxLogo);

    if (self->m_nLoadIndex == 6) {
        //_ModsResources
        CCTextureCache::sharedTextureCache()->addImage("_ModsResources.png", 0);
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("_ModsResources.plist");
        //game001Sheet platformer btns from other game :>
        CCTextureCache::sharedTextureCache()->addImage("game001Sheet.png", 0);
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("game001Sheet.plist");
        //GJ_ParticleSheet
        CCTextureCache::sharedTextureCache()->addImage("GJ_ParticleSheet.png", 0);
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("GJ_ParticleSheet.plist");
        //GJ_ParticleSheet
        CCTextureCache::sharedTextureCache()->addImage("PixelSheet_01.png", 0);
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("PixelSheet_01.plist");
        //TreasureRoomSheet
        CCTextureCache::sharedTextureCache()->addImage("TreasureRoomSheet.png", 0);
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("TreasureRoomSheet.plist");
        //TowerSheet
        CCTextureCache::sharedTextureCache()->addImage("TowerSheet.png", 0);
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("TowerSheet.plist");

        CCFileUtils::sharedFileUtils()->addSearchPath("mods");
        CCFileUtils::sharedFileUtils()->addSearchPath("adaf-dll");

        //ObjectToolbox::sharedState()->addObject(2140, "pixelart_040_001.png");

        ObjectToolbox::sharedState()->addObject(3004, "spiderRing_001.png");
        GameObject* spiderRing_001 = (GameObject*)ObjectToolbox::sharedState()->getUserObject();
        ObjectToolbox::sharedState()->addObject(3005, "spiderBump_001.png");
    }
    self->removeChildByTag(777);
    if (!hooksLoaded && self->m_nLoadIndex > 8) {
        self->m_nLoadIndex = 8;
        self->addChild(
            CCLabelTTF::create("                                   Waiting for hooks...\n\n",
            "Comic Sans MS", 10)
        , 5, 777);
    }
    if(hooksLoaded && !self->m_bFromRefresh) self->addChild(
            CCLabelTTF::create("                                 All hooks enabled!\n\n",
            "Comic Sans MS", 10)
        , 5, 777);
}

inline CCSprite* (__cdecl* CCSprite_create)(const char*);
CCSprite* CCSprite_create_H(const char* name) {
    if (strstr(name, "1337")) {
        CCSprite* no = CCSprite::create();
        //MessageBoxA(nullptr, name,"CCSprite_createHook -> no sprite", MB_ICONINFORMATION | MB_OK);
        return no;
    }
    if (std::string(name) == "GJ_colores_001.png" || std::string(name) == "GJ_paletaBtn_001.png")
        return ModUtils::createSprite("GJ_paintBtn_001.png");
    return CCSprite_create(name);
}

inline CCSprite* (__cdecl* CCSprite_createWithSpriteFrameName)(const char*);
CCSprite* CCSprite_createWithSpriteFrameName_H(const char* name) {
    if (std::string(name) == "groundSquareShadow_001.png" ||
        strstr(name, "1337")) {
        CCSprite* no = CCSprite::create();
        //MessageBoxA(nullptr, name, "CCSprite_createWithSpriteFrameNameHook -> no sprite", MB_ICONINFORMATION | MB_OK);
        return no;
    }
    if (std::string(name) == "GJ_colores_001.png" || std::string(name) == "GJ_paletaBtn_001.png")
        return ModUtils::createSprite("GJ_paintBtn_001.png");
    return CCSprite_createWithSpriteFrameName(name);
}

inline CCLabelBMFont* (__cdecl* CCLabelBMFont_create)(const char*, const char*);
CCLabelBMFont* CCLabelBMFont_create_H(const char* str, const char* fntFile) {
    //if (strstr(str, "1337")) {
    //    CCLabelBMFont* lbl = CCLabelBMFont::create("", "gjFont01.fnt");
    //    lbl->setVisible(false);
    //    lbl->setAnchorPoint({ -999.0f,-999.0f });
    //    //MessageBoxA(nullptr, str, "CCLabelBMFont_createHook -> no lbl", MB_ICONINFORMATION | MB_OK);
    //    return lbl;
    //}
    if (std::string(str) == "Practice music hack" || std::string(str) == "Show level info" ||  std::string(str) == "Hide attempt label")
        str = "Available in Gameplay Options only";
    if (std::string(str) == "Select Color") 
        str = "";

    if (std::string(str) == "Edit Animation Settings" && std::string(fntFile) == "goldFont.fnt") {
        if (lastSelectedObj == 3004 || lastSelectedObj == 3005 //spiter orb anda pad
            || lastSelectedObj == 12 || lastSelectedObj == 13 || lastSelectedObj == 47 || lastSelectedObj == 111 || lastSelectedObj == 660 || lastSelectedObj == 745 || lastSelectedObj == 47 || lastSelectedObj == 1331) //noground portals
            str = "Object setup";
    }
    if (std::string(str) == "Randomize Start" && std::string(fntFile) == "bigFont.fnt") {
        if (lastSelectedObj == 3004 || lastSelectedObj == 3005) str = "Allow multi activate";
        if (lastSelectedObj == 12 || lastSelectedObj == 13 || lastSelectedObj == 47 || lastSelectedObj == 111 || lastSelectedObj == 660 || lastSelectedObj == 745 || lastSelectedObj == 47 || lastSelectedObj == 1331)
            str = "No ground";//noGround
    }
    if (std::string(str) == "Animation settings help" && std::string(fntFile) == "chatFont.fnt") {
        CCLabelBMFont* lbl = CCLabelBMFont::create("", "chatFont.fnt", 435, kCCTextAlignmentCenter);
        std::string info = "";
        if (lastSelectedObj == 3004 || lastSelectedObj == 3005)
            info = "Allows multi activate feature.\nNote: set up first groundHeight(first 2 grounds gamemode) \nto reduce bugs with cube or robot";
        if (lastSelectedObj == 12 || lastSelectedObj == 13 || lastSelectedObj == 47 || lastSelectedObj == 111 || lastSelectedObj == 660 || lastSelectedObj == 745 || lastSelectedObj == 47 || lastSelectedObj == 1331)
            info = "Just will animate out grounds when enter portal";//noGround
        lbl->setString(std::string("                      \n" + info + "\n\n\n ").c_str());
        if(info != "") return lbl;
    }

    return CCLabelBMFont_create(str, fntFile);
}

DWORD WINAPI thread_func(void* hModule) {
    LoadLibrary("cocos-explorer.dll");

    // initialize minhook
    MH_Initialize();

    HOOK(base + 0x18C8E0, LoadingLayer_loadAssets, true);
    MH_EnableHook(LoadingLayer_loadAssets);
    
    CC_HOOK("?create@CCSprite@cocos2d@@SAPAV12@PBD@Z", CCSprite_create, false);
    CC_HOOK("?createWithSpriteFrameName@CCSprite@cocos2d@@SAPAV12@PBD@Z", CCSprite_createWithSpriteFrameName, false);
    CC_HOOK("?create@CCLabelBMFont@cocos2d@@SAPAV12@PBD0@Z", CCLabelBMFont_create, false);

    HOOK(base + 0x1907B0, MenuLayer_init, false);
    //HOOK(base + 0x191b50, MenuLayer_onPlay, false);
    HOOK(base + 0x4DE40, CreatorLayer_init, false);
    HOOK(base + 0x1255D0, GJGarageLayer_init, false);
    HOOK(base + 0x12ADF0, GJGarageLayer_onBack, false);

    HOOK(base + 0x15ee00, LevelEditorLayer_init, true);
    HOOK(base + 0x876E0, LevelEditorLayer_onStopPlaytest, true);
    HOOK(base + 0x1695A0, LevelEditorLayer_onPlaytest, true);
    HOOK(base + 0x730e0, EditorPauseLayer_init, true);
    HOOK(base + 0x7CAF0, EditorUI_setupCreateMenu, false);//huh
    HOOK(base + 0x86250, EditorUI_selectObject, false);

    HOOK(base + 0x1FB780, PlayLayer_init, true);
    HOOK(base + 0x20BF00, PlayLayer_resetLevel, true);
    HOOK(base + 0x1FD3D0, PlayLayer_levelComplete, true);
    HOOK(base + 0x20D810, PlayLayer_onQuit, true);
    HOOK(base + 0x209b20, animateInGround, true);
    HOOK(base + 0x209e60, animateOutGround, true);

    HOOK(base + 0x1E8F80, updateJump, true);
    HOOK(base + 0x1f4ff0, PlayerObject_ringJump, true);
    HOOK(base + 0x10ed50, bumpPlayer, true);
    HOOK(base + 0x1E8200, PlayerObject_update, true);//fk
    HOOK(base + 0xEF0E0, GameObject_activateObject, true);
    HOOK(base + 0xd1c10, GameObject_customSetup, true);
    HOOK(base + 0xd1790, triggerObject, false);
    HOOK(base + 0xcfef0, GameObject_addGlow, false);

    HOOK(base + 0x154560, KeysLayer_init, true);
    HOOK(base + 0x1DE8F0, MoreOptionsLayer_init, true);
    HOOK(base + 0x25C7B0, SupportLayer_customSetup, true);
    HOOK(base + 0x6a900, DailyLevelPage_init, true);
    HOOK(base + 0x210040, ProfilePage_loadPageFromUserInfo, true);

    // enable all hooks you've created with minhook
    MH_EnableHook(MH_ALL_HOOKS);
    hooksLoaded = true;
    //MessageBoxA(nullptr, "hooks enabled", __func__, MB_ICONINFORMATION | MB_OK);

    if("hacks container lol") {
        // Level Completion
        ModUtils::write_bytes(base + 0x1FD557, { 0xEB, 0x0C, });
        ModUtils::write_bytes(base + 0x1FD742, { 0xC7, 0x87, 0xE0, 0x02, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0xC7, 0x87, 0xE4, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 });
        ModUtils::write_bytes(base + 0x1FD756, { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 });
        ModUtils::write_bytes(base + 0x1FD79A, { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 });
        ModUtils::write_bytes(base + 0x1FD7AF, { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 });
        // Load Failed
        ModUtils::write_bytes(base + 0x18B2B4, { 0xB0 , 0x01 });
        //Rotation Hack
        ModUtils::write_bytes(base + 0x85CBC, { 0xB8, 0x01, 0x00, 0x00, 0x00, 0x90 });
        ModUtils::write_bytes(base + 0x8BDDD, { 0xB8, 0x01, 0x00, 0x00, 0x00, 0x90 });
        ModUtils::write_bytes(base + 0x8BE16, { 0xB8, 0x01, 0x00, 0x00, 0x00, 0x90 });
        ModUtils::write_bytes(base + 0xECA3D, { 0xB8, 0x01, 0x00, 0x00, 0x00, 0x90 });
        ModUtils::write_bytes(base + 0xEE5A9, { 0xB8, 0x01, 0x00, 0x00, 0x00, 0x90 });
        ModUtils::write_bytes(base + 0x20181E, { 0xB8, 0x01, 0x00, 0x00, 0x00, 0x90 });
        //DefaultSongBypass
        ModUtils::write_bytes(base + 0x174407, { 0x90, 0x90 });
        ModUtils::write_bytes(base + 0x174411, { 0x90, 0x90, 0x90 });
        ModUtils::write_bytes(base + 0x174456, { 0x90, 0x90 });
        ModUtils::write_bytes(base + 0x174460, { 0x90, 0x90, 0x90 });
        //Allows you to scroll out the editor
        ModUtils::write_bytes(base + 0x8FAAC, { 0xEB });
        ModUtils::write_bytes(base + 0x8FA95, { 0xEB });
        ModUtils::write_bytes(base + 0x8FAC5, { 0xEB });
        ModUtils::write_bytes(base + 0x8FADC, { 0xEB });
        //ZoomInBypass
        ModUtils::write_bytes(base + 0x87801, { 0x90, 0x90, 0x90 });
        ModUtils::write_bytes(base + 0x87806, { 0x90, 0x90, 0x90 });
        //PlaytestZoomBypass
        ModUtils::write_bytes(base + 0x1697A9, { 0x90, 0x90 });
        //SmoothEditorTrail
        ModUtils::write_bytes(base + 0x16AB0D, { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 });
        //Music Sync Correction
        ModUtils::write_bytes(base + 0x208808, { 0xEB, 0x08 });
    }

    LoadLibrary("cocos-explorer.dll");

    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
        CreateThread(0, 0, thread_func, hModule, 0, 0);
    return TRUE;
}