#include "LevelAreaInnerLayer.hpp"
#include "LevelAreaLayer.hpp"
#include "../../curly-eureka/mod_utils.hpp"
#include <cocos2d.h>
#include <gd.h>

using namespace cocos2d;
using namespace gd;

CCRepeatForever* LevelAreaInnerLayer::getscaleact(float time, float scale)
{
    return CCRepeatForever::create(
        CCSequence::create(
            CCEaseInOut::create(CCScaleTo::create(time, scale), 2.0),
            CCDelayTime::create(0.1),
            CCEaseInOut::create(CCScaleBy::create(time, scale-0.2), 2.0),
            CCDelayTime::create(0.1),
            nullptr
        ));
}

CCRepeatForever* LevelAreaInnerLayer::getfadeact(float time, GLubyte vally1, GLubyte vally2)
{
    return CCRepeatForever::create(
        CCSequence::create(
            CCEaseInOut::create(CCFadeTo::create(time, vally1), 2.0),
            CCEaseInOut::create(CCFadeTo::create(time, vally2), 2.0),
            nullptr
        ));
}

CCSprite* LevelAreaInnerLayer::towerTorchInner()
{   
    CCSprite* Torch = CCSprite::create();
    //towerShine1 for fire of torch пон?
    CCSprite* torchShine = ModUtils::createSprite("towerShine.png");
    torchShine->setBlendFunc({ GL_SRC_ALPHA, GL_ONE });
    torchShine->setColor({ 255, 180, 20 });
    torchShine->setPosition({ 14.000, 38.000 });
    torchShine->runAction(getfadeact(1.5, 160, 110));
    torchShine->runAction(getscaleact(3.0, 1.4));
    Torch->addChild(torchShine);
    CCSprite* torchShine2 = ModUtils::createSprite("towerShine.png");
    torchShine2->setBlendFunc({ GL_SRC_ALPHA, GL_ONE });
    torchShine2->setColor({ 255, 180, 20 });
    torchShine2->setPosition({ 14.000, 38.000 });
    torchShine2->runAction(getfadeact(1.0, 120, 90));
    torchShine2->runAction(getscaleact(2.0, 1.5));
    Torch->addChild(torchShine2);
    //towerTorchInner_001
    CCSprite* towerTorchInner_001 = ModUtils::createSprite("towerTorchInner_001.png");
    towerTorchInner_001->setPosition({ 15.000, 22.000 });
    Torch->addChild(towerTorchInner_001);
    Torch->setContentSize(towerTorchInner_001->getContentSize());//dnt ask
    //fire for torch 💀
    CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    CCPoint firePos = CCPoint(15.500, 52.000);
    CCSprite* fire2 = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Fire_02_2_looped_001.png"));
    Torch->addChild(fire2);
    fire2->setPosition(firePos);
    fire2->setScale(1.800);
    fire2->setColor({ 255, 255, 10 });
    CCSprite* fire1 = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Fire_02_looped_001.png"));
    Torch->addChild(fire1);
    fire1->setPosition(firePos);
    fire1->setScale(0.900);
    fire1->setColor({ 255, 100, 0 });
    char str1[100] = { 0 };
    char str2[100] = { 0 };
    CCArray* animFrames1 = CCArray::createWithCapacity(9);
    CCArray* animFrames2 = CCArray::createWithCapacity(9);
    for (int i = 1; i < 9; ++i)
    {
        sprintf(str1, "Fire_02_looped_00%d.png", i);
        CCSpriteFrame* frame1 = cache->spriteFrameByName(str1);
        animFrames1->addObject(frame1);
        sprintf(str2, "Fire_02_2_looped_00%d.png", i);
        CCSpriteFrame* frame2 = cache->spriteFrameByName(str2);
        animFrames2->addObject(frame2);
    }
    CCAnimation* animation1 = CCAnimation::createWithSpriteFrames(animFrames1, 0.1);
    fire1->runAction(CCRepeatForever::create(CCAnimate::create(animation1)));
    CCAnimation* animation2 = CCAnimation::createWithSpriteFrames(animFrames2, 0.1);
    fire2->runAction(CCRepeatForever::create(CCAnimate::create(animation2)));
    return Torch;
}

