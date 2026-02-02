// Copyright BanMing

#pragma once

#include "Character/BaseCharacter.h"
#include "CoreMinimal.h"
#include "Navigation/PathFollowingComponent.h"

#include "EnemyCharacter.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogEnemyCharacter, Log, All);

struct FAIRequestID;
class AAIController;
/**
 *
 */
UCLASS()
class SMARTENEMYAI_API AEnemyCharacter : public ABaseCharacter
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

protected:
	UFUNCTION()
	void OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type MovementResult);

	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnMoveCompleted(EPathFollowingResult::Type MovementResult);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "AI")
	TObjectPtr<AAIController> AIController;

protected:
	FAIRequestID CurAIMoveRequestID;
};
