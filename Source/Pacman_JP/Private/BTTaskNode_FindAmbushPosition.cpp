// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_FindAmbushPosition.h"
#include "Kismet/GameplayStatics.h"
#include "PacManPlayer.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Ghost.h"
#include "EngineUtils.h" // pour TActorIterator

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

    // Position et direction du joueur
    FVector PlayerLoc = Player->GetActorLocation();
    FVector ForwardDir = Player->GetActorForwardVector();

    // Cherche Blinky dans le monde (parmi les AGhost)
    AGhost* Blinky = nullptr;
    for (TActorIterator<AGhost> It(Pawn->GetWorld()); It; ++It)
    {
        // heuristique simple : chercher "Blinky" dans le nom de l'acteur (ou utiliser un tag / propriété)
        if (It->GetName().Contains(TEXT("Blinky")))
        {
            Blinky = *It;
            break;
        }
    }

    // Si Blinky trouvé, applique le calcul "Inky" classique
    if (Blinky)
    {
        // point devant Pac-Man (200 unités, ajustable)
        FVector AheadOfPac = PlayerLoc + ForwardDir * 200.f;

        // vecteur Blinky -> AheadOfPac
        FVector Diff = AheadOfPac - Blinky->GetActorLocation();

        // cible = AheadOfPac + Diff (double le vecteur)
        TargetLocation = AheadOfPac + Diff;
    }
    else
    {
        // fallback : se comporter comme Pinky (point devant Pac-Man)
        TargetLocation = PlayerLoc + ForwardDir * 300.f;
    }

    // Projecte la target sur le NavMesh si possible
    FNavLocation Projected;
    UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(Pawn->GetWorld());
    if (NavSys)
    {
        if (NavSys->ProjectPointToNavigation(TargetLocation, Projected))
        {
            TargetLocation = Projected.Location;
        }
        // si échec, on laisse TargetLocation tel quel (BT suivant / MoveTo peut échouer proprement)
    }

    // Écrit dans le Blackboard
    UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();
    if (BB)
    {
        BB->SetValueAsVector(FName("TargetLocation"), TargetLocation);
        return EBTNodeResult::Succeeded;
    }

    return EBTNodeResult::Failed;
}