//touch zone
CCMenu* createTouchZone(CCObject* rec, SEL_MenuHandler selector, CCSize contentSize)
{
    CCMenuItem* zone = CCMenuItem::create(rec, selector);
    zone->setContentSize(contentSize);
    return CCMenu::createWithItem(zone);
}

void LevelAreaInnerLayer::towerLevel1(CCObject* object)
{
    GameSoundManager::playEffect("door01.ogg");
    // Make Level
    auto level = gd::GJGameLevel::create();
    level->m_nLevelIndex = 385934;
    level->m_nLevelID_rand = 1070 + 5;
    level->m_nLevelID_seed = 5;
    level->m_nLevelID = 1070;
    level->m_sLevelName = "Unnamed 0C35";
    level->m_sCreatorName = "user666";
    level->m_nSongID = 345;
    level->m_bLevelNotDownloaded = true;
    level->m_eLevelType = gd::GJLevelType::kGJLevelTypeSaved;
    // Create Layer
    auto layer = gd::LevelInfoLayer::create(level);
    layer->downloadLevel();
    layer->setupProgressBars();
    auto scene = CCScene::create();
    scene->addChild(layer);
    CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5f, scene));
}

void LevelAreaInnerLayer::towerLevel2(CCObject* object)
{
    GameSoundManager::playEffect("door01.ogg");
    // Make Level
    auto level = gd::GJGameLevel::create();
    level->m_nLevelIndex = 385934;
    level->m_nLevelID_rand = 2049 + 5;
    level->m_nLevelID_seed = 5;
    level->m_nLevelID = 2049;
    level->m_sLevelName = "Synergy";
    level->m_sCreatorName = "TsuskaGD";
    level->m_nSongID = 134270;
    level->m_bLevelNotDownloaded = true;
    level->m_eLevelType = gd::GJLevelType::kGJLevelTypeSaved;
    // Create Layer
    auto layer = gd::LevelInfoLayer::create(level);
    layer->downloadLevel();
    layer->setupProgressBars();
    auto scene = CCScene::create();
    scene->addChild(layer);
    CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5f, scene));
}

void LevelAreaInnerLayer::towerLevel3(CCObject* object)
{
    GameSoundManager::playEffect("door01.ogg");
    // Make Level
    auto level = gd::GJGameLevel::create();
    level->m_nLevelIndex = 385934;
    level->m_nLevelID_rand = 632 + 5;
    level->m_nLevelID_seed = 5;
    level->m_nLevelID = 632;
    level->m_sLevelName = "SSIS";
    level->m_sCreatorName = "user666";
    level->m_nSongID = 345;
    level->m_bLevelNotDownloaded = true;
    level->m_eLevelType = gd::GJLevelType::kGJLevelTypeSaved;
    // Create Layer
    auto layer = gd::LevelInfoLayer::create(level);
    layer->downloadLevel();
    layer->setupProgressBars();
    auto scene = CCScene::create();
    scene->addChild(layer);
    CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5f, scene));
}

void LevelAreaInnerLayer::towerLevel4(CCObject* object)
{
    GameSoundManager::playEffect("door01.ogg");
    GameSoundManager::playEffect("chest08.ogg");
    // Make Level
    auto level = gd::GJGameLevel::create();
    level->m_nLevelIndex = 385934;
    level->m_nLevelID_rand = 21 + 5;
    level->m_nLevelID_seed = 5;
    level->m_nLevelID = 21;
    level->m_sLevelName = "Gear II v22";
    level->m_sCreatorName = "ScottXD";
    level->m_nUserID = 964;
    level->m_nSongID = 720222;
    level->m_bLevelNotDownloaded = true;
    level->m_eLevelType = gd::GJLevelType::kGJLevelTypeSaved;
    // Create Layer
    auto layer = gd::LevelInfoLayer::create(level);
    layer->downloadLevel();
    layer->setupProgressBars();
    auto scene = CCScene::create();
    scene->addChild(layer);
    CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5f, scene));
}

