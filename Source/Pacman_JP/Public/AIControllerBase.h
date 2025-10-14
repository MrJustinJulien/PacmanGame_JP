// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "AIControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class PACMAN_JP_API AAIControllerBase : public AAIController
{
	GENERATED_BODY()
	
public:
	// --- Constructeur ---
	AAIControllerBase();

protected:
	// --- Référence au Behavior Tree asset (à assigner dans le Blueprint ou via Pawn contrôlé)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	UBehaviorTree* BehaviorTreeAsset;

public:
	// --- Composants Runtime ---
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	UBehaviorTreeComponent* BehaviorTreeComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	UBlackboardComponent* MyBlackboard;

public:
	// --- Surcharge appelée quand l’IA prend le contrôle d’un Pawn ---
	virtual void OnPossess(APawn* InPawn) override;
};

