#include "OtherLayers.hpp"

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
        addclbtn("GJ_createBtn_001.png", menu_selector(CreatorLayer::onMyLevels), { -180,90 }, menu);
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
    else ModBase::msg(self, "msvcr180.dll (or Sai.dll by old version)");
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
        if (responseString != ModBase::version || !strstr(ModBase::version, "pre")) {
            AchievementNotifier::sharedState()->notifyAchievement("Update available!", ("You can download actual " + responseString + " version on the website.").c_str(), "GJ_downloadsIcon_001.png", true);
        }
    }
};
inline bool(__thiscall* MenuLayer_init)(MenuLayer*);
bool __fastcall MenuLayer_init_H(MenuLayer* self) {
    if (!MenuLayer_init(self)) return false;

    CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    //self->runAction(CCSequence::create(CCDelayTime::create(0.1f), CCCallFuncO::create(self, callfuncO_selector(MenuLayerMod::termsOfUseLayerShow), self), nullptr));

    auto versionLabel = CCLabelBMFont::create(ModBase::version, "chatFont.fnt");
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
    else ModBase::msg(self, "msvcr180.dll (or Sai.dll by old version)");
    //and then otrer shit from SaiModPack.dll
    CCLayer* SaiModPackThings = (CCLayer*)self->getChildren()->objectAtIndex(0);
    if (SaiModPackThings->getZOrder() == 100) SaiModPackThings->removeFromParent();
    else ModBase::msg(self, "SaiModPack.dll");
    //gdshare noitce
    if (CCFileUtils::sharedFileUtils()->isFileExist("mods/GDShare-v0.3.4.dll") ||
        CCFileUtils::sharedFileUtils()->isFileExist("mods/GDShare.dll") ||
        CCFileUtils::sharedFileUtils()->isFileExist("GDShare-v0.3.4.dll")
        ) ModBase::msg(self, "Seems you installed GDShare\nGDShare is unstable with sai's mods,\nyou can get game crash", " ");

    GameManager::sharedState()->setPlayerShip(GameManager::sharedState()->getIntGameVariable("oldShipIcon"));//bring up by oldShipIcon
    return true;
}

inline bool(__cdecl* GJGarageLayer_init)(GJGarageLayer*);
bool __fastcall GJGarageLayer_init_H(GJGarageLayer* self) {
    if (!GJGarageLayer_init(self)) return false;
    self->removeChild((CCLayer*)self->getChildren()->objectAtIndex(0)); //remove some idk nn random corners
    CCLayer* saimodpacklayer = (CCLayer*)self->getChildren()->objectAtIndex(7); //this is carazy shit 7
    if (saimodpacklayer->getZOrder() == 1000) saimodpacklayer->getChildren()->removeLastObject();//remove socials 
    else ModBase::msg(self, "SaiModPack.dll");
    CCMenu* menu = (CCMenu*)self->getChildren()->objectAtIndex(19); //this is carazy shit 19
    if (menu->getChildrenCount() == 5) {
        menu->getChildren()->removeLastObject();//remove infbtn
        menu->getChildren()->removeLastObject();//and remove colorsBtn
    }
    else ModBase::msg(self);
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

void CreateOtherLayersHooks() {
    HOOK(base + 0x1907B0, MenuLayer_init, false);
    //HOOK(base + 0x191b50, MenuLayer_onPlay, false);
    HOOK(base + 0x4DE40, CreatorLayer_init, false);
    HOOK(base + 0x1255D0, GJGarageLayer_init, false);
    HOOK(base + 0x12ADF0, GJGarageLayer_onBack, false);

    HOOK(base + 0x154560, KeysLayer_init, true);
    HOOK(base + 0x1DE8F0, MoreOptionsLayer_init, true);
    HOOK(base + 0x25C7B0, SupportLayer_customSetup, true);
    HOOK(base + 0x6a900, DailyLevelPage_init, true);
    HOOK(base + 0x210040, ProfilePage_loadPageFromUserInfo, true);
}
