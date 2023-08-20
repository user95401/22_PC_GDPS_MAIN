#include "ObjectSetupPopups.hpp"

CustomTriggerPopup::CustomTriggerPopup() :
    FLAlertLayer() {
    m_nJoystickConnected = -1;
    m_bNoElasticity = true;
    m_effectObject = nullptr;
}
CustomTriggerPopup* CustomTriggerPopup::create(EffectGameObject* obj) {
    CustomTriggerPopup* ret = new CustomTriggerPopup();
    if (ret && ret->init(obj)) ret->autorelease();
    else CC_SAFE_DELETE(ret);
    return ret;
}
void CustomTriggerPopup::onTouch(CCObject* sneder) { m_effectObject->m_bTouchTriggered = bool(!m_effectObject->m_bTouchTriggered); update(); }
void CustomTriggerPopup::onSpawn(CCObject* sneder) { m_effectObject->m_bSpawnTriggered = bool(!m_effectObject->m_bSpawnTriggered); update(); }
void CustomTriggerPopup::update() {
    m_effectObject->m_bTrigger = true;
    saveString->setString(m_effectObject->getSaveString().c_str());
}
void CustomTriggerPopup::onClose(CCObject* callback) {
    m_effectObject->m_bTrigger = true;
    m_effectObject = reinterpret_cast<EffectGameObject*>(EffectGameObject::objectFromString(m_effectObject->getSaveString(), true));
    this->removeFromParentAndCleanup(true);
}
void CustomTriggerPopup::keyBackClicked() {
    onClose(NULL);
}
bool CustomTriggerPopup::init(EffectGameObject* obj) {
    m_effectObject = obj;
    if (CCLayerColor::initWithColor(ccc4(0, 0, 0, 150)) && m_effectObject->m_nObjectID > 1) {
        registerWithTouchDispatcher();
        setTouchEnabled(true);
        setKeypadEnabled(true);

        m_pLayer = CCLayer::create();
        addChild(m_pLayer);
        m_pButtonMenu = CCMenu::create();
        addChild(m_pButtonMenu);

        auto scale9 = extension::CCScale9Sprite::create("GJ_square01.png");
        scale9->setContentSize(CCSizeMake(300, 280));
        m_pButtonMenu->addChild(scale9, -2);

        m_pButtonMenu->addChild(saveString = CCLabelBMFont::create(m_effectObject->getSaveString().c_str(), "chatFont.fnt", 160));
        saveString->setOpacity(8);
        saveString->setPositionY(-80.000);

        m_pButtonMenu->addChild(CCLabelBMFont::create("still idk how to save something of EffectGameObject", "chatFont.fnt", 160));

        auto okBtn = CCMenuItemSpriteExtra::create(ButtonSprite::create("OK", 0, false, "goldFont.fnt", "GJ_button_01.png", 0, 1.0),
            this, menu_selector(CustomTriggerPopup::onClose));
        m_pButtonMenu->addChild(okBtn);
        okBtn->setScale(0.8928571428571429);
        okBtn->setPositionY(-113.0);

        auto onTouchBtn = CCMenuItemToggler::createWithStandardSprites(this, menu_selector(CustomTriggerPopup::onTouch));
        onTouchBtn->setScale(0.7142857142857143);
        onTouchBtn->setPosition(-128.0, -68.5);
        onTouchBtn->toggle(m_effectObject->m_bTouchTriggered);
        m_pButtonMenu->addChild(onTouchBtn);

        auto onSpawnBtn = CCMenuItemToggler::createWithStandardSprites(this, menu_selector(CustomTriggerPopup::onSpawn));
        onSpawnBtn->setScale(0.7142857142857143);
        onSpawnBtn->setPosition(-128.0, -108.5);
        onSpawnBtn->toggle(m_effectObject->m_bSpawnTriggered);
        m_pButtonMenu->addChild(onSpawnBtn);

        auto SpawnTriggered = CCLabelBMFont::create("Spawn   \nTriggered", "bigFont.fnt");
        SpawnTriggered->setScale(0.37142857142857144);
        CCPoint SpawnTriggeredpos(-74.5, -108.0);
        SpawnTriggered->setPosition(m_pLayer->convertToNodeSpace(SpawnTriggeredpos));
        m_pButtonMenu->addChild(SpawnTriggered);

        auto TouchTriggered = CCLabelBMFont::create("Touch    \nTriggered", "bigFont.fnt");
        TouchTriggered->setScale(0.37142857142857144);
        CCPoint TouchTriggeredpos(-76.0, -68.0);
        TouchTriggered->setPosition(m_pLayer->convertToNodeSpace(TouchTriggeredpos));
        m_pButtonMenu->addChild(TouchTriggered);
        return true;
    }
    else return false;
}

