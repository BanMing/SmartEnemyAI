// Copyright BanMing

#include "AI/Task/BTTask_SetStatePassive.h"

#include "AIController.h"
#include "Interfaces/AIControllerInterface.h"

UBTTask_SetStatePassive::UBTTask_SetStatePassive(const FObjectInitializer& ObjectInitializer)
{
	NodeName = "Set State To Passive";
}

EBTNodeResult::Type UBTTask_SetStatePassive::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = EBTNodeResult::Failed;
	if (AAIController* const MyController = OwnerComp.GetAIOwner())
	{
		IAIControllerInterface::Execute_SetStatetoPassive(MyController);
		Result = EBTNodeResult::Succeeded;
	}

	return Result;
}
