// Fill out your copyright notice in the Description page of Project Settings.


#include "PacEntity.h"

// Sets default values
APacEntity::APacEntity()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	SetRootComponent(CollisionBox);
	CollisionBox->SetBoxExtent(FVector(25.f, 25.f, 25.f));
	CollisionBox->SetCollisionProfileName(TEXT("Pawn"));
	CollisionBox->SetGenerateOverlapEvents(true);

	// --- Flipbook (sprite animé) ---
	Flipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Flipbook"));
	Flipbook->SetupAttachment(RootComponent);
	Flipbook->SetRelativeRotation(FRotator(90.f, 0.f, 0.f)); // face caméra top-down
	Flipbook->SetRelativeLocation(FVector(0.f, 0.f, 25.f));

	// --- Mouvement ---
	PawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("PawnMovement"));
	PawnMovement->UpdatedComponent = RootComponent;
	PawnMovement->MaxSpeed = 400.f;

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

