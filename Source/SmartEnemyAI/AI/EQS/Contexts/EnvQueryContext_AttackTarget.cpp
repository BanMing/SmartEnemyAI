// Copyright BanMing

#include "AI/EQS/Contexts/EnvQueryContext_AttackTarget.h"

#include "AIController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "Interfaces/AIControllerInterface.h"
void UEnvQueryContext_AttackTarget::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	UObject* QuerierObject = QueryInstance.Owner.Get();
	AActor* QuerierActor = Cast<AActor>(QuerierObject);

	AAIController* AIController = UAIBlueprintHelperLibrary::GetAIController(QuerierActor);
	if (AIController->Implements<UAIControllerInterface>())
	{
		AActor* AttackTarget = IAIControllerInterface::Execute_GetAttackTarget(AIController);

		if (AttackTarget)
		{
			UEnvQueryItemType_Actor::SetContextHelper(ContextData, AttackTarget);
		}
	}
}
