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
    if (PlayLayerExt::isSwingCopterMode) {
        GameManager::sharedState()->setPlayerShip(GameManager::sharedState()->getIntGameVariable("oldShipIcon"));//bring up by oldShipIcon
    }
    PlayLayerExt::isSwingCopterMode = false;
}

inline void(__thiscall* LevelEditorLayer_onPlaytest)(LevelEditorLayer*);
void __fastcall LevelEditorLayer_onPlaytest_H(LevelEditorLayer* self, void*) {
    LevelEditorLayer_onPlaytest(self);
    if (PlayLayerExt::isSwingCopterMode) {
        GameManager::sharedState()->setPlayerShip(GameManager::sharedState()->getIntGameVariable("oldShipIcon"));//bring up by oldShipIcon
    }
    PlayLayerExt::isSwingCopterMode = false;
}

inline bool(__thiscall* EditorPauseLayer_init)(EditorPauseLayer*, LevelEditorLayer*);
bool __fastcall EditorPauseLayer_init_H(EditorPauseLayer* self, int edx, LevelEditorLayer* levelEditorLayer) {
    if (!EditorPauseLayer_init(self, levelEditorLayer)) return false;
    if (PlayLayerExt::PlayLayerExt::isSwingCopterMode) {
        GameManager::sharedState()->setPlayerShip(GameManager::sharedState()->getIntGameVariable("oldShipIcon"));//bring up by oldShipIcon
    }
    PlayLayerExt::isSwingCopterMode = false;
    return true;
}

