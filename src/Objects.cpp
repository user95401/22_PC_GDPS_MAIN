#include "Objects.hpp"

CustomTriggerPopup::CustomTriggerPopup() :
    FLAlertLayer() {
    m_nJoystickConnected = -1;
    m_bNoElasticity = true;
    m_effectObject = nullptr;
}
CustomTriggerPopup* CustomTriggerPopup::create(EffectGameObject* obj) {
    CustomTriggerPopup* ret = new CustomTriggerPopup();
    if (ret && ret->init(obj)) ret->autorelease();
    else CC_SAFE_DELETE(ret);
    return ret;
}
void CustomTriggerPopup::onTouch(CCObject* sneder) { m_effectObject->m_bTouchTriggered = bool(!m_effectObject->m_bTouchTriggered); update(); }
void CustomTriggerPopup::onSpawn(CCObject* sneder) { m_effectObject->m_bSpawnTriggered = bool(!m_effectObject->m_bSpawnTriggered); update(); }
void CustomTriggerPopup::update() {
    saveString->setString(m_effectObject->getSaveString().c_str());
}
void CustomTriggerPopup::onClose(CCObject* callback) {
    m_effectObject = reinterpret_cast<EffectGameObject*>(GameObject::objectFromString(m_effectObject->getSaveString(), true));
    this->removeFromParentAndCleanup(true);
}
void CustomTriggerPopup::keyBackClicked() {
    onClose(NULL);
}
bool CustomTriggerPopup::init(EffectGameObject* obj) {
    m_effectObject = obj;
    if (CCLayerColor::initWithColor(ccc4(0, 0, 0, 150)) && m_effectObject->m_nObjectID > 1) {
        registerWithTouchDispatcher();
        setTouchEnabled(true);
        setKeypadEnabled(true);

        m_pLayer = CCLayer::create();
        addChild(m_pLayer);
        m_pButtonMenu = CCMenu::create();
        addChild(m_pButtonMenu);

        auto scale9 = extension::CCScale9Sprite::create("GJ_square01.png");
        scale9->setContentSize(CCSizeMake(300, 280));
        m_pButtonMenu->addChild(scale9, -2);

        m_pButtonMenu->addChild(saveString = CCLabelBMFont::create(m_effectObject->getSaveString().c_str(), "chatFont.fnt", 160));

        auto okBtn = CCMenuItemSpriteExtra::create(ButtonSprite::create("OK", 0, false, "goldFont.fnt", "GJ_button_01.png", 0, 1.0),
            this, menu_selector(CustomTriggerPopup::onClose));
        m_pButtonMenu->addChild(okBtn);
        okBtn->setScale(0.8928571428571429);
        okBtn->setPositionY(-113.0);

        auto onTouchBtn = CCMenuItemToggler::createWithStandardSprites(this, menu_selector(CustomTriggerPopup::onTouch));
        onTouchBtn->setScale(0.7142857142857143);
        onTouchBtn->setPosition(-128.0, -68.5);
        onTouchBtn->toggle(m_effectObject->m_bTouchTriggered);
        m_pButtonMenu->addChild(onTouchBtn);

        auto onSpawnBtn = CCMenuItemToggler::createWithStandardSprites(this, menu_selector(CustomTriggerPopup::onSpawn));
        onSpawnBtn->setScale(0.7142857142857143);
        onSpawnBtn->setPosition(-128.0, -108.5);
        onSpawnBtn->toggle(m_effectObject->m_bSpawnTriggered);
        m_pButtonMenu->addChild(onSpawnBtn);

        auto SpawnTriggered = CCLabelBMFont::create("Spawn   \nTriggered", "bigFont.fnt");
        SpawnTriggered->setScale(0.37142857142857144);
        CCPoint SpawnTriggeredpos(-74.5, -108.0);
        SpawnTriggered->setPosition(m_pLayer->convertToNodeSpace(SpawnTriggeredpos));
        m_pButtonMenu->addChild(SpawnTriggered);

        auto TouchTriggered = CCLabelBMFont::create("Touch    \nTriggered", "bigFont.fnt");
        TouchTriggered->setScale(0.37142857142857144);
        CCPoint TouchTriggeredpos(-76.0, -68.0);
        TouchTriggered->setPosition(m_pLayer->convertToNodeSpace(TouchTriggeredpos));
        m_pButtonMenu->addChild(TouchTriggered);
        return true;
    }
    else return false;
}

