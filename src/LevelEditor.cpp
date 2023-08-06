#include "LevelEditor.hpp"

inline bool(__thiscall* LevelEditorLayer_init)(LevelEditorLayer*, GJGameLevel*);
bool __fastcall LevelEditorLayer_init_H(LevelEditorLayer* self, int edx, GJGameLevel* level) {
    if (!LevelEditorLayer_init(self, level)) return false;
    CCLayerColor* THE_LINE = CCLayerColor::create({ 255,255,255,55 });
    THE_LINE->setAnchorPoint({ 0.f,0.f });
    THE_LINE->setPosition({ 0, CCDirector::sharedDirector()->getScreenTop() - 115 });
    THE_LINE->setScaleX({ 50 }); THE_LINE->setScaleY({ 0.002f });
    self->addChild(THE_LINE, -1);
    return true;
}

inline void(__thiscall* LevelEditorLayer_onStopPlaytest)(LevelEditorLayer*);
void __fastcall LevelEditorLayer_onStopPlaytest_H(LevelEditorLayer* self, void*) {
    LevelEditorLayer_onStopPlaytest(self);
    if (PlayLayerMod::isSwingCopterMode) {
        GameManager::sharedState()->setPlayerShip(GameManager::sharedState()->getIntGameVariable("oldShipIcon"));//bring up by oldShipIcon
    }
    PlayLayerMod::isSwingCopterMode = false;
}

inline void(__thiscall* LevelEditorLayer_onPlaytest)(LevelEditorLayer*);
void __fastcall LevelEditorLayer_onPlaytest_H(LevelEditorLayer* self, void*) {
    LevelEditorLayer_onPlaytest(self);
    if (PlayLayerMod::isSwingCopterMode) {
        GameManager::sharedState()->setPlayerShip(GameManager::sharedState()->getIntGameVariable("oldShipIcon"));//bring up by oldShipIcon
    }
    PlayLayerMod::isSwingCopterMode = false;
}

inline bool(__thiscall* EditorPauseLayer_init)(EditorPauseLayer*, LevelEditorLayer*);
bool __fastcall EditorPauseLayer_init_H(EditorPauseLayer* self, int edx, LevelEditorLayer* levelEditorLayer) {
    if (!EditorPauseLayer_init(self, levelEditorLayer)) return false;
    if (PlayLayerMod::PlayLayerMod::isSwingCopterMode) {
        GameManager::sharedState()->setPlayerShip(GameManager::sharedState()->getIntGameVariable("oldShipIcon"));//bring up by oldShipIcon
    }
    PlayLayerMod::isSwingCopterMode = false;
    return true;
}

