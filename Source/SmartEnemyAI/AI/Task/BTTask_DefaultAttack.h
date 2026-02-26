// Copyright BanMing

#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "CoreMinimal.h"

#include "BTTask_DefaultAttack.generated.h"

/**
 *
 */
UCLASS()
class SMARTENEMYAI_API UBTTask_DefaultAttack : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_DefaultAttack(const FObjectInitializer& ObjectInitializer);

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UFUNCTION()
	void OnAttackEnd();

protected:
	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> MyOwnerComp;
};
