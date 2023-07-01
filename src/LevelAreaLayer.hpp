#pragma once
#include <gd.h>
using namespace cocos2d;
using namespace gd;

class LevelAreaLayer : public CCLayer {
protected:
    virtual bool init();
    virtual void keyBackClicked();
    void onBack(cocos2d::CCObject*);
    void onClickDoor(cocos2d::CCObject*);
    void enterTower();
    CCRepeatForever* getscaleact(float time, float scale);
    CCRepeatForever* getfadeact(float time, GLubyte vally1, GLubyte vally2);
public:
    static LevelAreaLayer* create();
};