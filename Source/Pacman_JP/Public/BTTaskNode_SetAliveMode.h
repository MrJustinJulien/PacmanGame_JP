// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BTTaskNode_SetAliveMode.generated.h"

/**
 * 
 */
UCLASS()
class PACMAN_JP_API UBTTaskNode_SetAliveMode : public UBTTaskNode
{
	GENERATED_BODY()
	
private:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
