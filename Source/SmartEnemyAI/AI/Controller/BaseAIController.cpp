// Copyright BanMing

#include "AI/Controller/BaseAIController.h"

#include "AI/AIDataTypes.h"
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
	Execute_SetStatetoPassive(this);
}

void ABaseAIController::SetStatetoAttack_Implementation(AActor* Target)
{
	Blackboard->SetValueAsObject(AttackTargetKeyName, Target);
	Blackboard->SetValueAsEnum(StateKeyName, (uint8) EAIState::Attacking);
}

void ABaseAIController::SetStatetoPassive_Implementation()
{
	Blackboard->ClearValue(AttackTargetKeyName);
	Blackboard->SetValueAsEnum(StateKeyName, (uint8) EAIState::Passive);
}
