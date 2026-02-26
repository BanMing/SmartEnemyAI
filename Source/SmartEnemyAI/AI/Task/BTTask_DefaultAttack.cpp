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

	MyOwnerComp = &OwnerComp;
	if (IEnemyInterface* EnemyInterface = Cast<IEnemyInterface>(MyController->GetPawn()))
	{
		if (!EnemyInterface->GetOnAttackEndDelegate().IsAlreadyBound(this, &ThisClass::OnAttackEnd))
		{
			EnemyInterface->GetOnAttackEndDelegate().AddDynamic(this, &ThisClass::OnAttackEnd);
		}
		IEnemyInterface::Execute_Attack(MyController->GetPawn());
		Result = EBTNodeResult::InProgress;
	}
	return Result;
}

EBTNodeResult::Type UBTTask_DefaultAttack::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* const MyController = OwnerComp.GetAIOwner();
	if (IEnemyInterface* EnemyInterface = Cast<IEnemyInterface>(MyController->GetPawn()))
	{
		EnemyInterface->GetOnAttackEndDelegate().RemoveDynamic(this, &ThisClass::OnAttackEnd);
	}
	MyOwnerComp = nullptr;
	return EBTNodeResult::Aborted;
}

void UBTTask_DefaultAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
}

void UBTTask_DefaultAttack::OnAttackEnd()
{
	if (MyOwnerComp)
	{
		FinishLatentTask(*MyOwnerComp, EBTNodeResult::Succeeded);
	}
}
