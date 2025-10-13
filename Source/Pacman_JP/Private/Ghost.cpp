// Fill out your copyright notice in the Description page of Project Settings.


#include "Ghost.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PacManPlayer.h"
#include "AIControllerBase.h"

AGhost::AGhost()
{
	PrimaryActorTick.bCanEverTick = true;

	IsDead = false;
	IsFrightened = false;

	// Collision : écouter les overlaps avec Pac-Man
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AGhost::OnOverlap);
	CollisionBox->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Ignore);
}

void AGhost::BeginPlay()
{
	Super::BeginPlay();

	Mesh->SetVisibility(true);

	// Le AIControllerBase s’occupe de lancer le Behavior Tree,
	// donc pas besoin d’appeler RunBehaviorTree ici.
}

void AGhost::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	// Vérifie si on a touché Pac-Man
	if (APacManPlayer* Pacman = Cast<APacManPlayer>(OtherActor))
	{
		if (IsFrightened)
		{
			// Pac-Man mange le fantôme
			SetDeadMode();
			Pacman->Score += 200; // Bonus
		}
		else if (!IsDead)
		{
			// Pac-Man est touché (perte de vie à gérer via GameMode)
			UE_LOG(LogTemp, Warning, TEXT("Pac-Man touché par un fantôme !"));
		}
	}
}

void AGhost::SetAliveMode()
{
	IsDead = false;
	IsFrightened = false;
	Mesh->SetVisibility(true);
	if (DeadMesh) DeadMesh->SetVisibility(false);
	if (FrightenedMesh) FrightenedMesh->SetVisibility(false);
}

void AGhost::SetDeadMode()
{
	IsDead = true;
	IsFrightened = false;
	if (DeadMesh) DeadMesh->SetVisibility(true);
	Mesh->SetVisibility(false);
	if (FrightenedMesh) FrightenedMesh->SetVisibility(false);
}

void AGhost::SetFrightenMode()
{
	IsFrightened = true;
	IsDead = false;
	if (FrightenedMesh) FrightenedMesh->SetVisibility(true);
	Mesh->SetVisibility(false);
	if (DeadMesh) DeadMesh->SetVisibility(false);
}

void AGhost::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
}


