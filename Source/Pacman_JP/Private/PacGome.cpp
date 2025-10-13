// Fill out your copyright notice in the Description page of Project Settings.


#include "PacGome.h"
#include "PacManPlayer.h"
#include "Kismet/GameplayStatics.h"

void APacGome::OnEat(APacManPlayer* Player)
{
	if (Player)
	{
		Player->Score += 10; // +10 points pour une gomme normale
		UE_LOG(LogTemp, Log, TEXT("Pac-Gomme mangée : Score = %d"), Player->Score);
	}

	// UGameplayStatics::PlaySoundAtLocation(this, EatSound, GetActorLocation());
}