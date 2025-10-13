// Fill out your copyright notice in the Description page of Project Settings.


#include "PacEntity.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/BoxComponent.h"

// Sets default values
APacEntity::APacEntity()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
    SetRootComponent(CollisionBox);
    CollisionBox->SetCollisionProfileName(TEXT("Pawn"));
    CollisionBox->SetGenerateOverlapEvents(true);
    CollisionBox->SetSimulatePhysics(false);

    // === Mesh visuel ===
    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    Mesh->SetupAttachment(CollisionBox);
    Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    // === Mouvement ===
    PawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("PawnMovement"));
    PawnMovement->UpdatedComponent = CollisionBox;

}

// Called when the game starts or when spawned
void APacEntity::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APacEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APacEntity::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

