// Copyright BanMing

#include "AI/Controller/BaseAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

void ABaseAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void ABaseAIController::OnUnPossess()
{
	Super::OnUnPossess();
}

void ABaseAIController::InitDefaultBT()
{
	RunBehaviorTree(DefaultBT);
	ACharacter* TargetPlayer = UGameplayStatics::GetPlayerCharacter(this, 0);
	Blackboard->SetValueAsObject(AttackTargetKeyName, TargetPlayer);
}
