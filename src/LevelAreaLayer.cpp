#include "LevelAreaLayer.hpp"
#include "LevelAreaInnerLayer.hpp"
#include "../../curly-eureka/mod_utils.hpp"
#include <cocos2d.h>
#include <gd.h>

using namespace cocos2d;
using namespace gd;

CCRepeatForever* LevelAreaLayer::getscaleact(float time, float scale)
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

CCRepeatForever* LevelAreaLayer::getfadeact(float time, GLubyte vally1, GLubyte vally2)
{
    return CCRepeatForever::create(
        CCSequence::create(
            CCEaseInOut::create(CCFadeTo::create(time, vally1), 2.0),
            CCEaseInOut::create(CCFadeTo::create(time, vally2), 2.0),
            nullptr
        ));
}

LevelAreaLayer* LevelAreaLayer::create() {
    auto ret = new LevelAreaLayer();
    if (ret && ret->init()) {
        //robert 1 :D
        ret->autorelease();
    }
    else {
        //robert -1
        delete ret;
        ret = nullptr;
    }
    return ret;
}
bool LevelAreaLayer::init() {
    auto winSize = CCDirector::sharedDirector()->getWinSize();
    setTouchEnabled(true);
    setKeypadEnabled(true);
    CCTextureCache::sharedTextureCache()->addImage("TowerSheet.png", 0);
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("TowerSheet.plist");
    GameManager::sharedState()->fadeInMusic("tower01.mp3");

    auto backgroundSprite = ModUtils::createSprite("game_bg_23_001.png");
    auto size = backgroundSprite->getContentSize();
    backgroundSprite->setScale(winSize.width / size.width);
    backgroundSprite->setAnchorPoint({ 0, 0 });
    backgroundSprite->setPosition({ 0,-75 });
    backgroundSprite->setColor({ 15, 50, 160 });

    backgroundSprite->setZOrder(-2);
    addChild(backgroundSprite);

    auto moveact = CCRepeatForever::create(
        CCSequence::create(
            CCEaseInOut::create(CCMoveBy::create(3.0, { 0,4 }), 2.0),
            CCEaseInOut::create(CCMoveBy::create(3.0, { 0,-4 }), 2.0),
            nullptr
        ));


    auto particle = CCParticleSystemQuad::create("particle_godray.plist");
    particle->setBlendFunc({ GL_SRC_ALPHA, GL_ONE });
    particle->setStartColor({ 200, 200, 40 });
    particle->setEndColor({ 200, 200, 40 });
    particle->runAction(getfadeact(4.0, 150, 110));
    particle->setPosition({ 0.0, winSize.height });
    particle->setAnchorPoint({ 0.0,0.5 });
    particle->setRotation(25.0);
    particle->setScale(1.0);
    addChild(particle);
    CCSprite* godray01_001 = ModUtils::createSprite("godray01_001.png");
    addChild(godray01_001);
    godray01_001->setPosition({ 0.0, winSize.height });
    godray01_001->setAnchorPoint({ 0.0,0.5 });
    godray01_001->setRotation(25.0);
    godray01_001->setScaleX(2.800);
    godray01_001->setScaleY(1.700);
    godray01_001->setColor({ 200, 200, 40 });
    godray01_001->setOpacity(80);
    godray01_001->setBlendFunc({ GL_SRC_ALPHA, GL_ONE });
    godray01_001->runAction(getfadeact(4.0, 140, 90));

    //theTower_01_001
    CCSprite* theTower_01_001 = ModUtils::createSprite("theTower_01_001.png");
    theTower_01_001->setTag(666);
    addChild(theTower_01_001);
    theTower_01_001->setPosition({ winSize.width / 2, winSize.height / 2 });
    theTower_01_001->runAction(moveact);
    //towerShine1 for theTower_01_001
    CCSprite* towerShine = ModUtils::createSprite("towerShine.png");
    towerShine->setBlendFunc({ GL_SRC_ALPHA, GL_ONE });
    towerShine->setColor({ 255, 255, 20 });
    towerShine->setPosition({ 58.000, 180.000 });
    towerShine->runAction(getfadeact(3.0, 150, 80));
    theTower_01_001->addChild(towerShine);
    //towerTorch_001 for theTower_01_001
    CCSprite* towerTorch_001 = ModUtils::createSprite("towerTorch_001.png");
    towerTorch_001->setPosition({ 90.000, 65.500 });
    theTower_01_001->addChild(towerTorch_001);
    //fire for torch 💀
    CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    CCPoint firePos = CCPoint(10.500, 27.500);
    CCSprite* fire2 = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Fire_02_2_looped_001.png"));
    towerTorch_001->addChild(fire2);
    fire2->setPosition(firePos);
    fire2->setScale(0.800);
    fire2->setColor({ 255, 255, 10 });
    CCSprite* fire1 = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Fire_02_looped_001.png"));
    towerTorch_001->addChild(fire1);
    fire1->setPosition(firePos);
    fire1->setScale(0.400);
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
    //towerShine1 for fire of torch пон?
    CCSprite* torchShine = ModUtils::createSprite("towerShine.png");
    torchShine->setBlendFunc({ GL_SRC_ALPHA, GL_ONE });
    torchShine->setColor({ 255, 180, 20 });
    torchShine->setPosition({ 10.000, 20.000 });
    torchShine->runAction(getfadeact(1.5, 100, 60));
    torchShine->runAction(getscaleact(3.0, 0.9));
    towerTorch_001->addChild(torchShine);
    CCSprite* torchShine2 = ModUtils::createSprite("towerShine.png");
    torchShine2->setBlendFunc({ GL_SRC_ALPHA, GL_ONE });
    torchShine2->setColor({ 255, 180, 20 });
    torchShine2->setPosition({ 10.000, 20.000 });
    torchShine2->runAction(getfadeact(1.0, 120, 80));
    torchShine2->runAction(getscaleact(2.0, 0.8));
    towerTorch_001->addChild(torchShine2);
    //tower touch zone
    CCMenuItem* doorZone = CCMenuItem::create(this, menu_selector(LevelAreaLayer::onClickDoor));
    doorZone->setContentSize({ 60.000, 60.000 });
    theTower_01_001->addChild(CCMenu::createWithItem(doorZone),1,777);
    CCMenu* doorZoneMenu = (CCMenu*)doorZone->getParent();
    doorZoneMenu->setPosition({57.000, 70.000});

    //BACK BTN GJ_arrow_03_001.png
    CCMenuItemSpriteExtra* backItem = CCMenuItemSpriteExtra::create(ModUtils::createSprite("GJ_arrow_03_001.png"), this, menu_selector(LevelAreaLayer::onBack));
    backItem->setPosition({ 25, winSize.height - 25 });
    addChild(CCMenu::createWithItem(backItem));
    CCMenu* backMenu = (CCMenu*)backItem->getParent();
    backMenu->setPosition({ 0,0 });

    CCLayerGradient* Gradient = CCLayerGradient::create(ccColor4B({ 0,0,0,0 }), ccColor4B({ 116, 177, 169, 160, }), { 0.0, 1.0 });
    addChild(Gradient);
    Gradient->runAction(getfadeact(5.0, 220, 160));
    Gradient->setBlendFunc({ GL_SRC_ALPHA, GL_ONE });

    
    return true;
}

