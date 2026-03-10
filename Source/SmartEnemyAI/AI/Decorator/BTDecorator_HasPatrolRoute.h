// Copyright BanMing

#pragma once

#include "BehaviorTree/BTDecorator.h"
#include "CoreMinimal.h"

#include "BTDecorator_HasPatrolRoute.generated.h"

/**
 *
 */
UCLASS()
class SMARTENEMYAI_API UBTDecorator_HasPatrolRoute : public UBTDecorator
{
	GENERATED_BODY()

public:
	UBTDecorator_HasPatrolRoute(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
