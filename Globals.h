#pragma once
#ifndef GLOBALS_H
#define GLOBALS_H

#include "Utils/Structs.h"
#include "SDK/SDK.h"
#include <vector>
#include <unordered_map>
#include <string>
#include <cstdint>

namespace Globals {
    extern int screenWidth;
    extern int screenHeight;

    extern __int64 uWorldAddy;
    extern UWorld* uWorld;
    extern UGameInstance* gameInstance;
    extern ULocalPlayer* localPlayer;
    extern APlayerController* localPlayerController;
    extern APawn* localPlayerPawn;
    extern Vector3 localPlayerPosition;
    extern AGameState* gameState;
    extern TArray<APlayerState*> playerArray;
    extern Camera localCamera;

    extern std::unordered_map<APlayerState*, CachedPlayer>playerCache;
}


namespace CFG {
    extern bool playerBox;
    extern bool playerLine;
}

#endif // GLOBALS_H