void LevelAreaLayer::keyBackClicked() {
    auto layer = CreatorLayer::create();
    auto scene = CCScene::create();
    scene->addChild(layer);
    CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5f, scene));
    GameManager::sharedState()->fadeInMusic("menuLoop.mp3");
}

void LevelAreaLayer::onClickDoor(CCObject* object) {
    CCSprite* theTower_01_001 = (CCSprite*)getChildByTag(666);
    if (theTower_01_001->numberOfRunningActions() == 1) {
        GameSoundManager::playEffect("door02.ogg");
        theTower_01_001->runAction(CCEaseExponentialIn::create(CCScaleTo::create(1.2, 15.000)));
        theTower_01_001->runAction(CCEaseExponentialIn::create(CCMoveBy::create(1.2, { -30.0, 1200.0 })));
        runAction(CCSequence::create(CCDelayTime::create(1.0f), CCCallFunc::create(object, SEL_CallFunc(&LevelAreaLayer::enterTower)), nullptr));
    }
}

void LevelAreaLayer::enterTower() {
    GameSoundManager::playEffect("door01.ogg");
    auto layer = LevelAreaInnerLayer::create();
    auto scene = CCScene::create();
    scene->addChild(layer);
    CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5f, scene));
}

void LevelAreaLayer::onBack(CCObject* object) {
    keyBackClicked();
}