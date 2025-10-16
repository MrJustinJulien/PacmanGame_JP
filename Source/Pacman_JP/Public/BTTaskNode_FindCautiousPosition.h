// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_FindCautiousPosition.generated.h"

/**
 * 
 */
UCLASS()
class PACMAN_JP_API UBTTaskNode_FindCautiousPosition : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTaskNode_FindCautiousPosition();

private:
	UPROPERTY()
	class UNavigationSystemV1* NavArea;

	UPROPERTY(EditAnywhere, Category = "AI")
	float ChaseRange = 600.f;

	UPROPERTY(EditAnywhere, Category = "AI")
	float RetreatRange = 400.f;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
