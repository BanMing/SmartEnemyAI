// Copyright BanMing

#include "AI/Task/BTTask_ClearFocus.h"

#include "AIController.h"

UBTTask_ClearFocus::UBTTask_ClearFocus(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Clear Focus";
}

EBTNodeResult::Type UBTTask_ClearFocus::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = EBTNodeResult::Failed;

	if (AAIController* const MyController = OwnerComp.GetAIOwner())
	{
		MyController->ClearFocus(EAIFocusPriority::Gameplay);
		Result = EBTNodeResult::Succeeded;
	}

	return Result;
}
