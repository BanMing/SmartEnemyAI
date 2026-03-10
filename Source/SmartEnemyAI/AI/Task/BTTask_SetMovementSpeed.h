// Copyright BanMing

#pragma once

#include "AI/AIDataTypes.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CoreMinimal.h"

#include "BTTask_SetMovementSpeed.generated.h"

/**
 *
 */
UCLASS()
class SMARTENEMYAI_API UBTTask_SetMovementSpeed : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_SetMovementSpeed(const FObjectInitializer& ObjectInitializer);

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere)
	EMovementSpeed MovementSpeed;
};
