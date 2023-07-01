#include "customLayerxd.h"
#include "../../curly-eureka/mod_utils.hpp"

using namespace gd;
using namespace cocos2d;

customLayerxd* customLayerxd::create() {
    auto ret = new customLayerxd();
    if (ret && ret->init()) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

void customLayerxd::keyBackClicked() {
    CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5f, MenuLayer::scene(0)));
    GameManager::sharedState()->fadeInMusic("menuLoop.mp3");
}

void customLayerxd::openURLcredits(CCObject* sender) { CCApplication::sharedApplication()->openURL("http://gdps22pc.webq2e.ru/credits.php"); }

void customLayerxd::gamejolt_openURL(CCObject* sender) { CCApplication::sharedApplication()->openURL("https://gamejolt.com/games/gdps22pc/776434"); }
void customLayerxd::openURL(CCObject* sender) { CCApplication::sharedApplication()->openURL("http://gdps22pc.webq2e.ru"); }
void customLayerxd::discord_openURL(CCObject* sender) { CCApplication::sharedApplication()->openURL("https://discord.io/GDPS-22-PC+"); }
void customLayerxd::vk_openURL(CCObject* sender) { CCApplication::sharedApplication()->openURL("https://vk.com/gdps22pc"); }
void customLayerxd::yt_openURL(CCObject* sender) { CCApplication::sharedApplication()->openURL("https://youtube.com/playlist?list=PLW0TbCFqUWlye2KpSxx357r7v08t-2LZR"); }

void customLayerxd::onBack(CCObject* object) {
    keyBackClicked();
}

