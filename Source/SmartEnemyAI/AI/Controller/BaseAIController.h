// Copyright BanMing

#pragma once

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
protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

public:
	UFUNCTION(BlueprintCallable)
	void InitDefaultBT();

	void SetStatetoAttack_Implementation(AActor* Target);
	void SetStatetoPassive_Implementation();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UBehaviorTree> DefaultBT;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName AttackTargetKeyName = "AttackTarget";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName StateKeyName = "State";
};
