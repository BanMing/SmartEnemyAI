// Copyright BanMing

#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "CoreMinimal.h"

#include "BTTask_ClearFocus.generated.h"

/**
 *
 */
UCLASS()
class SMARTENEMYAI_API UBTTask_ClearFocus : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_ClearFocus(const FObjectInitializer& ObjectInitializer);

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
