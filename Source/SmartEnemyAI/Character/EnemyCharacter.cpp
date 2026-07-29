// Copyright BanMing
#include "Character/EnemyCharacter.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"

DEFINE_LOG_CATEGORY(LogEnemyCharacter);

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	AIController = Cast<AAIController>(NewController);
	if (AIController)
	{
		AIController->ReceiveMoveCompleted.AddDynamic(this, &ThisClass::OnMoveCompleted);
	}
}

void AEnemyCharacter::UnPossessed()
{
	if (AIController)
	{
		AIController->ReceiveMoveCompleted.RemoveDynamic(this, &ThisClass::OnMoveCompleted);
		AIController = nullptr;
	}
	Super::UnPossessed();
}

void AEnemyCharacter::ChasePlayer(float AcceptanceRadius)
{
	if (!AIController)
	{
		UE_LOG(LogEnemyCharacter, Warning, TEXT("[%s] AIController is NULL !!!"), *GetNameSafe(this));
		return;
	}
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(this, 0);
	FAIMoveRequest MoveRequest;
	MoveRequest.SetGoalActor(Player);
	MoveRequest.SetAcceptanceRadius(AcceptanceRadius);
	FPathFollowingRequestResult ResultData = AIController->MoveTo(MoveRequest);
	switch (ResultData.Code)
	{
		case EPathFollowingRequestResult::RequestSuccessful:
			CurAIMoveRequestID = ResultData.MoveId;
			break;
		case EPathFollowingRequestResult::AlreadyAtGoal:
			OnMoveCompleted(CurAIMoveRequestID, EPathFollowingResult::Success);
			break;

		case EPathFollowingRequestResult::Failed:
		default:
			OnMoveCompleted(CurAIMoveRequestID, EPathFollowingResult::Aborted);
			break;
	}
}

void AEnemyCharacter::Attack_Implementation()
{
	PlayAnimMontage(AttackAnim);
}

APatrolRoute* AEnemyCharacter::GetPatrolRoute_Implementation()
{
	return PatrolRoute;
}

float AEnemyCharacter::SetMovement_Implementation(EMovementSpeed MovementSpeed)
{
	GetCharacterMovement()->MaxWalkSpeed = MovementSpeedMap[MovementSpeed];

	return MovementSpeedMap[MovementSpeed];
}

void AEnemyCharacter::GetIdealRange_Implementation(float& OutAttackRadius, float& OutDefendRadius)
{
	OutAttackRadius = AttackRadius;
	OutDefendRadius = DefendRadius;
}

FOnAttackEndSignature& AEnemyCharacter::GetOnAttackEndDelegate()
{
	return OnAttackEnd;
}

FOnWeaponReadySignature& AEnemyCharacter::GetOnWeaponReadyDelegate()
{
	return OnWeaponReady;
}

void AEnemyCharacter::OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type MovementResult)
{
	if (!RequestID.IsEquivalent(CurAIMoveRequestID))
	{
		UE_LOG(LogEnemyCharacter, Log, TEXT("OnMoveCompleted [%s] RequestID[%s] and CurAIMoveRequestID[%s] are not same!"), *GetNameSafe(this), *RequestID.ToString(), *CurAIMoveRequestID.ToString());
		return;
	}

	switch (MovementResult)
	{
		case EPathFollowingResult::Success:
			UE_LOG(LogEnemyCharacter, Log, TEXT("OnMoveCompleted [%s] Move completed successfully!"), *GetNameSafe(this));
			break;
		case EPathFollowingResult::Blocked:
			UE_LOG(LogEnemyCharacter, Warning, TEXT("OnMoveCompleted [%s] Move was blocked!"), *GetNameSafe(this));
			break;
		case EPathFollowingResult::OffPath:
			UE_LOG(LogEnemyCharacter, Warning, TEXT("OnMoveCompleted [%s] Character went off path!"), *GetNameSafe(this));
			break;
		case EPathFollowingResult::Aborted:
			UE_LOG(LogEnemyCharacter, Warning, TEXT("OnMoveCompleted [%s] Move was aborted!"), *GetNameSafe(this));
			break;
		case EPathFollowingResult::Invalid:
			UE_LOG(LogEnemyCharacter, Error, TEXT("OnMoveCompleted [%s] Invalid move request!"), *GetNameSafe(this));
			break;
	}
	BP_OnMoveCompleted(MovementResult);
}
