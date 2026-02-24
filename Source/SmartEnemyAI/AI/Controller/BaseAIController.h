// Copyright BanMing

#pragma once

#include "AIController.h"
#include "CoreMinimal.h"

#include "BaseAIController.generated.h"
class UBehaviorTree;
/**
 *
 */
UCLASS()
class SMARTENEMYAI_API ABaseAIController : public AAIController
{
	GENERATED_BODY()
protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

public:
	UFUNCTION(BlueprintCallable)
	void InitDefaultBT();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UBehaviorTree> DefaultBT;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName AttackTargetKeyName = "AttackTarget";
};
