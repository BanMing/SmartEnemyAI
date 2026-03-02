// Copyright BanMing

#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "CoreMinimal.h"
#include "Navigation/PathFollowingComponent.h"

#include "BTTask_MoveAlongPatrolRoute.generated.h"

/**
 *
 */
UCLASS()
class SMARTENEMYAI_API UBTTask_MoveAlongPatrolRoute : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_MoveAlongPatrolRoute(const FObjectInitializer& ObjectInitializer);

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	UFUNCTION()
	void OnMoveToEnd(EPathFollowingResult::Type MovementResult);

protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UBehaviorTreeComponent> MyOwnerComp;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class UAIAsyncTaskBlueprintProxy> AIAsyncTaskBlueprintProxy;
};
