// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Eatable.h"
#include "PacGome.generated.h"

/**
 * 
 */
UCLASS()
class PACMAN_JP_API APacGome : public AEatable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundBase* EatSound;
	
private:
	virtual void OnEat(class APacManPlayer* Player) override;
};
