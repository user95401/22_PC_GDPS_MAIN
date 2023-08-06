// 22_PC_GDPS_MAIN.h : включаемый файл для стандартных системных включаемых файлов
// или включаемые файлы для конкретного проекта.

#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <iostream>
#include <random>
#include <cocos2d.h>
#include <gd.h>
#include "mod_utils.hpp"
#include "hooks.hpp"
#include <MinHook.h>
#include "customLayerxd.h"
#include "EventLevelPage.hpp"
#include "LevelAreaInnerLayer.hpp"
#include "LevelAreaLayer.hpp"

#include "Gameplay.hpp"
#include "Objects.hpp"
#include "OtherLayers.hpp"
#include "LevelEditor.hpp"

class ModBase {
protected:
    void ondontgiveashit(cocos2d::CCObject*);
public:
    inline static const char* version = "1.11";
    inline static bool idontgiveashitbro = false;
    static void msg(CCLayer* self, const char* redText = "", const char* customMsg = "");
};

// TODO: установите здесь ссылки на дополнительные заголовки, требующиеся для программы.
