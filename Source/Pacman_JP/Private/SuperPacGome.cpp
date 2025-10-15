// Fill out your copyright notice in the Description page of Project Settings.


#include "SuperPacGome.h"
#include "PacManPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "Ghost.h"

void ASuperPacGome::OnEat(APacManPlayer* Player)
{
	if(Player)
	{
		Player->Score += 50; // +50 points pour une super gomme

		// Active le mode "effrayé" pour tous les fantômes
		TArray<AActor*> Ghosts;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGhost::StaticClass(), Ghosts);

		for (AActor* GhostActor : Ghosts)
		{
			if (AGhost* Ghost = Cast<AGhost>(GhostActor))
			{
				Ghost->SetFrightenMode();
			}
		}
	}

	UGameplayStatics::PlaySoundAtLocation(this, PickUpEatSound, GetActorLocation());
	UGameplayStatics::PlaySoundAtLocation(this, TimerCooldown, GetActorLocation());
}