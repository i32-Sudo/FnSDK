#pragma once
#include "SDK.h"
class APlayerState {
private:

public:
	APawn* GetAPawn() {
		return Driver->read<APawn*>((uint64_t)this + Offsets::APlayerState::pawnPrivate);
	}
};