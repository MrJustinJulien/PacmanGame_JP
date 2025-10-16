// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_FindPredictivePos.h"

#include "Kismet/GameplayStatics.h"
#include "PacManPlayer.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTaskNode_FindPredictivePos::UBTTaskNode_FindPredictivePos()
{
	NodeName = "Find Predictive Position";
}

EBTNodeResult::Type UBTTaskNode_FindPredictivePos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AICon = OwnerComp.GetAIOwner();
	if (!AICon) return EBTNodeResult::Failed;

	APawn* Pawn = AICon->GetPawn();
	if (!Pawn) return EBTNodeResult::Failed;

	APacManPlayer* Player = Cast<APacManPlayer>(UGameplayStatics::GetPlayerPawn(Pawn, 0));
	if (!Player) return EBTNodeResult::Failed;

	FVector PlayerLoc = Player->GetActorLocation();
	FVector ForwardDir = Player->GetActorForwardVector();

	// 4 cases (400 unités) devant Pac-Man
	FVector TargetLocation = PlayerLoc + ForwardDir * PredictDistance;

	// Vérifie si la position est valide sur le NavMesh
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