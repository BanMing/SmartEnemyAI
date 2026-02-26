// Copyright BanMing
#include "AI/Task/BTTask_FocusTarget.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FocusTarget::UBTTask_FocusTarget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Focus Target";
	// 设置过滤
	AttackTargetKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_FocusTarget, AttackTargetKey), AActor::StaticClass());
}

EBTNodeResult::Type UBTTask_FocusTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = EBTNodeResult::Failed;

	AAIController* const MyController = OwnerComp.GetAIOwner();
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (!MyController || !Blackboard || !AttackTargetKey.IsSet())
	{
		return Result;
	}

	if (AActor* Target = Cast<AActor>(Blackboard->GetValueAsObject(AttackTargetKey.SelectedKeyName)))
	{
		MyController->SetFocus(Target);
		Result = EBTNodeResult::Succeeded;
	}

	return Result;
}

void UBTTask_FocusTarget::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

	// 从资产中解析选中的键名
	if (const UBlackboardData* BBAsset = GetBlackboardAsset())
	{
		AttackTargetKey.ResolveSelectedKey(*BBAsset);
	}
	else
	{
		AttackTargetKey.InvalidateResolvedKey();
	}
}
