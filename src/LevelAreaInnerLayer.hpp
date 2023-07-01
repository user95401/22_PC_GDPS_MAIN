#pragma once
#include <gd.h>
using namespace cocos2d;
using namespace gd;

class LevelAreaInnerLayer : public CCLayer {
protected:
    virtual void keyBackClicked();
    CCMenu* runLevel1;
    CCMenu* runLevel2;
    CCMenu* runLevel3;
    CCMenu* runLevel4;
public:
    CREATE_FUNC(LevelAreaInnerLayer);
    virtual bool init();
    //static LevelAreaInnerLayer* create();
    void towerLevel1(cocos2d::CCObject*);
    void towerLevel2(cocos2d::CCObject*);
    void towerLevel3(cocos2d::CCObject*);
    void towerLevel4(cocos2d::CCObject*);
    void onBack(cocos2d::CCObject*);
    CCRepeatForever* getscaleact(float time, float scale);
    CCRepeatForever* getfadeact(float time, GLubyte vally1, GLubyte vally2);
    CCSprite* towerTorchInner();
};