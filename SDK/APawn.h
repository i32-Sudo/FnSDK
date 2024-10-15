#pragma once
#include "SDK.h"
class APawn {
private:

public:
	Vector3 GetRelativeLocation() {
		return Driver->read<Vector3>((Driver->read<uint64_t>((uint64_t)this + Offsets::APawn::rootComponent) + Offsets::APawn::relativeLocation));
	}

	USkeletalMeshComponent* GetSkeletalMeshComponent() {
		return Driver->read<USkeletalMeshComponent*>((uint64_t)this + Offsets::APawn::mesh);
	}
};