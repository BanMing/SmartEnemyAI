// Copyright BanMing

#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "CoreMinimal.h"

#include "BTTask_SetStatePassive.generated.h"

/**
 *
 */
UCLASS()
class SMARTENEMYAI_API UBTTask_SetStatePassive : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_SetStatePassive(const FObjectInitializer& ObjectInitializer);

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
