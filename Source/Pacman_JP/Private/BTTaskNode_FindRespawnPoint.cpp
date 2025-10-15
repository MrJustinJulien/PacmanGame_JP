// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_FindRespawnPoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Ghost.h"
#include "AIController.h"
#include "NavigationSystem.h"

EBTNodeResult::Type UBTTaskNode_FindRespawnPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AICon = OwnerComp.GetAIOwner();
	if (!AICon) return EBTNodeResult::Failed;

	AGhost* Ghost = Cast<AGhost>(AICon->GetPawn());
	if (!Ghost)
		return EBTNodeResult::Failed;

	TargetLocation = Ghost->SpawnLocation;

	UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();
	if (BB)
	{
		BB->SetValueAsVector(FName("TargetLocation"), TargetLocation);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}


