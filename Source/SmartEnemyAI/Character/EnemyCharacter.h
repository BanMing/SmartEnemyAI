// Copyright BanMing

#pragma once

#include "Character/BaseCharacter.h"
#include "CoreMinimal.h"
#include "Interfaces/EnemyInterface.h"
#include "Navigation/PathFollowingComponent.h"

#include "EnemyCharacter.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogEnemyCharacter, Log, All);

struct FAIRequestID;
class AAIController;
class UAnimMontage;
	/**
 *
 */
UCLASS()
class SMARTENEMYAI_API AEnemyCharacter : public ABaseCharacter, public IEnemyInterface
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void UnPossessed() override;

public:
	// UAIAsyncTaskBlueprintProxy* UAIBlueprintHelperLibrary::CreateMoveToProxyObject(...)
	UFUNCTION(BlueprintCallable)
	void ChasePlayer(float AcceptanceRadius);

public:
	// START IEnemyInterface START
	void Attack_Implementation();
	// END IEnemyInterface END

protected:
	UFUNCTION()
	void OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type MovementResult);

	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnMoveCompleted(EPathFollowingResult::Type MovementResult);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "AI")
	TObjectPtr<AAIController> AIController;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	TObjectPtr<UAnimMontage> AttackAnim;

protected:
	FAIRequestID CurAIMoveRequestID;
};
