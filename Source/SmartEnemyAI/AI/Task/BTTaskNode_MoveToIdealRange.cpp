// Copyright BanMing

#include "AI/Task/BTTaskNode_MoveToIdealRange.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIAsyncTaskBlueprintProxy.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

UBTTaskNode_MoveToIdealRange::UBTTaskNode_MoveToIdealRange(const FObjectInitializer& ObjectInitializer)
{
	NodeName = "Move to Ideal Range";
}

EBTNodeResult::Type UBTTaskNode_MoveToIdealRange::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = EBTNodeResult::Failed;

	if (AAIController* const MyController = OwnerComp.GetAIOwner())
	{
		if (AActor* Target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AttackTargetKey.SelectedKeyName)))
		{
			MyOwnerComp = &OwnerComp;
			const float IdealRange = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(IdealRangeKey.SelectedKeyName);

			MyController->MoveToActor(Target, IdealRange);
			AIAsyncTaskBlueprintProxy = UAIBlueprintHelperLibrary::CreateMoveToProxyObject(MyController, MyController->GetPawn(), FVector::Zero(), Target, IdealRange);
			AIAsyncTaskBlueprintProxy->OnSuccess.AddDynamic(this, &ThisClass::OnMoveToEnd);
			AIAsyncTaskBlueprintProxy->OnFail.AddDynamic(this, &ThisClass::OnMoveToEnd);
			Result = EBTNodeResult::InProgress;
		}
	}
	return Result;
}

EBTNodeResult::Type UBTTaskNode_MoveToIdealRange::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

void UBTTaskNode_MoveToIdealRange::OnMoveToEnd(EPathFollowingResult::Type MovementResult)
{
	if (MyOwnerComp)
	{
		FinishLatentTask(*MyOwnerComp, EBTNodeResult::Succeeded);
	}
}
