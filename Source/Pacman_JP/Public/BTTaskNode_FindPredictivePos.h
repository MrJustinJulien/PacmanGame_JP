// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_FindPredictivePos.generated.h"

/**
 * 
 */
UCLASS()
class PACMAN_JP_API UBTTaskNode_FindPredictivePos : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTaskNode_FindPredictivePos();

private:
	UPROPERTY()
	class UNavigationSystemV1* NavArea;

	UPROPERTY(EditAnywhere, Category = "AI")
	float PredictDistance = 400.f; // Distance devant le joueur

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};

