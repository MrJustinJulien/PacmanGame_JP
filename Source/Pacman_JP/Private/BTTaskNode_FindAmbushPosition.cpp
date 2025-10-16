// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_FindAmbushPosition.h"
#include "Kismet/GameplayStatics.h"
#include "PacManPlayer.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Ghost.h"
#include "EngineUtils.h"

UBTTaskNode_FindAmbushPosition::UBTTaskNode_FindAmbushPosition()
{
    NodeName = TEXT("FindAmbushPosition");
}

EBTNodeResult::Type UBTTaskNode_FindAmbushPosition::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AAIController* AICon = OwnerComp.GetAIOwner();
    if (!AICon) return EBTNodeResult::Failed;

    APawn* Pawn = AICon->GetPawn();
    if (!Pawn) return EBTNodeResult::Failed;

    APacManPlayer* Player = Cast<APacManPlayer>(UGameplayStatics::GetPlayerPawn(Pawn->GetWorld(), 0));
    if (!Player) return EBTNodeResult::Failed;

    FVector PlayerLoc = Player->GetActorLocation();
    FVector ForwardDir = Player->GetActorForwardVector();

    // --- Trouve Blinky ---
    AGhost* Blinky = nullptr;
    for (TActorIterator<AGhost> It(Pawn->GetWorld()); It; ++It)
    {
        if (It->GetName().Contains(TEXT("Blinky")))
        {
            Blinky = *It;
            break;
        }
    }

    FVector DesiredLocation;

    if (Blinky)
    {
        FVector AheadOfPac = PlayerLoc + ForwardDir * 200.f;
        FVector Diff = AheadOfPac - Blinky->GetActorLocation();
        DesiredLocation = AheadOfPac + Diff; // Ambush point
    }
    else
    {
        DesiredLocation = PlayerLoc + ForwardDir * 300.f; // Fallback Pinky-like
    }

    // --- Securite NavMesh ---
    UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(Pawn->GetWorld());
    FNavLocation Projected;

    bool bFoundValidPoint = false;
    float ShrinkFactor = 1.0f;

    // On essaie de rapprocher progressivement le point de Pac-Man jusqu’a trouver un chemin valide
    while (!bFoundValidPoint && ShrinkFactor > 0.2f)
    {
        FVector TestLocation = PlayerLoc + (DesiredLocation - PlayerLoc) * ShrinkFactor;
        if (NavSys && NavSys->ProjectPointToNavigation(TestLocation, Projected, FVector(200.f, 200.f, 200.f)))
        {
            bFoundValidPoint = true;
            TargetLocation = Projected.Location;
        }
        else
        {
            ShrinkFactor -= 0.2f; // rapproche du joueur
        }
    }

    if (!bFoundValidPoint)
    {
        // Aucun point valide -> fallback simple : autour de Pac-Man
        TargetLocation = PlayerLoc + FMath::VRand() * 300.f;
        UE_LOG(LogTemp, Warning, TEXT("Inky: aucun point d'ambush valide trouve, fallback autour du joueur."));
    }

    // --- Enregistre dans le Blackboard ---
    if (UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent())
    {
        BB->SetValueAsVector(FName("TargetLocation"), TargetLocation);
        return EBTNodeResult::Succeeded;
    }

    return EBTNodeResult::Failed;
}





