// Copyright BanMing

#include "AI/Controller/BaseAIController.h"

#include "AI/AIDataTypes.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionSystem.h"
#include "Perception/AISense_Damage.h"
#include "Perception/AISense_Hearing.h"
#include "Perception/AISense_Sight.h"

ABaseAIController::ABaseAIController()
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("AIPerceptionComponent");
}

void ABaseAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	AIPerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &ThisClass::OnPerceptionUpdated);
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

bool ABaseAIController::CanSenseActor(AActor* Actor, EAISense AISense, FAIStimulus& OutAIStimulus)
{
	bool Res = false;
	FActorPerceptionBlueprintInfo Info;
	AIPerceptionComponent->GetActorsPerception(Actor, Info);
	for (const FAIStimulus& AIStimulus : Info.LastSensedStimuli)
	{
		if (TSubclassOf<UAISense> SenseClass = UAIPerceptionSystem::GetSenseClassForStimulus(this, AIStimulus))
		{
			switch (AISense)
			{
				case EAISense::Sight:
					if (SenseClass->IsChildOf(UAISense_Sight::StaticClass()))
					{
						OutAIStimulus = AIStimulus;
						return AIStimulus.WasSuccessfullySensed();
					}
				case EAISense::Hearing:
					if (SenseClass->IsChildOf(UAISense_Hearing::StaticClass()))
					{
						OutAIStimulus = AIStimulus;
						return AIStimulus.WasSuccessfullySensed();
					}
				case EAISense::Damage:
					if (SenseClass->IsChildOf(UAISense_Damage::StaticClass()))
					{
						OutAIStimulus = AIStimulus;
						return AIStimulus.WasSuccessfullySensed();
					}
			}
		}
	}
	return Res;
}

EAIState ABaseAIController::GetCurrentState() const
{
	return (EAIState) Blackboard->GetValueAsEnum(StateKeyName);
}

void ABaseAIController::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	for (AActor* Actor : UpdatedActors)
	{
		FAIStimulus OutAIStimulus;
		if (CanSenseActor(Actor, EAISense::Sight, OutAIStimulus))
		{
			HandleSenseSight(Actor);
		}

		if (CanSenseActor(Actor, EAISense::Hearing, OutAIStimulus))
		{
			HandleSenseHearing(OutAIStimulus.StimulusLocation);
		}
		if (CanSenseActor(Actor, EAISense::Damage, OutAIStimulus))
		{
			HandleSenseDamage(Actor);
		}
	}
}

void ABaseAIController::HandleSenseSight(AActor* Actor)
{
	EAIState AIState = GetCurrentState();
	if (AIState == EAIState::Investigating || AIState == EAIState::Passive)
	{
		ACharacter* TargetPlayer = UGameplayStatics::GetPlayerCharacter(this, 0);
		if (TargetPlayer == Actor)
		{
			Execute_SetStatetoAttack(this, Actor);
		}
	}
}

void ABaseAIController::HandleSenseHearing(FVector Location)
{
	EAIState AIState = GetCurrentState();
	if (AIState == EAIState::Investigating || AIState == EAIState::Passive)
	{
		Blackboard->ClearValue(AttackTargetKeyName);
		Blackboard->SetValueAsEnum(StateKeyName, (uint8) EAIState::Investigating);
		Blackboard->SetValueAsVector(InvestigatingLocationKey, Location);
	}
}

void ABaseAIController::HandleSenseDamage(AActor* Actor)
{
	EAIState AIState = GetCurrentState();
	if (AIState == EAIState::Investigating || AIState == EAIState::Passive)
	{
		Execute_SetStatetoAttack(this, Actor);
	}
}
