// Copyright BanMing

#pragma once

#include "AI/AIDataTypes.h"
#include "Character/BaseCharacter.h"
#include "CoreMinimal.h"
#include "Interfaces/EnemyInterface.h"
#include "Navigation/PathFollowingComponent.h"

#include "EnemyCharacter.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogEnemyCharacter, Log, All);

struct FAIRequestID;
class AAIController;
class UAnimMontage;
class APatrolRoute;

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
	FOnAttackEndSignature& GetOnAttackEndDelegate() override;
	FOnWeaponReadySignature& GetOnWeaponReadyDelegate() override;
	void Attack_Implementation();
	APatrolRoute* GetPatrolRoute_Implementation();
	float SetMovement_Implementation(EMovementSpeed MovementSpeed);
	// END IEnemyInterface END

protected:
	UFUNCTION()
	void OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type MovementResult);

	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnMoveCompleted(EPathFollowingResult::Type MovementResult);

public:
	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnAttackEndSignature OnAttackEnd;

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnWeaponReadySignature OnWeaponReady;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "AI")
	TObjectPtr<AAIController> AIController;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	TObjectPtr<APatrolRoute> PatrolRoute;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
	TObjectPtr<UAnimMontage> AttackAnim;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	TMap<EMovementSpeed, float> MovementSpeedMap;

protected:
	FAIRequestID CurAIMoveRequestID;
};
