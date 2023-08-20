#pragma once
#include "22_PC_GDPS_MAIN.h"

class PlayLayerExt : public PlayLayer {
public:
    static void updateByGamePlayOptins(PlayLayer* self);

    inline static PlayLayer* PlayLayerFromINit;
    inline static bool freeMode = false;
    inline static bool isSwingCopterMode = false;
};

void CreatePlayLayerHooks();
void CreatePlayerObjectHooks();