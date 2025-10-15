// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_FindPlayerLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PacManPlayer.h"

EBTNodeResult::Type UBTTaskNode_FindPlayerLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    APacManPlayer* Player = Cast<APacManPlayer>(UGameplayStatics::GetPlayerPawn(OwnerComp.GetWorld(), 0));
    if (!Player)
        return EBTNodeResult::Failed;

    FVector PlayerLoc = Player->GetActorLocation();
    PlayerLoc.X = FMath::GridSnap(PlayerLoc.X, 100.f);
    PlayerLoc.Y = FMath::GridSnap(PlayerLoc.Y, 100.f);

    OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("TargetLocation"), PlayerLoc);

    return EBTNodeResult::Succeeded; // On passe à la tâche suivante
}

