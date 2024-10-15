#pragma once
#include "SDK.h"

class AGameState {
private:

public:
	TArray<APlayerState*> GetPlayerArray() {
		return Driver->read<TArray<APlayerState*>>((uint64_t)this + Offsets::AGameState::playerArray);
	}
};