// Copyright BanMing

#include "AI/Task/BTTask_WieldWeapon.h"

#include "AIController.h"
#include "Interfaces/EnemyInterface.h"

UBTTask_WieldWeapon::UBTTask_WieldWeapon(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Wield Weapon";
}

EBTNodeResult::Type UBTTask_WieldWeapon::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* const MyController = OwnerComp.GetAIOwner();
	EBTNodeResult::Type Result = EBTNodeResult::Failed;

	if (MyController->GetPawn()->Implements<UEnemyInterface>())
	{
		IEnemyInterface::Execute_WieldingWeapon(MyController->GetPawn());
		Result = EBTNodeResult::Succeeded;
	}
	return Result;
}
