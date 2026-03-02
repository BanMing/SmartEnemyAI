// Copyright BanMing

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "EnemyInterface.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttackEndSignature);

class APatrolRoute;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEnemyInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class SMARTENEMYAI_API IEnemyInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual FOnAttackEndSignature& GetOnAttackEndDelegate() = 0;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Attack();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void WieldingWeapon();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool IsWiedingWeapon();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	APatrolRoute* GetPatrolRoute();
};