inline void(__thiscall* EditorUI_setupCreateMenu)(EditorUI*);
void __fastcall EditorUI_setupCreateMenu_H(EditorUI* self, void*) {
    EditorUI_setupCreateMenu(self);
    //tab6
    auto tab6 = (EditButtonBar*)(self->m_pCreateButtonBars->objectAtIndex(6));
    tab6->m_pButtonArray->insertObject(self->getCreateBtn(3005, 4), 4);//spider pad
    tab6->m_pButtonArray->insertObject(self->getCreateBtn(3004, 4), 13);//spider orb
    tab6->m_pButtonArray->insertObject(self->getCreateBtn(2926, 4), 17);//green portal
    tab6->reloadItemsInNormalSize();
    //tab7
    auto tab7 = (EditButtonBar*)(self->m_pCreateButtonBars->objectAtIndex(7));
    //lava nad other animated blocks
    tab7->m_pButtonArray->addObject(self->getCreateBtn(1591, 4));
    tab7->m_pButtonArray->addObject(self->getCreateBtn(1593, 4));
    tab7->m_pButtonArray->addObject(self->getCreateBtn(1849, 4));
    tab7->m_pButtonArray->addObject(self->getCreateBtn(1850, 4));
    tab7->m_pButtonArray->addObject(self->getCreateBtn(1851, 4));
    tab7->m_pButtonArray->addObject(self->getCreateBtn(1852, 4));
    tab7->m_pButtonArray->addObject(self->getCreateBtn(1853, 4));
    tab7->m_pButtonArray->addObject(self->getCreateBtn(1854, 4));
    tab7->m_pButtonArray->addObject(self->getCreateBtn(1855, 4));
    tab7->m_pButtonArray->addObject(self->getCreateBtn(1858, 4));
    tab7->m_pButtonArray->addObject(self->getCreateBtn(1856, 4));
    tab7->m_pButtonArray->addObject(self->getCreateBtn(1697, 4));
    tab7->m_pButtonArray->addObject(self->getCreateBtn(1698, 4));
    tab7->m_pButtonArray->addObject(self->getCreateBtn(1699, 4));
    tab7->m_pButtonArray->addObject(self->getCreateBtn(1857, 4));
    tab7->m_pButtonArray->addObject(self->getCreateBtn(1860, 4));
    tab7->m_pButtonArray->addObject(self->getCreateBtn(1516, 4));
    tab7->m_pButtonArray->addObject(self->getCreateBtn(1518, 4));
    tab7->m_pButtonArray->addObject(self->getCreateBtn(1517, 4));
    //reload tab7 i think
    tab7->reloadItemsInNormalSize();

    //tab8
    //auto tab8 = (EditButtonBar*)(self->m_pCreateButtonBars->objectAtIndex(8));
    //tab8->m_pButtonArray->addObject(self->getCreateBtn(2140, 4));
    //tab8->loadFromItems(tab8->m_pButtonArray, GameManager::sharedState()->getIntGameVariable("0049"), GameManager::sharedState()->getIntGameVariable("0050"), true);
    //tab14
    auto tab14 = (EditButtonBar*)(self->m_pCreateButtonBars->objectAtIndex(14));
    auto timeWarp = tab14->m_pButtonArray->objectAtIndex(4);
    tab14->m_pButtonArray->removeObjectAtIndex(4);
    tab14->m_pButtonArray->insertObject(self->getCreateBtn(2701, 5), 4);//stop
    tab14->m_pButtonArray->insertObject(self->getCreateBtn(2702, 5), 5);//stop
    tab14->m_pButtonArray->insertObject(self->getCreateBtn(2067, 5), 11);//scale
    tab14->m_pButtonArray->insertObject(self->getCreateBtn(1912, 5), 20);//random
    tab14->m_pButtonArray->insertObject(self->getCreateBtn(2068, 5), 21);//adv random
    tab14->m_pButtonArray->insertObject(self->getCreateBtn(1913, 4), 22);//zoom
    tab14->m_pButtonArray->insertObject(self->getCreateBtn(1914, 5), 23);//zoom
    tab14->m_pButtonArray->insertObject(self->getCreateBtn(1916, 5), 24);//offset
    tab14->m_pButtonArray->insertObject(self->getCreateBtn(1917, 4), 25);//reverse
    tab14->m_pButtonArray->insertObject(self->getCreateBtn(1934, 4), 26);//song
    tab14->m_pButtonArray->insertObject(timeWarp, 27);//yo
    tab14->m_pButtonArray->insertObject(self->getCreateBtn(1931, 4), 38);//end
    tab14->m_pButtonArray->insertObject(self->getCreateBtn(1932, 5), 39);//stopJump
    tab14->reloadItemsInNormalSize();

    return;
}
inline void(__thiscall* EditorUI_selectObject)(EditorUI*, GameObject* obj, bool filter);//win 0x86250;
void __fastcall EditorUI_selectObject_H(EditorUI* self, void*, GameObject* obj, bool filter) {
    EditorUI_selectObject(self, obj, filter);
    LevelEditor::lastSelectedObj = obj;
    //CCMessageBox(std::string("LevelEditor::lastSelectedObj: " + std::to_string(LevelEditor::lastSelectedObj)).c_str(), __FUNCTION__);
}
inline void(__thiscall* editObject)(EditorUI*, cocos2d::CCObject*);
void __fastcall editObject_H(EditorUI* self, void*, cocos2d::CCObject* object) {
    if (LevelEditor::lastSelectedObj->m_nObjectID == 1913) {
        CustomTriggerPopup::create((EffectGameObject*)LevelEditor::lastSelectedObj)->show();
    }
    editObject(self, object);
}

void CreateLevelEditorHooks() {
    HOOK(base + 0x15ee00, LevelEditorLayer_init, true);
    HOOK(base + 0x169F10, LevelEditorLayer_onStopPlaytest, true);
    HOOK(base + 0x1695A0, LevelEditorLayer_onPlaytest, true);
    HOOK(base + 0x730e0, EditorPauseLayer_init, true);
    HOOK(base + 0x7CAF0, EditorUI_setupCreateMenu, false);//huh
    HOOK(base + 0x86250, EditorUI_selectObject, false);
    HOOK(base + 0x8ca50, editObject, false);
}
