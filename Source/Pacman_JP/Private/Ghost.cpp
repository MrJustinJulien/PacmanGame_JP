// Fill out your copyright notice in the Description page of Project Settings.

#include "Ghost.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
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

	M_Normal = nullptr;
	M_Frightened = nullptr;
	M_Dead = nullptr;
}

void AGhost::BeginPlay()
{
	Super::BeginPlay();

	SpawnLocation = GetActorLocation();

	if (AAIControllerBase* AIC = Cast<AAIControllerBase>(GetController()))
	{
		AIC->RunBehaviorTree(TreeAsset);
		UpdateBlackboard();
	}

	if (M_Normal)
		Mesh->SetMaterial(0, M_Normal);
}

void AGhost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateBlackboard();
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
		else if (!IsDead && Pacman->Vies != 1)
		{
			Pacman->Vies -= 1;
		}
		else if(Pacman->Vies == 1)
		{
			Pacman->Destroy();
		}
	}
}

void AGhost::SetAliveMode()
{
	IsDead = false;
	IsFrightened = false;
	PawnMovement->MaxSpeed = 300.f;

	if (M_Normal) Mesh->SetMaterial(0, M_Normal);

	UpdateBlackboard();	
}

void AGhost::SetDeadMode()
{
	IsDead = true;
	IsFrightened = false;
	PawnMovement->MaxSpeed = 500.f;

	if (M_Dead) Mesh->SetMaterial(0, M_Dead);

	UpdateBlackboard();

	// Planifie le retour en vie après 3 secondes
	GetWorldTimerManager().ClearTimer(RespawnTimerHandle);
	GetWorldTimerManager().SetTimer(
		RespawnTimerHandle,
		this,
		&AGhost::SetAliveMode,
		10.0f,
		false
	);
}

void AGhost::SetFrightenMode()
{
	IsFrightened = true;
	IsDead = false;
	PawnMovement->MaxSpeed = 200.f;

	if (M_Frightened) Mesh->SetMaterial(0, M_Frightened);

	GetWorldTimerManager().ClearTimer(FrightenTimerHandle);

	GetWorldTimerManager().SetTimer(
		FrightenTimerHandle,
		this,
		&AGhost::EndFrightenMode,
		10.0f,
		false
	);

	UpdateBlackboard();
}

void AGhost::EndFrightenMode()
{
	// S’il est mort entre-temps, ne rien faire
	if (IsDead)
		return;

	IsFrightened = false;
	PawnMovement->MaxSpeed = 300.f;

	if (M_Normal)
		Mesh->SetMaterial(0, M_Normal);

	UpdateBlackboard();
}

void AGhost::UpdateBlackboard()
{
	AAIControllerBase* AIC = Cast<AAIControllerBase>(GetController());
	if (AIC && AIC->MyBlackboard)
	{
		AIC->MyBlackboard->SetValueAsBool(TEXT("IsFrightened"), IsFrightened);
		AIC->MyBlackboard->SetValueAsBool(TEXT("IsDead"), IsDead);

		APacManPlayer* Player = Cast<APacManPlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
		AIC->MyBlackboard->SetValueAsObject(TEXT("PlayerActor"), Player);
	}
}

void AGhost::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
}


