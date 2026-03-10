// Copyright BanMing
#include "AI/Task/BTTask_SetMovementSpeed.h"

#include "AIController.h"
#include "Interfaces/EnemyInterface.h"

UBTTask_SetMovementSpeed::UBTTask_SetMovementSpeed(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Set Movement Speed";
}

EBTNodeResult::Type UBTTask_SetMovementSpeed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = EBTNodeResult::Failed;
	if (AAIController* const MyController = OwnerComp.GetAIOwner())
	{
		if (MyController->GetPawn()->Implements<UEnemyInterface>())
		{
			IEnemyInterface::Execute_SetMovement(MyController->GetPawn(), MovementSpeed);
			Result = EBTNodeResult::Succeeded;
		}
	}

	return Result;
}
