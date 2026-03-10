// Copyright BanMing

#include "AI/Task/BTTask_MoveAlongPatrolRoute.h"

#include "AIController.h"
#include "Actor/PatrolRoute.h"
#include "Blueprint/AIAsyncTaskBlueprintProxy.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Interfaces/EnemyInterface.h"

UBTTask_MoveAlongPatrolRoute::UBTTask_MoveAlongPatrolRoute(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Move Along Patrol Route";
}

EBTNodeResult::Type UBTTask_MoveAlongPatrolRoute::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = EBTNodeResult::Failed;
	MyOwnerComp = &OwnerComp;
	if (AAIController* const MyController = OwnerComp.GetAIOwner())
	{
		if (MyController->GetPawn()->Implements<UEnemyInterface>())
		{
			if (APatrolRoute* PatrolRoute = IEnemyInterface::Execute_GetPatrolRoute(MyController->GetPawn()))
			{
				FVector TargetLocation = PatrolRoute->GetSplinePointAsWorldPosition();
				MyController->MoveTo(TargetLocation);
				AIAsyncTaskBlueprintProxy = UAIBlueprintHelperLibrary::CreateMoveToProxyObject(MyController, MyController->GetPawn(), TargetLocation, nullptr, 10.f);
				AIAsyncTaskBlueprintProxy->OnSuccess.AddDynamic(this, &ThisClass::OnMoveToEnd);
				AIAsyncTaskBlueprintProxy->OnFail.AddDynamic(this, &ThisClass::OnMoveToEnd);
				Result = EBTNodeResult::InProgress;
			}
		}
	}

	return Result;
}

EBTNodeResult::Type UBTTask_MoveAlongPatrolRoute::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (AIAsyncTaskBlueprintProxy)
	{
		AIAsyncTaskBlueprintProxy->OnSuccess.RemoveDynamic(this, &ThisClass::OnMoveToEnd);
		AIAsyncTaskBlueprintProxy->OnFail.RemoveDynamic(this, &ThisClass::OnMoveToEnd);
		AIAsyncTaskBlueprintProxy->RemoveFromRoot();
		AIAsyncTaskBlueprintProxy->MarkAsGarbage();
		AIAsyncTaskBlueprintProxy = nullptr;
	}
	MyOwnerComp = nullptr;

	if (AAIController* const MyController = OwnerComp.GetAIOwner())
	{
		MyController->StopMovement();
	}
	
	return EBTNodeResult::Aborted;
}

void UBTTask_MoveAlongPatrolRoute::OnMoveToEnd(EPathFollowingResult::Type MovementResult)
{
	if (MyOwnerComp)
	{
		if (AAIController* const MyController = MyOwnerComp->GetAIOwner())
		{
			if (MyController->GetPawn()->Implements<UEnemyInterface>())
			{
				if (APatrolRoute* PatrolRoute = IEnemyInterface::Execute_GetPatrolRoute(MyController->GetPawn()))
				{
					PatrolRoute->IncrementPatrolRoute();
				}
			}
		}
		FinishLatentTask(*MyOwnerComp, EBTNodeResult::Succeeded);
	}
}