//LevelAreaInnerLayer* LevelAreaInnerLayer::create() {
//    auto ret = new LevelAreaInnerLayer();
//    if (ret && ret->init()) {
//        //robert 1 :D
//        ret->autorelease();
//    }
//    else {
//        //robert -1
//        delete ret;
//        ret = nullptr;
//    }
//    return ret;
//}
bool LevelAreaInnerLayer::init() {
    auto winSize = CCDirector::sharedDirector()->getWinSize();
    setTouchEnabled(true);
    setKeypadEnabled(true);

    auto moveact = CCRepeatForever::create(
        CCSequence::create(
            CCEaseInOut::create(CCMoveBy::create(3.0, { 0,4 }), 2.0),
            CCEaseInOut::create(CCMoveBy::create(3.0, { 0,-4 }), 2.0),
            nullptr
        ));

    //towerBG_01_001
    CCSprite* towerBG_01_001 = ModUtils::createSprite("towerBG_01_001.png");
    towerBG_01_001->setTag(666);
    addChild(towerBG_01_001);
    towerBG_01_001->setPosition({ winSize.width / 2, winSize.height / 2 });
    towerBG_01_001->runAction(moveact);
    towerBG_01_001->runAction(CCSequence::create(CCScaleTo::create(0.0, 0.000), CCEaseExponentialOut::create(CCScaleTo::create(1.0, 1.000))));
    //TouchZones
    CCMenu* runLevel1 = createTouchZone(this, menu_selector(LevelAreaInnerLayer::towerLevel1), CCSize(60.000, 60.000));
    runLevel1->setPosition({64.500,42.000});
    towerBG_01_001->addChild(runLevel1, 1);
    CCMenu* runLevel2 = createTouchZone(this, menu_selector(LevelAreaInnerLayer::towerLevel2), CCSize(60.000, 60.000));
    runLevel2->setPosition({ 263.000,98.000 });
    towerBG_01_001->addChild(runLevel2, 1);
    CCMenu* runLevel3 = createTouchZone(this, menu_selector(LevelAreaInnerLayer::towerLevel3), CCSize(60.000, 60.000));
    runLevel3->setPosition({ 64.500,148.000 });
    towerBG_01_001->addChild(runLevel3, 1);
    CCMenu* runLevel4 = createTouchZone(this, menu_selector(LevelAreaInnerLayer::towerLevel4), CCSize(60.000, 60.000));
    runLevel4->setPosition({ 216.500,210.000 });
    towerBG_01_001->addChild(runLevel4, 1);
    //addTourches
    CCSprite* towerTorchInner1 = towerTorchInner();
    towerTorchInner1->setPosition({ -38.000, 136.000 });
    towerBG_01_001->addChild(towerTorchInner1);
    CCSprite* towerTorchInner2 = towerTorchInner();
    towerTorchInner2->setPosition({ 358.000, 136.000 });
    towerBG_01_001->addChild(towerTorchInner2);

    //BACK BTN GJ_arrow_03_001.png
    CCMenuItemSpriteExtra* backItem = CCMenuItemSpriteExtra::create(ModUtils::createSprite("GJ_arrow_03_001.png"), this, menu_selector(LevelAreaInnerLayer::onBack));
    backItem->setPosition({ 25, winSize.height - 25 });
    addChild(CCMenu::createWithItem(backItem));
    CCMenu* backMenu = (CCMenu*)backItem->getParent();
    backMenu->setPosition({ 0,0 });

    //wtf
    //runAction(CCRepeatForever::create(CCSequence::create(CCCallFunc::create(this, SEL_CallFunc(&LevelAreaInnerLayer::updateDoors)), nullptr)));
    this->scheduleUpdate();

    return true;
}

void LevelAreaInnerLayer::keyBackClicked() {
    auto layer = LevelAreaLayer::create();
    auto scene = CCScene::create();
    scene->addChild(layer);
    CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5f, scene));
}

void LevelAreaInnerLayer::onBack(CCObject* object) {
    keyBackClicked();
}