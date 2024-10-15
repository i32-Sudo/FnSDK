#pragma once
#include "SDK.h"
class APlayerController {
private:

public:
	APawn* GetAPawn() {
		return Driver->read<APawn*>((uint64_t)this + Offsets::APlayerController::acknowledgedPawn);
	}
};