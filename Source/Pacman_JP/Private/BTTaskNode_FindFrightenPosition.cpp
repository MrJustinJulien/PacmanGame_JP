// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_FindFrightenPosition.h"
#include "Kismet/GameplayStatics.h"
#include "PacManPlayer.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTaskNode_FindFrightenPosition::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AICon = OwnerComp.GetAIOwner();
	if (!AICon) return EBTNodeResult::Failed;

	APawn* Pawn = AICon->GetPawn();
	if (!Pawn) return EBTNodeResult::Failed;

	APacManPlayer* Player = Cast<APacManPlayer>(UGameplayStatics::GetPlayerPawn(Pawn, 0));
	if (!Player) return EBTNodeResult::Failed;

	FVector PlayerLoc = Player->GetActorLocation();

	// Prend une direction aléatoire opposée au joueur
	FVector Dir = (Pawn->GetActorLocation() - PlayerLoc).GetSafeNormal();
	FVector RandomOffset = Dir * 600.f + FMath::VRand() * 200.f;
	TargetLocation = Pawn->GetActorLocation() + RandomOffset;

	UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();
	if (BB)
	{
		BB->SetValueAsVector(FName("TargetLocation"), TargetLocation);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}


