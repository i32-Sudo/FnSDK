#pragma once
#include "SDK.h"
class ULocalPlayer {
private:

public:
	APlayerController* GetPlayerController() {
		return Driver->read<APlayerController*>((uint64_t)this + Offsets::ULocalPlayer::playerController);
	}
};