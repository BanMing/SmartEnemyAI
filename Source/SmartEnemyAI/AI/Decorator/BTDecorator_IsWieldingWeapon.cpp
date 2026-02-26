// Copyright BanMing

#include "AI/Decorator/BTDecorator_IsWieldingWeapon.h"

#include "AIController.h"
#include "Interfaces/EnemyInterface.h"

UBTDecorator_IsWieldingWeapon::UBTDecorator_IsWieldingWeapon(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = TEXT("Is Wielding Weapon");
}

bool UBTDecorator_IsWieldingWeapon::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AAIController* const MyController = OwnerComp.GetAIOwner();

	if (MyController->GetPawn()->Implements<UEnemyInterface>())
	{
		return IEnemyInterface::Execute_IsWiedingWeapon(MyController->GetPawn());
	}
	return false;
}
