// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_FindAmbushPosition.h"
#include "Kismet/GameplayStatics.h"
#include "PacManPlayer.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTaskNode_FindAmbushPosition::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AICon = OwnerComp.GetAIOwner();
	if (!AICon) return EBTNodeResult::Failed;

	APacManPlayer* Player = Cast<APacManPlayer>(UGameplayStatics::GetPlayerPawn(AICon, 0));
	if (!Player) return EBTNodeResult::Failed;

	FVector PlayerLoc = Player->GetActorLocation();
	FVector ForwardDir = Player->GetActorForwardVector();
	TargetLocation = PlayerLoc + ForwardDir * 300.f; // 300 unités devant Pac-Man

	UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();
	if (BB)
	{
		BB->SetValueAsVector(FName("TargetLocation"), TargetLocation);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}


