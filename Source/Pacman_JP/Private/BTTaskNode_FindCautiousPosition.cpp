// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_FindCautiousPosition.h"
#include "Kismet/GameplayStatics.h"
#include "PacManPlayer.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTaskNode_FindCautiousPosition::UBTTaskNode_FindCautiousPosition()
{
	NodeName = "FindCautiousPosition";
}

EBTNodeResult::Type UBTTaskNode_FindCautiousPosition::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AICon = OwnerComp.GetAIOwner();
	if (!AICon) return EBTNodeResult::Failed;

	APawn* Pawn = AICon->GetPawn();
	if (!Pawn) return EBTNodeResult::Failed;

	APacManPlayer* Player = Cast<APacManPlayer>(UGameplayStatics::GetPlayerPawn(Pawn, 0));
	if (!Player) return EBTNodeResult::Failed;

	FVector PlayerLoc = Player->GetActorLocation();
	FVector GhostLoc = Pawn->GetActorLocation();

	float Distance = FVector::Dist(GhostLoc, PlayerLoc);
	FVector Dir = (PlayerLoc - GhostLoc).GetSafeNormal();

	FVector TargetLocation;

	if (Distance > ChaseRange)
	{
		// Poursuit Pac-Man
		TargetLocation = PlayerLoc;
	}
	else
	{
		// Trop proche -> s’enfuit dans la direction opposée
		TargetLocation = GhostLoc - Dir * 600.f;
	}

	// S’assure que la position est navigable
	FNavLocation Projected;
	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(Pawn->GetWorld());
	if (NavSys && NavSys->ProjectPointToNavigation(TargetLocation, Projected))
		TargetLocation = Projected.Location;

	UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();
	if (BB)
	{
		BB->SetValueAsVector(FName("TargetLocation"), TargetLocation);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}

