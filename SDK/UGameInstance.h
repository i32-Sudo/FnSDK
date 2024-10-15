#pragma once
#include "SDK.h"
class UGameInstance {
private:

public:
	ULocalPlayer* GetLocalPlayer() {
		return Driver->read<TArray<ULocalPlayer*>>((uint64_t)this + Offsets::UGameInstance::localPlayers).GetById(0);
	}
};