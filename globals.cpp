#include "Globals.h"

// Include necessary headers for the types
#include <vector>
#include <unordered_map>
#include <string>

// Definitions of the variables
namespace Globals {
    int screenWidth = 0;
    int screenHeight = 0;

    __int64 uWorldAddy = NULL;
    UWorld* uWorld = NULL;
    UGameInstance* gameInstance = NULL;
    ULocalPlayer* localPlayer = NULL;
    APlayerController* localPlayerController = NULL;
    APawn* localPlayerPawn = NULL;
    Vector3 localPlayerPosition = { 0.0, 0.0, 0.0 };
    AGameState* gameState = NULL;
    TArray<APlayerState*> playerArray{};
    Camera localCamera{};

    std::unordered_map<APlayerState*, CachedPlayer>playerCache{};
}

namespace CFG {
    bool playerBox = false;
    bool playerLine = false;
}
