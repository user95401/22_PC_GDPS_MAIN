#pragma once
#include "22_PC_GDPS_MAIN.h"

class PlayLayerMod : PlayLayer {
public:
    static void updateByGamePlayOptins(PlayLayer* self);

    inline static PlayLayer* PlayLayerFromINit;
    inline static bool enableTheCameraYFolow = false;
    inline static bool isSwingCopterMode = false;
};

void CreatePlayLayerHooks();
void CreatePlayerObjectHooks();