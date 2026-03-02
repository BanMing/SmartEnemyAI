// Copyright BanMing

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "PatrolRoute.generated.h"

UCLASS()
class SMARTENEMYAI_API APatrolRoute : public AActor
{
	GENERATED_BODY()

public:
	APatrolRoute();

public:
	UFUNCTION(BlueprintCallable)
	void IncrementPatrolRoute();

	UFUNCTION(BlueprintPure)
	FVector GetSplinePointAsWorldPosition() const;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<class USplineComponent> SplineComp;

protected:
	UPROPERTY(BlueprintReadOnly)
	int32 PatrolIndex;

	// +1 / -1
	UPROPERTY(BlueprintReadOnly)
	int32 Direction;
};
