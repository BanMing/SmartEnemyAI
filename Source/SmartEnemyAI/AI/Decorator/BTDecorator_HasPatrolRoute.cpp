// Copyright BanMing

#include "AI/Decorator/BTDecorator_HasPatrolRoute.h"

#include "AIController.h"
#include "Actor/PatrolRoute.h"
#include "Interfaces/EnemyInterface.h"

UBTDecorator_HasPatrolRoute::UBTDecorator_HasPatrolRoute(const FObjectInitializer& ObjectInitializer)
{
	NodeName = TEXT("Has Patrol Route");
}

bool UBTDecorator_HasPatrolRoute::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	if (AAIController* const MyController = OwnerComp.GetAIOwner())
	{
		if (MyController->GetPawn()->Implements<UEnemyInterface>())
		{
			APatrolRoute* PatrolRoute = IEnemyInterface::Execute_GetPatrolRoute(MyController->GetPawn());
			return PatrolRoute != nullptr;
		}
	}

	return false;
}
