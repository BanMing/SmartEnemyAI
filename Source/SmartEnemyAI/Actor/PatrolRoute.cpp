// Copyright BanMing

#include "Actor/PatrolRoute.h"

#include "Components/SplineComponent.h"

APatrolRoute::APatrolRoute()
{
	PrimaryActorTick.bCanEverTick = false;

	SplineComp = CreateDefaultSubobject<USplineComponent>("SplineComponent");
}

void APatrolRoute::IncrementPatrolRoute()
{
	PatrolIndex += Direction;
	if (PatrolIndex == SplineComp->GetNumberOfSplinePoints() - 1)
	{
		Direction = -1;
	}
	else if (PatrolIndex == 0)
	{
		Direction = 1;
	}
}

FVector APatrolRoute::GetSplinePointAsWorldPosition() const
{
	return SplineComp->GetLocationAtSplinePoint(PatrolIndex, ESplineCoordinateSpace::World);
}