inline void(__thiscall* GameObject_activateObject)(GameObject*, PlayerObject*);
void __fastcall GameObject_activateObject_H(GameObject* self, int, PlayerObject* player) {
    GameObject_activateObject(self, player);
    if ("SwingCopter") {
        if (self->m_nObjectID == 1933) {
            PlayLayerMod::isSwingCopterMode = true;
            if (GameManager::sharedState()->getPlayerShip() != 170) GameManager::sharedState()->setIntGameVariable("oldShipIcon", GameManager::sharedState()->getPlayerShip());//save oldShipIcon
            GameManager::sharedState()->setPlayerShip(170);
            player->toggleRobotMode(true);
            player->toggleFlyMode(true);
        }
        else if (self->m_nObjectType != kGameObjectTypeNormalGravityPortal && self->m_nObjectType != kGameObjectTypeInverseGravityPortal && self->m_nObjectType != kGameObjectTypeTeleportPortal) {
            GameManager::sharedState()->setPlayerShip(GameManager::sharedState()->getIntGameVariable("oldShipIcon"));//bring up by oldShipIcon
            if (self->m_nObjectID == 13 && PlayLayerMod::isSwingCopterMode) {
                player->toggleRobotMode(true);
                player->toggleFlyMode(true);
            }
            PlayLayerMod::isSwingCopterMode = false;
        }
    }
    //noGround
    if (self->m_nObjectType == kGameObjectTypeShipPortal || self->m_nObjectType == kGameObjectTypeCubePortal || self->m_nObjectType == kGameObjectTypeBallPortal || self->m_nObjectType == kGameObjectTypeUfoPortal || self->m_nObjectType == kGameObjectTypeWavePortal || self->m_nObjectType == kGameObjectTypeRobotPortal || self->m_nObjectType == kGameObjectTypeSpiderPortal) {
        //multiactive
        if (self->m_bRandomisedAnimStart)
        {
            self->m_bHasBeenActivated = false; self->m_bHasBeenActivatedP2 = false;
        }
        //animateOutGround
        if (self->m_fAnimSpeed > 0.49 && self->m_fAnimSpeed < 0.62)
            if (PlayLayerMod::PlayLayerMod::PlayLayerFromINit && player->m_isInPlayLayer) PlayLayerMod::PlayLayerFromINit->animateOutGround(!self->m_bHasBeenActivated);
        //enableTheCameraYFolow
        PlayLayerMod::enableTheCameraYFolow = bool(self->m_fAnimSpeed > 0.585f && self->m_fAnimSpeed < 0.612f);
        ModUtils::copyToClipboard(std::to_string(self->m_fAnimSpeed).c_str());
    }
    //multiactive bumps
    if (self->m_bRandomisedAnimStart && bool(self->m_nObjectID == 3005 || self->m_nObjectID == 35 || self->m_nObjectID == 140 || self->m_nObjectID == 1332 || self->m_nObjectID == 67))
    {
        self->m_bHasBeenActivated = false; self->m_bHasBeenActivatedP2 = false;
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
    if (self->m_nObjectID == 1931 && !self->m_bEditor) {
        PlayLayerMod::PlayLayerFromINit->levelComplete();
        PlayLayerMod::PlayLayerFromINit->m_hasCompletedLevel = true;
        PlayLayerMod::PlayLayerFromINit->moveCameraToPos({ self->m_obStartPosition.x - (CCDirector::sharedDirector()->getWinSize().width / 2), self->m_obStartPosition.y - (CCDirector::sharedDirector()->getWinSize().height / 2) });
        PlayerObj->m_playerSpeed = 0.0;
        PlayLayerMod::PlayLayerFromINit->playExitDualEffect(PlayerObj);
    }
    if (self->m_nObjectID == 1913) {
        float speed = 0.5;
        if (self->m_bRandomisedAnimStart) speed = self->m_fAnimSpeed;
        if (self->m_bEditor) baseGameLayer->m_pObjectLayer->runAction(CCEaseInOut::create(CCScaleTo::create(speed, self->m_fAnimSpeed), 2.00f));
        else {
            PlayLayerMod::PlayLayerFromINit->runAction(CCEaseInOut::create(CCScaleTo::create(speed, self->m_fAnimSpeed), 2.00f));
        }
    }
    if (self->m_nObjectID == 1934) {
        GameSoundManager::sharedState()->stopBackgroundMusic();
        if (!self->m_bEditor && self->m_bRandomisedAnimStart) PlayLayerMod::PlayLayerFromINit->startMusic();
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
    }
    //multiactive bumps
    if (bool(self->m_nObjectID == 3005 || self->m_nObjectID == 35 || self->m_nObjectID == 140 || self->m_nObjectID == 1332 || self->m_nObjectID == 67))
    {
        self->m_bIsEffectObject = true;
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

    //triggers
    if (self->m_nObjectID == 1913 || self->m_nObjectID == 1934) {
        self = reinterpret_cast<EffectGameObject*>(self);
        self->m_bIsEffectObject = true;
    }

    if (self->m_nObjectID == 1814) self->setDisplayFrame(cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(
        "edit_eCameraBtn_001.png"));
    if (self->m_nObjectID == 1817) self->setDisplayFrame(cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(
        "edit_e2.2Btn_001.png"));
    if (self->m_nObjectID == 1933 && self->displayFrame()->getRect().size.width < 45) {
        self->setDisplayFrame(cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(
            "portal_14_front_001.png"));
        self->runAction(CCRepeatForever::create(CCTintTo::create(0.0, 255, 255, 0)));
    }
}

GameObject* (__cdecl* objectFromString)(std::string, bool);
GameObject* objectFromString_H(std::string str, bool idk) {
    //GameObject* obj = objectFromString(str, idk);
    //if (obj->m_nObjectID == 1913) {
    //    //obj = reinterpret_cast<EffectGameObject*>(obj);
    //    //if (strstr(std::string(str).c_str(), "11,1")) obj->m_bTouchTriggered = true;
    //    obj->m_bIsGroupParent = true;
    //}
    //return obj;
    auto go = objectFromString(str, idk);
    if (go && go->m_nObjectID == 1913) {
        auto ego = reinterpret_cast<EffectGameObject*>(go);
        //if (strstr(std::string(str).c_str(), "11,1")) 
            ego->m_bTouchTriggered = true;
    }
    return go;
}

bool g_lock;
std::string (__stdcall* myGSaveString)(EffectGameObject*);
std::string myGSaveString_H(EffectGameObject* ego) {
    if (ego->m_nObjectID == 1913) {
        if (!g_lock) {
            g_lock = true;
            return myGSaveString(ego) + std::string("11,1");
        }
        g_lock = false;
    }
    return myGSaveString(ego);
}

void CreateObjectsThemedHooks() {
    HOOK(base + 0xEF0E0, GameObject_activateObject, true);
    HOOK(base + 0xd1c10, GameObject_customSetup, true);
    HOOK(base + 0xd1790, triggerObject, false);
    //HOOK(base + 0xEBE50, objectFromString, false);
    //HOOK(base + 0xed0c0, myGSaveString, false);
}
