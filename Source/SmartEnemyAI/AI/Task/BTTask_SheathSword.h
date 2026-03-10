// Copyright BanMing

#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "CoreMinimal.h"

#include "BTTask_SheathSword.generated.h"

/**
 *
 */
UCLASS()
class SMARTENEMYAI_API UBTTask_SheathSword : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_SheathSword(const FObjectInitializer& ObjectInitializer);

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UFUNCTION()
	void OnWeaponReady(bool bInWieldWeapon);

protected:
	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> MyOwnerComp;
};
