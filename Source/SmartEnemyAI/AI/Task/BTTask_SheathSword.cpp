// Copyright BanMing

#include "AI/Task/BTTask_SheathSword.h"

#include "AIController.h"
#include "Interfaces/EnemyInterface.h"

UBTTask_SheathSword::UBTTask_SheathSword(const FObjectInitializer& ObjectInitializer)
{
	NodeName = "Sheath Weapon";
}

EBTNodeResult::Type UBTTask_SheathSword::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* const MyController = OwnerComp.GetAIOwner();
	EBTNodeResult::Type Result = EBTNodeResult::Failed;
	MyOwnerComp = &OwnerComp;
	if (IEnemyInterface* EnemyInterface = Cast<IEnemyInterface>(MyController->GetPawn()))
	{
		IEnemyInterface::Execute_SheathWeapon(MyController->GetPawn());

		if (!EnemyInterface->GetOnWeaponReadyDelegate().IsAlreadyBound(this, &ThisClass::OnWeaponReady))
		{
			EnemyInterface->GetOnWeaponReadyDelegate().AddDynamic(this, &ThisClass::OnWeaponReady);
		}

		Result = EBTNodeResult::InProgress;
	}
	return Result;
}
EBTNodeResult::Type UBTTask_SheathSword::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* const MyController = OwnerComp.GetAIOwner();

	if (IEnemyInterface* EnemyInterface = Cast<IEnemyInterface>(MyController->GetPawn()))
	{
		if (!EnemyInterface->GetOnWeaponReadyDelegate().IsAlreadyBound(this, &ThisClass::OnWeaponReady))
		{
			EnemyInterface->GetOnWeaponReadyDelegate().RemoveDynamic(this, &ThisClass::OnWeaponReady);
		}
	}
	MyOwnerComp = nullptr;

	return EBTNodeResult::Aborted;
}
void UBTTask_SheathSword::OnWeaponReady(bool bInWieldWeapon)
{
	if (MyOwnerComp)
	{
		FinishLatentTask(*MyOwnerComp, EBTNodeResult::Succeeded);
	}
}
