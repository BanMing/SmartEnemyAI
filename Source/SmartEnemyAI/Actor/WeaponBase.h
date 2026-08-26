// Copyright BanMing

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/WeaponInterface.h"

#include "WeaponBase.generated.h"

UCLASS()
class SMARTENEMYAI_API AWeaponBase : public AActor, public IWeaponInterface
{
	GENERATED_BODY()

public:
	AWeaponBase();

public:
	virtual void WieldWeapon_Implementation(USkeletalMeshComponent* OwnerSkeletalMesh) override;
};
