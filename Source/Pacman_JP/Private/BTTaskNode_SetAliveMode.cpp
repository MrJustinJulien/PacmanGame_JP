// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_SetAliveMode.h"
#include "AIController.h"
#include "Ghost.h"

EBTNodeResult::Type UBTTaskNode_SetAliveMode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AICon = OwnerComp.GetAIOwner();
	if (!AICon) return EBTNodeResult::Failed;

	AGhost* Ghost = Cast<AGhost>(AICon->GetPawn());
	if (!Ghost) return EBTNodeResult::Failed;

	Ghost->SetAliveMode();
	return EBTNodeResult::Succeeded;
}


