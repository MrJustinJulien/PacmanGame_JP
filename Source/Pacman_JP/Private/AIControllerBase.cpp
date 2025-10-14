// Fill out your copyright notice in the Description page of Project Settings.


#include "AIControllerBase.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Pawn.h"
#include "Ghost.h"

AAIControllerBase::AAIControllerBase()
{
	// Crée les composants du BehaviorTree et Blackboard
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	MyBlackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
}

void AAIControllerBase::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AGhost* Ghost = Cast<AGhost>(InPawn);
	if (Ghost && Ghost->TreeAsset)
	{
		MyBlackboard->InitializeBlackboard(*Ghost->TreeAsset->BlackboardAsset);
		BehaviorTreeComponent->StartTree(*Ghost->TreeAsset);
	}
}
