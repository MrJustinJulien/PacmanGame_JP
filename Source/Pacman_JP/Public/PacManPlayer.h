// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PacEntity.h"
#include "PacManPlayer.generated.h"

/**
 * 
 */
UCLASS()
class PACMAN_JP_API APacManPlayer : public APacEntity
{
	GENERATED_BODY()

public:

	APacManPlayer();

protected:

	virtual void BeginPlay() override;

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Gameplay")
	int32 Score;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();	
};
