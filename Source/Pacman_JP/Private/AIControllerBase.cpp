// Fill out your copyright notice in the Description page of Project Settings.


#include "AIControllerBase.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Pawn.h"

AAIControllerBase::AAIControllerBase()
{
	// Crée les composants du BehaviorTree et Blackboard
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	MyBlackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
}

void AAIControllerBase::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (!InPawn)
		return;

	// Essaie de trouver un BehaviorTree dans le Pawn (par exemple AGhost)
	if (!BehaviorTreeAsset)
	{
		// Certains de tes Pawns (comme les fantômes) auront un UPROPERTY TreeAsset exposé
		// On tente de le récupérer automatiquement
		UObject* TreeProperty = nullptr;

		// On regarde si le Pawn possède une propriété nommée "TreeAsset"
		UClass* PawnClass = InPawn->GetClass();
		FProperty* FoundProp = PawnClass->FindPropertyByName(TEXT("TreeAsset"));
		if (FoundProp)
		{
			TreeProperty = FoundProp->ContainerPtrToValuePtr<UObject>(InPawn);
			BehaviorTreeAsset = Cast<UBehaviorTree>(TreeProperty);
		}
	}

	// Démarre le Behavior Tree
	if (BehaviorTreeAsset)
	{
		if (BehaviorTreeAsset->BlackboardAsset)
		{
			MyBlackboard->InitializeBlackboard(*BehaviorTreeAsset->BlackboardAsset);
		}

		BehaviorTreeComponent->StartTree(*BehaviorTreeAsset);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIControllerBase: Aucun BehaviorTree assigné pour %s"), *GetName());
	}
}
