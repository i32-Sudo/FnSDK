#pragma once
#include "SDK.h"
class UWorld {
private:

public:
	UGameInstance* GetGameInstance() {
		return Driver->read<UGameInstance*>((uint64_t)this + Offsets::UWorld::owningGameInstance);
	}

	AGameState* GetGameState() {
		return Driver->read<AGameState*>((uint64_t)this + Offsets::UWorld::gameState);
	}
};