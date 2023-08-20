#include "Objects.hpp"

inline void(__thiscall* GameObject_activateObject)(GameObject*, PlayerObject*);
void __fastcall GameObject_activateObject_H(GameObject* self, int, PlayerObject* player) {
    GameObject_activateObject(self, player);
    if ("SwingCopter") {
        if (self->m_nObjectID == 1933) {
            PlayLayerExt::isSwingCopterMode = true;
            if (GameManager::sharedState()->getPlayerShip() != 170) GameManager::sharedState()->setIntGameVariable("oldShipIcon", GameManager::sharedState()->getPlayerShip());//save oldShipIcon
            GameManager::sharedState()->setPlayerShip(170);
            player->toggleRobotMode(true);
            player->toggleFlyMode(true);
        }
        else if (self->m_nObjectType != kGameObjectTypeNormalGravityPortal && self->m_nObjectType != kGameObjectTypeInverseGravityPortal && self->m_nObjectType != kGameObjectTypeTeleportPortal) {
            GameManager::sharedState()->setPlayerShip(GameManager::sharedState()->getIntGameVariable("oldShipIcon"));//bring up by oldShipIcon
            if (self->m_nObjectID == 13 && PlayLayerExt::isSwingCopterMode) {
                player->toggleRobotMode(true);
                player->toggleFlyMode(true);
            }
            PlayLayerExt::isSwingCopterMode = false;
        }
    }
    if (self->m_nObjectType == kGameObjectTypeShipPortal || self->m_nObjectType == kGameObjectTypeCubePortal || self->m_nObjectType == kGameObjectTypeBallPortal || self->m_nObjectType == kGameObjectTypeUfoPortal || self->m_nObjectType == kGameObjectTypeWavePortal || self->m_nObjectType == kGameObjectTypeRobotPortal || self->m_nObjectType == kGameObjectTypeSpiderPortal) {
        //multiactive
        if (self->m_bRandomisedAnimStart)
        {
            self->m_bHasBeenActivated = false; self->m_bHasBeenActivatedP2 = false;
        }
        //animateOutGround
        if (self->m_fAnimSpeed > 0.49 && self->m_fAnimSpeed < 0.62)
            if (PlayLayerExt::PlayLayerFromINit && player->m_isInPlayLayer) {
                PlayLayerExt::PlayLayerFromINit->animateOutGround(!self->m_bHasBeenActivated);
            }
        if (self->m_nObjectType == kGameObjectTypeCubePortal || self->m_nObjectType == kGameObjectTypeRobotPortal || !bool(self->m_fAnimSpeed > 0.49 && self->m_fAnimSpeed < 0.62)) {
            if (PlayLayerExt::freeMode && player->m_isInPlayLayer)
            {
            PlayLayerExt::freeMode = false;
            PlayLayerExt::PlayLayerFromINit->m_bIsDualMode = false;
            player->flipGravity(false, false);
            self->m_bHasBeenActivated = false; self->m_bHasBeenActivatedP2 = false;
            PlayLayerExt::PlayLayerFromINit->animateOutGround(true);
            if(!bool(self->m_nObjectType == kGameObjectTypeCubePortal || self->m_nObjectType == kGameObjectTypeRobotPortal))
                PlayLayerExt::PlayLayerFromINit->animateInGround(true);
            }
        }
        else PlayLayerExt::freeMode = bool(self->m_fAnimSpeed > 0.49 && self->m_fAnimSpeed < 0.62);
        //ModUtils::copyToClipboard(std::to_string(self->m_fAnimSpeed).c_str());
    }
    //other multiactive
    if (self->m_bRandomisedAnimStart && bool(self->m_nObjectID == 3005 || self->m_nObjectID == 35 || self->m_nObjectID == 140 || self->m_nObjectID == 1332 || self->m_nObjectID == 67 || self->m_nObjectType==kGameObjectTypeInverseGravityPortal ||self->m_nObjectType == kGameObjectTypeNormalGravityPortal))
    {
        self->m_bHasBeenActivated = false; self->m_bHasBeenActivatedP2 = false;
    }
    //ModUtils::copyToClipboard(std::string(std::to_string(self->m_obObjectSize.width) + "," + std::to_string(self->m_obObjectSize.height)).c_str());
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
        PlayLayerExt::PlayLayerFromINit->levelComplete();
        PlayLayerExt::PlayLayerFromINit->m_hasCompletedLevel = true;
        PlayLayerExt::PlayLayerFromINit->moveCameraToPos({ self->m_obStartPosition.x - (CCDirector::sharedDirector()->getWinSize().width / 2), self->m_obStartPosition.y - (CCDirector::sharedDirector()->getWinSize().height / 2) });
        PlayerObj->m_playerSpeed = 0.0;
        PlayLayerExt::PlayLayerFromINit->playExitDualEffect(PlayerObj);
    }
    if (self->m_nObjectID == 1913) {
        float speed = 0.5;
        if (self->m_bRandomisedAnimStart) speed = self->m_fAnimSpeed;
        baseGameLayer->m_pObjectLayer->runAction(CCEaseInOut::create(CCScaleTo::create(speed, self->m_fAnimSpeed), 2.00f));
    }
    if (self->m_nObjectID == 1934) {
        GameSoundManager::sharedState()->stopBackgroundMusic();
        if (!self->m_bEditor && self->m_bRandomisedAnimStart) PlayLayerExt::PlayLayerFromINit->startMusic();
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
    if (self->m_nObjectType == kGameObjectTypeShipPortal || self->m_nObjectType == kGameObjectTypeCubePortal || self->m_nObjectType == kGameObjectTypeBallPortal || self->m_nObjectType == kGameObjectTypeUfoPortal || self->m_nObjectType == kGameObjectTypeWavePortal || self->m_nObjectType == kGameObjectTypeRobotPortal || self->m_nObjectType == kGameObjectTypeSpiderPortal)
        self->m_bIsEffectObject = true;
    //multiactive
    if (bool(self->m_nObjectID == 3005 || self->m_nObjectID == 35 || self->m_nObjectID == 140 || self->m_nObjectID == 1332 || self->m_nObjectID == 67 || self->m_nObjectType == kGameObjectTypeInverseGravityPortal || self->m_nObjectType == kGameObjectTypeNormalGravityPortal))
        self->m_bIsEffectObject = true;

    if (self->m_nObjectID == 3004) {//spider ring
        //main setups
        self->m_nObjectType = kGameObjectTypePinkJumpRing;
        self->m_pBaseColor->defaultColorID = 1011;
        self->m_bIsEffectObject = true;

    }
    if (self->m_nObjectID == 3005) {//spider pad
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

    if (self->m_sTextureName.find("pixelart_") != self->m_sTextureName.npos) {//any pixel art
        self->m_nObjectType = kGameObjectTypeDecoration;
    }
    if (self->m_sTextureName.find("blockPiece_") != self->m_sTextureName.npos) {//any blockPiece
        self->m_nObjectType = kGameObjectTypeDecoration;
    }

    if (self->m_nObjectID == 2926) {//green portal
        self->m_nObjectType = GameObjectType::kGameObjectTypeGreenRing;
        self->setAnchorPoint(CCPoint(self->getAnchorPoint().x - 0.1, self->getAnchorPoint().y - 0.001));// totally :smiling_face_with_tear:
        self->m_obObjectSize.setSize(25.000000, 75.000000);
        self->m_bIsEffectObject = true;
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
    if (self->m_sTextureName.find("portal_19") != self->m_sTextureName.npos && self->m_bEditor) {
        self->setDisplayFrame(cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(
            "portal_19_front_001.png"));
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

    ObjectToolbox::sharedState()->addObject(3004, "spiderRing_001.png");
    ObjectToolbox::sharedState()->addObject(3005, "spiderBump_001.png");
    ObjectToolbox::sharedState()->addObject(2926, "portal_19_unity_001.png");

    ObjectToolbox::sharedState()->addObject(1964, "blockPiece_001_001.png");
    ObjectToolbox::sharedState()->addObject(1965, "blockPiece_002_001.png");
    ObjectToolbox::sharedState()->addObject(1966, "blockPiece_003_001.png");
    ObjectToolbox::sharedState()->addObject(1967, "blockPiece_004_001.png");
    ObjectToolbox::sharedState()->addObject(1968, "blockPiece_005_001.png");
    ObjectToolbox::sharedState()->addObject(1969, "blockPiece_006_001.png");
    ObjectToolbox::sharedState()->addObject(1970, "blockPiece_007_001.png");
    ObjectToolbox::sharedState()->addObject(1971, "blockPiece_008_001.png");
    ObjectToolbox::sharedState()->addObject(1972, "blockPiece_009_001.png");
    ObjectToolbox::sharedState()->addObject(1973, "blockPiece_010_001.png");
    ObjectToolbox::sharedState()->addObject(1974, "blockPiece_011_001.png");
    ObjectToolbox::sharedState()->addObject(1975, "blockPiece_012_001.png");
    ObjectToolbox::sharedState()->addObject(1976, "blockPiece_013_001.png");
    ObjectToolbox::sharedState()->addObject(1977, "blockPiece_014_001.png");
    ObjectToolbox::sharedState()->addObject(1978, "blockPiece_015_001.png");
    ObjectToolbox::sharedState()->addObject(1979, "blockPiece_016_001.png");
    ObjectToolbox::sharedState()->addObject(1980, "blockPiece_017_001.png");
    ObjectToolbox::sharedState()->addObject(1981, "blockPiece_018_001.png");
    ObjectToolbox::sharedState()->addObject(1982, "blockPiece_019_001.png");
    ObjectToolbox::sharedState()->addObject(1983, "blockPiece_020_001.png");
    ObjectToolbox::sharedState()->addObject(1984, "blockPiece_021_001.png");
    ObjectToolbox::sharedState()->addObject(1985, "blockPiece_022_001.png");
    ObjectToolbox::sharedState()->addObject(1986, "blockPiece_023_001.png");
    ObjectToolbox::sharedState()->addObject(1987, "blockPiece_024_001.png");

    ObjectToolbox::sharedState()->addObject(1988, "blockPiece_small_001_001.png");
    ObjectToolbox::sharedState()->addObject(1989, "blockPiece_small_002_001.png");
    ObjectToolbox::sharedState()->addObject(1990, "blockPiece_small_003_001.png");
    ObjectToolbox::sharedState()->addObject(1991, "blockPiece_small_004_001.png");
    ObjectToolbox::sharedState()->addObject(1992, "blockPiece_small_005_001.png");
    ObjectToolbox::sharedState()->addObject(1993, "blockPiece_small_006_001.png");
    ObjectToolbox::sharedState()->addObject(1994, "blockPiece_small_007_001.png");
    ObjectToolbox::sharedState()->addObject(1995, "blockPiece_small_008_001.png");
    ObjectToolbox::sharedState()->addObject(1996, "blockPiece_small_009_001.png");
    ObjectToolbox::sharedState()->addObject(1997, "blockPiece_small_010_001.png");
    ObjectToolbox::sharedState()->addObject(1998, "blockPiece_small_011_001.png");
    ObjectToolbox::sharedState()->addObject(1999, "blockPiece_small_012_001.png");
    ObjectToolbox::sharedState()->addObject(2000, "blockPiece_small_013_001.png");
    ObjectToolbox::sharedState()->addObject(2001, "blockPiece_small_014_001.png");
    ObjectToolbox::sharedState()->addObject(2002, "blockPiece_small_015_001.png");
    ObjectToolbox::sharedState()->addObject(2003, "blockPiece_small_016_001.png");
    ObjectToolbox::sharedState()->addObject(2004, "blockPiece_small_017_001.png");
    ObjectToolbox::sharedState()->addObject(2005, "blockPiece_small_018_001.png");
    ObjectToolbox::sharedState()->addObject(2006, "blockPiece_small_019_001.png");
    ObjectToolbox::sharedState()->addObject(2007, "blockPiece_small_020_001.png");
    ObjectToolbox::sharedState()->addObject(2008, "blockPiece_small_021_001.png");
    ObjectToolbox::sharedState()->addObject(2009, "blockPiece_small_022_001.png");
    ObjectToolbox::sharedState()->addObject(2010, "blockPiece_small_023_001.png");
    ObjectToolbox::sharedState()->addObject(2011, "blockPiece_small_024_001.png");
}
