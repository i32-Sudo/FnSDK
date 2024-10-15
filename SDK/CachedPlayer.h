#pragma once
#include "SDK.h"

struct CachedPlayer {
	APlayerState* pointer = NULL;
	APawn* aPawn = NULL;
	USkeletalMeshComponent* mesh = NULL;
	Vector3 headPosition = { 0.0, 0.0, 0.0 };
	Vector3 rootPosition = { 0.0, 0.0, 0.0 };
	Vector3 relativeLocation = { 0.0, 0.0, 0.0 };
	bool isVisible = false;
};