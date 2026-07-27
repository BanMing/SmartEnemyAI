// Copyright BanMing

#pragma once

#include "CoreMinimal.h"

#include "AIDataTypes.generated.h"

UENUM(BlueprintType)
enum class EMovementSpeed : uint8
{
	Idle,
	Walking,
	Jogging,
	Sprinting
};

UENUM(BlueprintType)
enum class EAIState : uint8
{
	Passive,
	Attacking,
	Frozen,
	Investigating,
	Dead
};

UENUM(BlueprintType)
enum class EAISense : uint8
{
	None,
	Sight,
	Hearing,
	Damage
};