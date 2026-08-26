// Copyright BanMing

#include "Actor/WeaponBase.h"

AWeaponBase::AWeaponBase()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AWeaponBase::WieldWeapon_Implementation(USkeletalMeshComponent* OwnerSkeletalMesh)
{
}
