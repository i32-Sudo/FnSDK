#pragma once
#include "SDK.h"

static D3DMATRIX MatrixMultiplication(D3DMATRIX pm1, D3DMATRIX pm2)
{
	D3DMATRIX pout{};
	pout._11 = pm1._11 * pm2._11 + pm1._12 * pm2._21 + pm1._13 * pm2._31 + pm1._14 * pm2._41;
	pout._12 = pm1._11 * pm2._12 + pm1._12 * pm2._22 + pm1._13 * pm2._32 + pm1._14 * pm2._42;
	pout._13 = pm1._11 * pm2._13 + pm1._12 * pm2._23 + pm1._13 * pm2._33 + pm1._14 * pm2._43;
	pout._14 = pm1._11 * pm2._14 + pm1._12 * pm2._24 + pm1._13 * pm2._34 + pm1._14 * pm2._44;
	pout._21 = pm1._21 * pm2._11 + pm1._22 * pm2._21 + pm1._23 * pm2._31 + pm1._24 * pm2._41;
	pout._22 = pm1._21 * pm2._12 + pm1._22 * pm2._22 + pm1._23 * pm2._32 + pm1._24 * pm2._42;
	pout._23 = pm1._21 * pm2._13 + pm1._22 * pm2._23 + pm1._23 * pm2._33 + pm1._24 * pm2._43;
	pout._24 = pm1._21 * pm2._14 + pm1._22 * pm2._24 + pm1._23 * pm2._34 + pm1._24 * pm2._44;
	pout._31 = pm1._31 * pm2._11 + pm1._32 * pm2._21 + pm1._33 * pm2._31 + pm1._34 * pm2._41;
	pout._32 = pm1._31 * pm2._12 + pm1._32 * pm2._22 + pm1._33 * pm2._32 + pm1._34 * pm2._42;
	pout._33 = pm1._31 * pm2._13 + pm1._32 * pm2._23 + pm1._33 * pm2._33 + pm1._34 * pm2._43;
	pout._34 = pm1._31 * pm2._14 + pm1._32 * pm2._24 + pm1._33 * pm2._34 + pm1._34 * pm2._44;
	pout._41 = pm1._41 * pm2._11 + pm1._42 * pm2._21 + pm1._43 * pm2._31 + pm1._44 * pm2._41;
	pout._42 = pm1._41 * pm2._12 + pm1._42 * pm2._22 + pm1._43 * pm2._32 + pm1._44 * pm2._42;
	pout._43 = pm1._41 * pm2._13 + pm1._42 * pm2._23 + pm1._43 * pm2._33 + pm1._44 * pm2._43;
	pout._44 = pm1._41 * pm2._14 + pm1._42 * pm2._24 + pm1._43 * pm2._34 + pm1._44 * pm2._44;
	return pout;
}

class USkeletalMeshComponent {
private:

public:
	Vector3 GetBoneById(int boneId) {
		TArray<FTransform>boneArray = Driver->read<TArray<FTransform>>((uint64_t)this + Offsets::USkeletalMeshComponent::boneArray);
		if (!boneArray.Num())
			boneArray = Driver->read<TArray<FTransform>>((uint64_t)this + Offsets::USkeletalMeshComponent::boneArray + 0x10);

		FTransform bone = boneArray.GetById(boneId);

		FTransform compToWorld = Driver->read<FTransform>((uint64_t)this + Offsets::USkeletalMeshComponent::componentToWorld);

		D3DMATRIX matrix = MatrixMultiplication(bone.ToMatrixWithScale(), compToWorld.ToMatrixWithScale());
		return Vector3(matrix._41, matrix._42, matrix._43);
	}

	bool IsVisible()
	{
		float last_sumbit_time = Driver->read<float>((uint64_t)this + Offsets::USkeletalMeshComponent::lastSubmitTime);
		float last_render_time_on_screen = Driver->read<float>((uint64_t)this + Offsets::USkeletalMeshComponent::lastSubmitTimeOnScreen);
		return last_render_time_on_screen + 0.06f >= last_sumbit_time;
	}
};