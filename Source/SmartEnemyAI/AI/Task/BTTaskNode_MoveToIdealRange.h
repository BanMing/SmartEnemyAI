// Copyright BanMing

#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "CoreMinimal.h"
#include "Navigation/PathFollowingComponent.h"

#include "BTTaskNode_MoveToIdealRange.generated.h"

/**
 *
 */
UCLASS()
class SMARTENEMYAI_API UBTTaskNode_MoveToIdealRange : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskNode_MoveToIdealRange(const FObjectInitializer& ObjectInitializer);

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UFUNCTION()
	void OnMoveToEnd(EPathFollowingResult::Type MovementResult);

protected:
	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector IdealRangeKey;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector AttackTargetKey;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UBehaviorTreeComponent> MyOwnerComp;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class UAIAsyncTaskBlueprintProxy> AIAsyncTaskBlueprintProxy;
};
