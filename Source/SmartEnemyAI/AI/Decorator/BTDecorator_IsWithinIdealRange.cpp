// Copyright BanMing

#include "AI/Decorator/BTDecorator_IsWithinIdealRange.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_IsWithinIdealRange::UBTDecorator_IsWithinIdealRange(const FObjectInitializer& ObjectInitializer)
{
	NodeName = TEXT("Is Within Ideal Range");
}

bool UBTDecorator_IsWithinIdealRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AAIController* const MyController = OwnerComp.GetAIOwner();
	AActor* Target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AttackTargetKey.SelectedKeyName));

	if (!MyController || !MyController->GetPawn() || !Target)
	{
		return false;
	}

	const float DistSquared = FVector::DistSquared(Target->GetActorLocation(), MyController->GetPawn()->GetActorLocation());
	const float IdealRange = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(IdealRangeKey.SelectedKeyName);
	return DistSquared - ErrorMargin * ErrorMargin <= IdealRange * IdealRange;
}
