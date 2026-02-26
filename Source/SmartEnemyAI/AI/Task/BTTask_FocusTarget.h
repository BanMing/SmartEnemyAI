// Copyright BanMing

#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "CoreMinimal.h"

#include "BTTask_FocusTarget.generated.h"

/**
 *
 */
UCLASS()
class SMARTENEMYAI_API UBTTask_FocusTarget : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_FocusTarget(const FObjectInitializer& ObjectInitialize);

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;

protected:
	/** blackboard key selector */
	UPROPERTY(EditAnywhere, Category = Blackboard)
	struct FBlackboardKeySelector AttackTargetKey;
};
