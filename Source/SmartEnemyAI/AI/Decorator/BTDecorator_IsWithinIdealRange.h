// Copyright BanMing

#pragma once

#include "BehaviorTree/BTDecorator.h"
#include "CoreMinimal.h"

#include "BTDecorator_IsWithinIdealRange.generated.h"

/**
 *
 */
UCLASS()
class SMARTENEMYAI_API UBTDecorator_IsWithinIdealRange : public UBTDecorator
{
	GENERATED_BODY()
public:
	UBTDecorator_IsWithinIdealRange(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

protected:
	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector IdealRangeKey;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector AttackTargetKey;

	UPROPERTY(EditAnywhere)
	float ErrorMargin = 50.0f;
};