inline void(__thiscall* EditorUI_setupCreateMenu)(EditorUI*);
void __fastcall EditorUI_setupCreateMenu_H(EditorUI* self, void*) {
    EditorUI_setupCreateMenu(self);
    //tab6
    if (auto tab6 = (EditButtonBar*)(self->m_pCreateButtonBars->objectAtIndex(6))) {
        tab6->m_pButtonArray->insertObject(self->getCreateBtn(3005, 4), 4);//spider pad
        tab6->m_pButtonArray->insertObject(self->getCreateBtn(3004, 4), 13);//spider orb
        tab6->m_pButtonArray->insertObject(self->getCreateBtn(2926, 4), 17);//green portal
        tab6->reloadItemsInNormalSize();
    }
    //tab7
    if(auto tab7 = (EditButtonBar*)(self->m_pCreateButtonBars->objectAtIndex(7))){
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
    }
    //tab11
    if(auto tab11 = (EditButtonBar*)(self->m_pCreateButtonBars->objectAtIndex(11))) {
        tab11->m_pButtonArray->addObject(self->getCreateBtn(1964, 4));//"blockPiece_001_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(1965, 4));//"blockPiece_002_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(1966, 4));//"blockPiece_003_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(1967, 4));//"blockPiece_004_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(1968, 4));//"blockPiece_005_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(1969, 4));//"blockPiece_006_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(1970, 4));//"blockPiece_007_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(1971, 4));//"blockPiece_008_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(1972, 4));//"blockPiece_009_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(1973, 4));//"blockPiece_010_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(1974, 4));//"blockPiece_011_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(1975, 4));//"blockPiece_012_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(1976, 4));//"blockPiece_013_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(1977, 4));//"blockPiece_014_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(1978, 4));//"blockPiece_015_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(1979, 4));//"blockPiece_016_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(1980, 4));//"blockPiece_017_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(1981, 4));//"blockPiece_018_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(1982, 4));//"blockPiece_019_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(1983, 4));//"blockPiece_020_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(1984, 4));//"blockPiece_021_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(1985, 4));//"blockPiece_022_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(1986, 4));//"blockPiece_023_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(1987, 4));//"blockPiece_024_001.png");

        tab11->m_pButtonArray->addObject(self->getCreateBtn(1988, 4));//"blockPiece_small_001_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(1989, 4));//"blockPiece_small_002_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(1990, 4));//"blockPiece_small_003_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(1991, 4));//"blockPiece_small_004_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(1992, 4));//"blockPiece_small_005_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(1993, 4));//"blockPiece_small_006_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(1994, 4));//"blockPiece_small_007_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(1995, 4));//"blockPiece_small_008_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(1996, 4));//"blockPiece_small_009_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(1997, 4));//"blockPiece_small_010_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(1998, 4));//"blockPiece_small_011_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(1999, 4));//"blockPiece_small_012_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(2000, 4));//"blockPiece_small_013_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(2001, 4));//"blockPiece_small_014_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(2002, 4));//"blockPiece_small_015_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(2003, 4));//"blockPiece_small_016_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(2004, 4));//"blockPiece_small_017_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(2005, 4));//"blockPiece_small_018_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(2006, 4));//"blockPiece_small_019_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(2007, 4));//"blockPiece_small_020_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(2008, 4));//"blockPiece_small_021_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(2009, 4));//"blockPiece_small_022_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(2010, 4));//"blockPiece_small_023_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(2011, 4));//"blockPiece_small_024_001.png");
        tab11->reloadItemsInNormalSize();
    }
    //tab14
    if(auto tab14 = (EditButtonBar*)(self->m_pCreateButtonBars->objectAtIndex(14))){
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
    }
    return;
}
inline void(__thiscall* EditorUI_selectObject)(EditorUI*, GameObject* obj, bool filter);//win 0x86250;
void __fastcall EditorUI_selectObject_H(EditorUI* self, void*, GameObject* obj, bool filter) {
    EditorUI_selectObject(self, obj, filter);
    LevelEditor::lastSelectedObj = obj;
    self->removeChildByTag(384);
    CCMenuItemSpriteExtra* customEditBtn = CCMenuItemSpriteExtra::create(ModUtils::createSprite("GJ_editObjBtn3_001.png"), self, menu_selector(EditorUI::editObject));
    customEditBtn->setPosition(-24.000, -95.000);
    CCMenu* customEditBtnMenu = CCMenu::createWithItem(customEditBtn);
    customEditBtnMenu->setPosition({ CCDirector::sharedDirector()->getScreenRight(), CCDirector::sharedDirector()->getScreenTop() });
    if (LevelEditor::lastSelectedObj->m_nObjectType == kGameObjectTypeShipPortal || LevelEditor::lastSelectedObj->m_nObjectType == kGameObjectTypeBallPortal || LevelEditor::lastSelectedObj->m_nObjectType == kGameObjectTypeUfoPortal || LevelEditor::lastSelectedObj->m_nObjectType == kGameObjectTypeWavePortal || LevelEditor::lastSelectedObj->m_nObjectType == kGameObjectTypeSpiderPortal) {
        self->addChild(customEditBtnMenu, 10, 384);
    }
    else if (LevelEditor::lastSelectedObj->m_nObjectID == 1913 ||
        LevelEditor::lastSelectedObj->m_nObjectID == 2701 ||
        LevelEditor::lastSelectedObj->m_nObjectID == 2702 ||
        LevelEditor::lastSelectedObj->m_nObjectID == 2067 ||
        LevelEditor::lastSelectedObj->m_nObjectID == 1912 ||
        LevelEditor::lastSelectedObj->m_nObjectID == 2068 ||
        LevelEditor::lastSelectedObj->m_nObjectID == 1913 ||
        LevelEditor::lastSelectedObj->m_nObjectID == 1914 ||
        LevelEditor::lastSelectedObj->m_nObjectID == 1916 ||
        LevelEditor::lastSelectedObj->m_nObjectID == 1917 ||
        LevelEditor::lastSelectedObj->m_nObjectID == 1934 ||
        LevelEditor::lastSelectedObj->m_nObjectID == 1931 ||
        LevelEditor::lastSelectedObj->m_nObjectID == 1932)
        self->addChild(customEditBtnMenu, 10, 384);
    else self->removeChildByTag(384);
    //CCMessageBox(std::string("LevelEditor::lastSelectedObj: " + std::to_string(LevelEditor::lastSelectedObj)).c_str(), __FUNCTION__);
}
inline void(__thiscall* deselectAll)(EditorUI*);//win 0x86af0;
void __fastcall deselectAll_H(EditorUI* self, void*) {
    deselectAll(self);
    self->removeChildByTag(384);
    //CCMessageBox(std::string("LevelEditor::lastSelectedObj: " + std::to_string(LevelEditor::lastSelectedObj)).c_str(), __FUNCTION__);
}
inline void(__thiscall* editObject)(EditorUI*, cocos2d::CCObject*);
void __fastcall editObject_H(EditorUI* self, void*, cocos2d::CCObject* object) {
    if (LevelEditor::lastSelectedObj->m_nObjectID == 1913 ||
        LevelEditor::lastSelectedObj->m_nObjectID == 2701 ||
        LevelEditor::lastSelectedObj->m_nObjectID == 2702 ||
        LevelEditor::lastSelectedObj->m_nObjectID == 2067 ||
        LevelEditor::lastSelectedObj->m_nObjectID == 1912 ||
        LevelEditor::lastSelectedObj->m_nObjectID == 2068 ||
        LevelEditor::lastSelectedObj->m_nObjectID == 1913 ||
        LevelEditor::lastSelectedObj->m_nObjectID == 1914 ||
        LevelEditor::lastSelectedObj->m_nObjectID == 1916 ||
        LevelEditor::lastSelectedObj->m_nObjectID == 1917 ||
        LevelEditor::lastSelectedObj->m_nObjectID == 1934 ||
        LevelEditor::lastSelectedObj->m_nObjectID == 1931 ||
        LevelEditor::lastSelectedObj->m_nObjectID == 1932) {
        self->editObject2(object);
        CustomTriggerPopup::create((EffectGameObject*)LevelEditor::lastSelectedObj)->show();
    }
    if (LevelEditor::lastSelectedObj->m_nObjectType == kGameObjectTypeShipPortal || LevelEditor::lastSelectedObj->m_nObjectType == kGameObjectTypeBallPortal || LevelEditor::lastSelectedObj->m_nObjectType == kGameObjectTypeUfoPortal || LevelEditor::lastSelectedObj->m_nObjectType == kGameObjectTypeWavePortal || LevelEditor::lastSelectedObj->m_nObjectType == kGameObjectTypeSpiderPortal) {
        SetupPortalPopup::create(LevelEditor::lastSelectedObj)->show();
    }
    editObject(self, object);
}

void CreateLevelEditorHooks() {
    HOOK(base + 0x15ee00, LevelEditorLayer_init, true);
    HOOK(base + 0x169F10, LevelEditorLayer_onStopPlaytest, true);
    HOOK(base + 0x1695A0, LevelEditorLayer_onPlaytest, true);
    HOOK(base + 0x730e0, EditorPauseLayer_init, true);
    HOOK(base + 0x7CAF0, EditorUI_setupCreateMenu, true);//huh
    HOOK(base + 0x86250, EditorUI_selectObject, true);
    HOOK(base + 0x86af0, deselectAll, true);
    HOOK(base + 0x8ca50, editObject, true);
}
