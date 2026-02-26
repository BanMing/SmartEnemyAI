// Copyright BanMing

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_IsWieldingWeapon.generated.h"

/**
 * 
 */
UCLASS()
class SMARTENEMYAI_API UBTDecorator_IsWieldingWeapon : public UBTDecorator
{
	GENERATED_BODY()
public:
	UBTDecorator_IsWieldingWeapon(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	 virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
	
};
