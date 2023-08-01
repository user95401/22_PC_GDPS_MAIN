#pragma once
#include "22_PC_GDPS_MAIN.h"

class CustomTriggerPopup : public FLAlertLayer {
public:
    CCTextInputNode* mainInput;
    FLAlertLayer* helper;
    CCLabelBMFont* saveString;
    EffectGameObject* m_effectObject;
    CustomTriggerPopup();
    static CustomTriggerPopup* create(EffectGameObject* obj);
    void onTouch(CCObject* sneder);
    void onSpawn(CCObject* sneder);
    void update();
    void onClose(CCObject* callback);
    virtual void keyBackClicked();

    bool init(EffectGameObject* obj);
};

void CreateObjectsThemedHooks();