bool customLayerxd::init() {
    auto winSize = CCDirector::sharedDirector()->getWinSize();

    GameManager::sharedState()->fadeInMusic("Embers.mp3");

    auto backgroundSprite = ModUtils::createSprite("shopBG_001.png");
    auto size = backgroundSprite->getContentSize();
    backgroundSprite->setScaleX(winSize.width / size.width);
    backgroundSprite->setScaleY(winSize.height / size.height);
    backgroundSprite->setAnchorPoint({ 0, 0 });
    backgroundSprite->setPosition({ 0,0 });
    backgroundSprite->setZOrder(-2);
    addChild(backgroundSprite);

    auto backBtn = gd::CCMenuItemSpriteExtra::create(
        ModUtils::createSprite("GJ_arrow_03_001.png"),
        this,
        menu_selector(customLayerxd::onBack)
    );

    auto menuBack = CCMenu::createWithItem(backBtn);
    menuBack->setPosition({25, winSize.height - 25});
    addChild(menuBack);

    setKeypadEnabled(true);


    auto menuInLtopBtns = CCMenu::create();
    menuInLtopBtns->setPosition({ 35, winSize.height - 105 });
    addChild(menuInLtopBtns);

    //creaditsLnk
    auto creditsLnk = gd::CCMenuItemSpriteExtra::create(
        ModUtils::createSprite("communityCreditsBtn_001.png"),
        this,
        menu_selector(customLayerxd::openURLcredits)
    );
    menuInLtopBtns->addChild(creditsLnk);
    
    menuInLtopBtns->alignItemsVerticallyWithPadding(8);

    //bese yp
    auto Mod_logo_001 = ModUtils::createSprite("Mod_logo_001.png");
    Mod_logo_001->setPosition({ winSize.width / 2, winSize.height - 50 });
    addChild(Mod_logo_001);
    auto txt1 = CCLabelBMFont::create("At first, this is mod and private server for Geometry Dash.\nBasically a combination of mods by others and own,\n besides adding mechanics was modified game and its resources.\nThis mod basically aimed to recreate known features from 2.2 update(currently in dev).\nBased on Geometry Dash 2.2 Recreation v2.0 (before update 1.7 was taken v1.1)\n by elSai and GenaMorphosis.\n Server and other improvements by user666 (anda he is owner).", "chatFont.fnt");
    txt1->setPosition({ winSize.width / 2, winSize.height / 2 });
    txt1->setScale(0.8f);
    txt1->setAlignment(kCCTextAlignmentCenter);
    addChild(txt1);

    //gamegamejoltLnk
    auto gamegamejoltLnk = CCMenuItemSpriteExtra::create(
        CCLabelBMFont::create("GAME", "gjFont02.fnt"),
        this,
        menu_selector(customLayerxd::gamejolt_openURL)
    );
    auto gamegamejoltLnkPt2 = CCLabelBMFont::create("JOLT", "gjFont02.fnt");
    gamegamejoltLnkPt2->setColor(ccc3(191, 255, 0));
    gamegamejoltLnkPt2->setAnchorPoint({ -1.3f, 0 });
    gamegamejoltLnk->setContentSize({ 172, 33 });
    gamegamejoltLnk->addChild(gamegamejoltLnkPt2);
    auto gamegamejoltLnkMenu = CCMenu::createWithItem(gamegamejoltLnk);
    gamegamejoltLnkMenu->setPosition({ winSize.width / 2, 55 });
    addChild(gamegamejoltLnkMenu);

    //links
    auto linksMenu = CCMenu::create();

    auto user666_siteIcon_001 = ModUtils::createSprite("user666_siteIcon_001.png");
    auto openURLbtn = gd::CCMenuItemSpriteExtra::create(
        user666_siteIcon_001,
        this,
        menu_selector(customLayerxd::openURL)
    );
    auto lastXpos = openURLbtn->getPositionX();
    linksMenu->addChild(openURLbtn);

    auto gj_discordIcon_001 = ModUtils::createSprite("gj_discordIcon_001.png");
    auto discord_openURLbtn = gd::CCMenuItemSpriteExtra::create(
        gj_discordIcon_001,
        this,
        menu_selector(customLayerxd::discord_openURL)
    );
    discord_openURLbtn->setPosition({ 0, -30 });
    linksMenu->addChild(discord_openURLbtn);

    auto user666_vkIcon_001 = ModUtils::createSprite("user666_vkIcon_001.png");
    auto vk_openURLbtn = gd::CCMenuItemSpriteExtra::create(
        user666_vkIcon_001,
        this,
        menu_selector(customLayerxd::vk_openURL)
    );
    vk_openURLbtn->setPosition({ 0, -30 });
    linksMenu->addChild(vk_openURLbtn);

    auto gj_ytIcon_001 = ModUtils::createSprite("gj_ytIcon_001.png");
    auto yt_openURLbtn = gd::CCMenuItemSpriteExtra::create(
        gj_ytIcon_001,
        this,
        menu_selector(customLayerxd::yt_openURL)
    );
    yt_openURLbtn->setPosition({ 0, -30 });
    linksMenu->addChild(yt_openURLbtn);

    linksMenu->setPosition({ winSize.width / 2, 22 });
    linksMenu->alignItemsHorizontallyWithPadding(5);
    addChild(linksMenu);

    auto treasureRoomSpiderweb_001 = ModUtils::createSprite("treasureRoomSpiderweb_001.png");
    treasureRoomSpiderweb_001->setPosition({ winSize.width,winSize.height });
    treasureRoomSpiderweb_001->setColor({ 240,240,240 }); treasureRoomSpiderweb_001->setOpacity(160);
    treasureRoomSpiderweb_001->setAnchorPoint({ 0.95f,0.95f });
    treasureRoomSpiderweb_001->setScale(1.2f);
    addChild(treasureRoomSpiderweb_001, 5);

    return true;
}

void customLayerxd::switchcustomLayerxdbtn(CCObject* object) {
    auto layer = customLayerxd::create();
    auto scene = CCScene::create();
    scene->addChild(layer);
    auto transition = CCTransitionMoveInT::create(0.5f, scene);
    CCDirector::sharedDirector()->pushScene(transition);
}