// 22_PC_GDPS_MAIN.cpp: определяет точку входа для приложения.
//
#include "22_PC_GDPS_MAIN.h"

bool hooksLoaded = false;
int oldShipIcon;

void ModBase::ondontgiveashit(cocos2d::CCObject*) {
    idontgiveashitbro = (!idontgiveashitbro);
    CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5f, MenuLayer::scene(0)));
    GameSoundManager::sharedState()->playEffect("quitSound_01.ogg");
}
void ModBase::msg(CCLayer* self, const char* redText, const char* customMsg) {
    CCLabelTTF* msg = CCLabelTTF::create(
        "OBJECT HASN'T FOUNDED\nseems u delete or add some mods\n\n that prevent getting objects\n in this layer",
        "Comic Sans MS",
        120.0f);
    if (customMsg != "") msg = CCLabelTTF::create(customMsg, "Comic Sans MS", 80.0f);
    msg->setPosition(ModUtils::getCenterPoint());
    msg->setScale(0.150f);//120.0f for lbl fontSize
    CCLabelTTF* msg2 = CCLabelTTF::create(redText, "Comic Sans MS", 120.0f);
    msg2->setPosition({ msg->getContentSize().width / 2,  msg->getContentSize().height / 2 });
    msg2->setColor({ 255, 70, 70 });
    msg->addChild(msg2);
    if (!idontgiveashitbro) self->removeAllChildren(); //:trollface:
    if (!idontgiveashitbro) self->addChild(msg, 666, 666);
    if (!idontgiveashitbro) GameManager::sharedState()->fadeInMusic("shop3.mp3");
    CCMenu* dontgiveashit = CCMenu::createWithItem(
        CCMenuItemSpriteExtra::create(
            ButtonSprite::create("i dont give a shit, bro", 80, false, "gjFont06.fnt", "GJ_button_05.png", 30, 5.0f),
            self,
            menu_selector(ModBase::ondontgiveashit)
        )
    );
    dontgiveashit->setPositionY(dontgiveashit->getPositionY() - 120.0f);
    if (!idontgiveashitbro) self->addChild(dontgiveashit);
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
    //SetupAnimSettingsPopup
    if("SetupAnimSettingsPopup") {
        if (std::string(str) == "Edit Animation Settings") {
            if (LevelEditor::LevelEditor::lastSelectedObj->m_nObjectID == 3004 || LevelEditor::lastSelectedObj->m_nObjectID == 3005 //spider orb anda pad
                || LevelEditor::lastSelectedObj->m_nObjectID == 35 || LevelEditor::lastSelectedObj->m_nObjectID == 140 || LevelEditor::lastSelectedObj->m_nObjectID == 1332 || LevelEditor::lastSelectedObj->m_nObjectID == 67 //bumps
                || LevelEditor::lastSelectedObj->m_nObjectType == kGameObjectTypeShipPortal || LevelEditor::lastSelectedObj->m_nObjectType == kGameObjectTypeCubePortal || LevelEditor::lastSelectedObj->m_nObjectType == kGameObjectTypeBallPortal || LevelEditor::lastSelectedObj->m_nObjectType == kGameObjectTypeUfoPortal || LevelEditor::lastSelectedObj->m_nObjectType == kGameObjectTypeWavePortal || LevelEditor::lastSelectedObj->m_nObjectType == kGameObjectTypeRobotPortal || LevelEditor::lastSelectedObj->m_nObjectType == kGameObjectTypeSpiderPortal //noground portals
                || LevelEditor::lastSelectedObj->m_nObjectID == 1934 //song trigger
                )
                str = "Object setup";
            if (LevelEditor::lastSelectedObj->m_nObjectID == 1913)
                str = "Zoom thing setup...";
        }
        if (std::string(str) == "Speed: ") {
            if (LevelEditor::lastSelectedObj->m_nObjectID == 3004 || LevelEditor::lastSelectedObj->m_nObjectID == 3005 || LevelEditor::lastSelectedObj->m_nObjectID == 3005  //spider orb anda pad
                || LevelEditor::lastSelectedObj->m_nObjectID == 35 || LevelEditor::lastSelectedObj->m_nObjectID == 140 || LevelEditor::lastSelectedObj->m_nObjectID == 1332 || LevelEditor::lastSelectedObj->m_nObjectID == 67 //bumps
                || LevelEditor::lastSelectedObj->m_nObjectID == 1934 //song trigger
                )
                str = "(No features)";
            if (LevelEditor::lastSelectedObj->m_nObjectType == kGameObjectTypeShipPortal || LevelEditor::lastSelectedObj->m_nObjectType == kGameObjectTypeCubePortal || LevelEditor::lastSelectedObj->m_nObjectType == kGameObjectTypeBallPortal || LevelEditor::lastSelectedObj->m_nObjectType == kGameObjectTypeUfoPortal || LevelEditor::lastSelectedObj->m_nObjectType == kGameObjectTypeWavePortal || LevelEditor::lastSelectedObj->m_nObjectType == kGameObjectTypeRobotPortal || LevelEditor::lastSelectedObj->m_nObjectType == kGameObjectTypeSpiderPortal) //noground portals
                str = "Feature id: ";
            if (LevelEditor::lastSelectedObj->m_nObjectID == 1913)
                str = "Scale: ";
        }
        if (std::string(str) == "Randomize Start") {
            if (LevelEditor::lastSelectedObj->m_nObjectID == 3004 || LevelEditor::lastSelectedObj->m_nObjectID == 3005 //spider orb anda pad
                || LevelEditor::lastSelectedObj->m_nObjectID == 35 || LevelEditor::lastSelectedObj->m_nObjectID == 140 || LevelEditor::lastSelectedObj->m_nObjectID == 1332 || LevelEditor::lastSelectedObj->m_nObjectID == 67 || LevelEditor::lastSelectedObj->m_nObjectType == kGameObjectTypeInverseGravityPortal || LevelEditor::lastSelectedObj->m_nObjectType == kGameObjectTypeNormalGravityPortal
                || LevelEditor::lastSelectedObj->m_nObjectType == kGameObjectTypeShipPortal || LevelEditor::lastSelectedObj->m_nObjectType == kGameObjectTypeCubePortal || LevelEditor::lastSelectedObj->m_nObjectType == kGameObjectTypeBallPortal || LevelEditor::lastSelectedObj->m_nObjectType == kGameObjectTypeUfoPortal || LevelEditor::lastSelectedObj->m_nObjectType == kGameObjectTypeWavePortal || LevelEditor::lastSelectedObj->m_nObjectType == kGameObjectTypeRobotPortal || LevelEditor::lastSelectedObj->m_nObjectType == kGameObjectTypeSpiderPortal //noground portals
                ) str = "Allow multi activate";
            if (LevelEditor::lastSelectedObj->m_nObjectID == 1913)
                str = "Take Scale for\n duration also :p";
            if (LevelEditor::lastSelectedObj->m_nObjectID == 1934)
                str = "Restart music";
            return CCLabelBMFont::create(str, fntFile, 220, kCCTextAlignmentCenter);
        }
        if (std::string(str) == "Animation settings help" && std::string(fntFile) == "chatFont.fnt") {
            CCLabelBMFont* lbl = CCLabelBMFont::create("", "chatFont.fnt", 435, kCCTextAlignmentCenter);
            std::string info = "";
            if (LevelEditor::lastSelectedObj->m_nObjectID == 3004 || LevelEditor::lastSelectedObj->m_nObjectID == 3005)
                info = "Allows multi activate feature.\nNote: set up first groundHeight(first 2 grounds gamemode) \nto reduce bugs with cube or robot";
            if (LevelEditor::lastSelectedObj->m_nObjectID == 35 || LevelEditor::lastSelectedObj->m_nObjectID == 140 || LevelEditor::lastSelectedObj->m_nObjectID == 1332 || LevelEditor::lastSelectedObj->m_nObjectID == 67)
                info = "Allows multi activate feature.";
            if (LevelEditor::lastSelectedObj->m_nObjectType == kGameObjectTypeShipPortal || LevelEditor::lastSelectedObj->m_nObjectType == kGameObjectTypeCubePortal || LevelEditor::lastSelectedObj->m_nObjectType == kGameObjectTypeBallPortal || LevelEditor::lastSelectedObj->m_nObjectType == kGameObjectTypeUfoPortal || LevelEditor::lastSelectedObj->m_nObjectType == kGameObjectTypeWavePortal || LevelEditor::lastSelectedObj->m_nObjectType == kGameObjectTypeRobotPortal || LevelEditor::lastSelectedObj->m_nObjectType == kGameObjectTypeSpiderPortal)
                info = "0.50: Just will animate out grounds when enter portal\n0.60: Toggle camera follow (crazy shit) and animate out grounds";//noGround
            if (LevelEditor::lastSelectedObj->m_nObjectID == 1913)
                info = "No"; 
            if (LevelEditor::lastSelectedObj->m_nObjectID == 1934)
                info = "Can restart or stop music";
            lbl->setString(std::string("                      \n" + info + "\n\n\n ").c_str());
            if (info != "") return lbl;
        }
    }
    return CCLabelBMFont_create(str, fntFile);
}

DWORD WINAPI thread_func(void* hModule) {
    LoadLibrary("cocos-explorer.dll");

    // initialize minhook
    MH_Initialize();

    HOOK(base + 0x18C8E0, LoadingLayer_loadAssets, true);
    
    CC_HOOK("?create@CCSprite@cocos2d@@SAPAV12@PBD@Z", CCSprite_create, false);
    CC_HOOK("?createWithSpriteFrameName@CCSprite@cocos2d@@SAPAV12@PBD@Z", CCSprite_createWithSpriteFrameName, false);
    CC_HOOK("?create@CCLabelBMFont@cocos2d@@SAPAV12@PBD0@Z", CCLabelBMFont_create, false);

    CreatePlayLayerHooks();
    CreatePlayerObjectHooks();
    CreateObjectsThemedHooks();
    CreateOtherLayersHooks();
    CreateLevelEditorHooks();

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