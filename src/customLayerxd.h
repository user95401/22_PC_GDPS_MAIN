#pragma once

#include <gd.h>
using namespace cocos2d;
using namespace gd;

class customLayerxd : public CCLayer {
protected:
    virtual bool init();
    virtual void keyBackClicked();
    void onBack(cocos2d::CCObject*);
public:
    static customLayerxd* create();

    // button callback function. if we were robtop this would be in MenuLayer, however we are not
    void switchcustomLayerxdbtn(CCObject*);
    //links
    void openURLcredits(CCObject*);
    void gamejolt_openURL(CCObject*);
    void openURL(CCObject*);
    void discord_openURL(CCObject*);
    void vk_openURL(CCObject*);
    void yt_openURL(CCObject*);
};