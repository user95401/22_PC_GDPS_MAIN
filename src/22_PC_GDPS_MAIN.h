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

bool idontgiveashitbro = false;
bool hooksLoaded = false;

PlayLayer* PlayLayerFromINit;
bool shouldPlaySpeedParticle = true;
int lastSelectedObj = 0;

bool isSwingCopterMode = false;
int oldShipIcon;

const char* version = "1.20";

// TODO: установите здесь ссылки на дополнительные заголовки, требующиеся для программы.