SetupPortalPopup::SetupPortalPopup() :
    FLAlertLayer() {
    m_nJoystickConnected = -1;
    m_bNoElasticity = true;
    m_effectObject = nullptr;
}
SetupPortalPopup* SetupPortalPopup::create(GameObject* obj) {
    SetupPortalPopup* ret = new SetupPortalPopup();
    if (ret && ret->init(obj)) ret->autorelease();
    else CC_SAFE_DELETE(ret);
    return ret;
}
void SetupPortalPopup::onTouch(CCObject* sneder) { m_effectObject->m_bTouchTriggered = bool(!m_effectObject->m_bTouchTriggered); update(); }
void SetupPortalPopup::onfrfly(CCObject* sneder) { 
    m_effectObject->m_fAnimSpeed = (m_effectObject->m_fAnimSpeed > 0.49 && m_effectObject->m_fAnimSpeed < 0.62) ? 1.0 : 0.5; 
    update(); 
}
void SetupPortalPopup::update() {
    saveString->setString(m_effectObject->getSaveString().c_str());
}
void SetupPortalPopup::onClose(CCObject* callback) {
    m_effectObject = reinterpret_cast<GameObject*>(GameObject::objectFromString(m_effectObject->getSaveString(), true));
    this->removeFromParentAndCleanup(true);
}
void SetupPortalPopup::keyBackClicked() {
    onClose(NULL);
}
bool SetupPortalPopup::init(GameObject* obj) {
    m_effectObject = obj;
    if (CCLayerColor::initWithColor(ccc4(0, 0, 0, 150)) && m_effectObject->m_nObjectID > 1) {
        registerWithTouchDispatcher();
        setTouchEnabled(true);
        setKeypadEnabled(true);

        m_pLayer = CCLayer::create();
        addChild(m_pLayer);
        m_pButtonMenu = CCMenu::create();
        addChild(m_pButtonMenu);

        auto scale9 = extension::CCScale9Sprite::create("GJ_square01.png");
        scale9->setContentSize(CCSizeMake(430.0, 310.0));
        m_pButtonMenu->addChild(scale9, -2);

        CCLabelBMFont* title = CCLabelBMFont::create("Setup Portal", "bigFont.fnt");
        title->setPositionY(140.f);
        title->setScale(0.650);
        m_pButtonMenu->addChild(title);

        m_pButtonMenu->addChild(saveString = CCLabelBMFont::create(m_effectObject->getSaveString().c_str(), "chatFont.fnt", 160));
        saveString->setOpacity(8);
        saveString->setPositionY(-100.000);

        auto okBtn = CCMenuItemSpriteExtra::create(ButtonSprite::create("OK", 0, false, "goldFont.fnt", "GJ_button_01.png", 0, 1.0),
            this, menu_selector(SetupPortalPopup::onClose));
        m_pButtonMenu->addChild(okBtn);
        okBtn->setScale(1.0);
        okBtn->setPositionY(-132.000);

        auto freeflyBtn = CCMenuItemToggler::createWithStandardSprites(this, menu_selector(SetupPortalPopup::onfrfly));
        freeflyBtn->setScale(0.800);
        freeflyBtn->setPosition(-194.000, 134.000);
        freeflyBtn->toggle(m_effectObject->m_fAnimSpeed > 0.49 && m_effectObject->m_fAnimSpeed < 0.62);
        m_pButtonMenu->addChild(freeflyBtn);
        auto freefly = CCLabelBMFont::create("Free Mode", "bigFont.fnt");
        freefly->setScale(0.450);
        freefly->setPosition(-135.000, 135.000);
        m_pButtonMenu->addChild(freefly);
        return true;
    }
    else return false;
}