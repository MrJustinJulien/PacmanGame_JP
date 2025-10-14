// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_ChasePlayer.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PacManPlayer.h"

EBTNodeResult::Type UBTTaskNode_ChasePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AICon = OwnerComp.GetAIOwner();
	if (!AICon) return EBTNodeResult::Failed;

	APacManPlayer* Player = Cast<APacManPlayer>(UGameplayStatics::GetPlayerPawn(AICon, 0));
	if (!Player) return EBTNodeResult::Failed;

	TargetLocation = Player->GetActorLocation();

	UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();
	if (BB)
	{
		BB->SetValueAsVector(FName("TargetLocation"), TargetLocation);
	}

	AICon->MoveToLocation(TargetLocation, 5.0f, true);
	return EBTNodeResult::Succeeded;
}


