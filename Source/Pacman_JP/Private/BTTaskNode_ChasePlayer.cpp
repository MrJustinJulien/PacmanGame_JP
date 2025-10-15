// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_ChasePlayer.h"
#include "AIControllerBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "PacManPlayer.h"

UBTTaskNode_ChasePlayer::UBTTaskNode_ChasePlayer()
{
	NodeName = "Chase Player";
}

EBTNodeResult::Type UBTTaskNode_ChasePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AAIControllerBase* Controller = Cast<AAIControllerBase>(OwnerComp.GetAIOwner());
    if (!Controller) return EBTNodeResult::Failed;

    UBlackboardComponent* BB = Controller->MyBlackboard;
    if (!BB) return EBTNodeResult::Failed;

    FVector TargetLocation = BB->GetValueAsVector(TEXT("TargetLocation"));
    APawn* ControlledPawn = Controller->GetPawn();
    if (!ControlledPawn) return EBTNodeResult::Failed;

    UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(ControlledPawn->GetWorld());
    if (NavSys)
    {
        FNavLocation Projected;
        if (NavSys->ProjectPointToNavigation(TargetLocation, Projected))
        {
            Controller->MoveToLocation(Projected.Location, 5.0f);
            return EBTNodeResult::Succeeded; // <--- important : relance la boucle
        }
    }

    return EBTNodeResult::Failed;
}


