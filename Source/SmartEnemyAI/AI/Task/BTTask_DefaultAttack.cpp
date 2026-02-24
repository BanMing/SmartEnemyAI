// Copyright BanMing

#include "AI/Task/BTTask_DefaultAttack.h"

#include "AIController.h"
#include "Interfaces/EnemyInterface.h"

UBTTask_DefaultAttack::UBTTask_DefaultAttack(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Default Attack";
}

EBTNodeResult::Type UBTTask_DefaultAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* const MyController = OwnerComp.GetAIOwner();
	EBTNodeResult::Type Result = EBTNodeResult::Failed;
	if (MyController->GetPawn()->Implements<UEnemyInterface>())
	{
		IEnemyInterface::Execute_Attack(MyController->GetPawn());
		Result = EBTNodeResult::Succeeded;
	}
	return Result;
}

EBTNodeResult::Type UBTTask_DefaultAttack::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::Aborted;
}

void UBTTask_DefaultAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
}
