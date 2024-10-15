#include "../Driver/Driver.h"
#include "../Globals.h"
#include "../Offsets.h"
#include "../SDK/SDK.h"
#include <algorithm>
#include <iterator>
#include <thread>
#include <chrono>

std::vector<APlayerState*> oldData{};

Camera GetViewPoint()
{
	Camera view_point{};
	uintptr_t location_pointer = Driver->read<uint64_t>((uint64_t)Globals::uWorld + 0x110);
	uintptr_t rotation_pointer = Driver->read<uint64_t>((uint64_t)Globals::uWorld + 0x120);
	FNRot fnrot{};
	fnrot.a = Driver->read<double>(rotation_pointer);
	fnrot.b = Driver->read<double>(rotation_pointer + 0x20);
	fnrot.c = Driver->read<double>(rotation_pointer + 0x1D0);
	view_point.location = Driver->read<Vector3>(location_pointer);
	view_point.rotation.x = asin(fnrot.c) * (180.0 / M_PI);
	view_point.rotation.y = ((atan2(fnrot.a * -1, fnrot.b) * (180.0 / M_PI)) * -1) * -1;
	view_point.fov = Driver->read<float>((uint64_t)Globals::localPlayerController + 0x394) * 90.f;
	return view_point;
}

namespace Threads {
	void ViewPoint() {
		while (true) {
			Globals::localCamera = GetViewPoint();
			std::this_thread::sleep_for(std::chrono::milliseconds(1)); //Remove sleep for ultra fast actorLoop but not needed this is fast enough
		}
	}

	void EntityCache() {
		while (true) {
			Globals::uWorld = Driver->read<UWorld*>(Globals::uWorldAddy);
			if (!Globals::uWorld) {
				printf("UWorld not found!\n");
				continue;
			}

			Globals::gameInstance = Globals::uWorld->GetGameInstance();
			if (!Globals::gameInstance) {
				printf("Game instance not found!\n");
				continue;
			}

			Globals::localPlayer = Globals::gameInstance->GetLocalPlayer();
			if (!Globals::localPlayer) {
				printf("Local player not found!\n");
				continue;
			}

			Globals::localPlayerController = Globals::localPlayer->GetPlayerController();
			if (!Globals::localPlayerController) {
				printf("Local player controller not found!\n");
				continue;
			}

			Globals::localPlayerPawn = Globals::localPlayerController->GetAPawn();
			if (!Globals::localPlayerPawn) {
				printf("Local player pawn not found!\n");
				continue;
			}

			Globals::localPlayerPosition = Globals::localPlayerPawn->GetRelativeLocation();

			Globals::gameState = Globals::uWorld->GetGameState();
			if (!Globals::gameState) {
				printf("game state not found!\n");
				continue;
			}

			Globals::playerArray = Globals::gameState->GetPlayerArray();
			if (!Globals::playerArray.Num()) {
				printf("Player array emtpy!\n");
				continue;
			}

			std::vector<APlayerState*>newData(Globals::playerArray.Num());
			Driver->readArray<APlayerState*>(Globals::playerArray.GetAddress(), newData.data(), Globals::playerArray.Num());
			std::sort(newData.begin(), newData.end());

			std::vector<APlayerState*> removedPlayers;
			std::set_difference(oldData.begin(), oldData.end(), newData.begin(), newData.end(), std::inserter(removedPlayers, removedPlayers.begin()));

			std::vector<APlayerState*> newPlayers;
			std::set_difference(newData.begin(), newData.end(), oldData.begin(), oldData.end(), std::inserter(newPlayers, newPlayers.begin()));

			printf("New data size: %d\n", newData.size());
			oldData = newData;

			for (APlayerState* playerState : removedPlayers) {
				Globals::playerCache.erase(playerState);
			}

			for (APlayerState* playerState : newPlayers) {
				if (!playerState)
					continue;

				Globals::playerCache[playerState].pointer = playerState;
				Globals::playerCache[playerState].aPawn = playerState->GetAPawn();

				if (Globals::localPlayerPawn == Globals::playerCache[playerState].aPawn) {
					Globals::playerCache.erase(playerState);
					continue;
				}

				Globals::playerCache[playerState].mesh = Globals::playerCache[playerState].aPawn->GetSkeletalMeshComponent();
			}

			for (auto& [key, player] : Globals::playerCache) {
				if (!player.aPawn)
					player.aPawn = player.pointer->GetAPawn();

				player.mesh = player.aPawn->GetSkeletalMeshComponent();

				player.relativeLocation = player.aPawn->GetRelativeLocation();

				player.headPosition = player.mesh->GetBoneById(110);
				player.rootPosition = player.mesh->GetBoneById(0);

				player.isVisible = player.mesh->IsVisible();
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(1)); //Remove sleep for ultra fast actorLoop but not needed this is fast enough

		}
	}

	void Misc() {
		while (true) {

		}
	}

	void Aimbot() {
		while (true) {

		}
	}
}

