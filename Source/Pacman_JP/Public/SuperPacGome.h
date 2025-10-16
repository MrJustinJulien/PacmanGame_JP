// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Eatable.h"
#include "SuperPacGome.generated.h"

/**
 * 
 */
UCLASS()
class PACMAN_JP_API ASuperPacGome : public AEatable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundBase* PickUpEatSound;

	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundBase* TimerCooldown;
	
private:
	virtual void OnEat(class APacManPlayer* Player) override;
};
