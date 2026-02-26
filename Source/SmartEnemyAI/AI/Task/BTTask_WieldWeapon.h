// Copyright BanMing

#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "CoreMinimal.h"

#include "BTTask_WieldWeapon.generated.h"

/**
 *
 */
UCLASS()
class SMARTENEMYAI_API UBTTask_WieldWeapon : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_WieldWeapon(const FObjectInitializer& ObjectInitializer);

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
