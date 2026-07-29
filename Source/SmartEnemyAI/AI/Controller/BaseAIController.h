// Copyright BanMing

#pragma once

#include "AI/AIDataTypes.h"
#include "AIController.h"
#include "CoreMinimal.h"
#include "Interfaces/AIControllerInterface.h"

#include "BaseAIController.generated.h"
class UBehaviorTree;
/**
 *
 */
UCLASS()
class SMARTENEMYAI_API ABaseAIController : public AAIController, public IAIControllerInterface
{
	GENERATED_BODY()

	ABaseAIController();

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

public:
	UFUNCTION(BlueprintCallable)
	void InitDefaultBT();

	void SetStatetoAttack_Implementation(AActor* Target);
	void SetStatetoPassive_Implementation();
	AActor* GetAttackTarget_Implementation();

public:
	UFUNCTION(BlueprintPure)
	bool CanSenseActor(AActor* Actor, EAISense AISense, FAIStimulus& OutAIStimulus);

	UFUNCTION(BlueprintPure)
	EAIState GetCurrentState() const;

protected:
	UFUNCTION()
	void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);

	void HandleSenseSight(AActor* Actor);
	void HandleSenseHearing(FVector Location);
	void HandleSenseDamage(AActor* Actor);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) TObjectPtr<UBehaviorTree> DefaultBT;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<class UAIPerceptionComponent> AIPerceptionComponent;

	UPROPERTY()
	TWeakObjectPtr<AActor> AttackTarget;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName AttackTargetKeyName = "AttackTarget";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName InvestigatingLocationKey = "InvestigatingLocation";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName StateKeyName = "State";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName AttackRadiusKeyName = "AttackRadius";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName DefendRadiusKeyName = "DefendRadius";
};
