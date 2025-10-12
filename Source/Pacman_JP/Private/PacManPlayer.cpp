// Fill out your copyright notice in the Description page of Project Settings.


#include "PacManPlayer.h"
#include "GameFramework/FloatingPawnMovement.h"

APacManPlayer::APacManPlayer()
{
	Score = 0;
}

void APacManPlayer::BeginPlay()
{
	Super::BeginPlay();
}

void APacManPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("MoveUp", IE_Pressed, this, &APacManPlayer::MoveUp);
	PlayerInputComponent->BindAction("MoveDown", IE_Pressed, this, &APacManPlayer::MoveDown);
	PlayerInputComponent->BindAction("MoveLeft", IE_Pressed, this, &APacManPlayer::MoveLeft);
	PlayerInputComponent->BindAction("MoveRight", IE_Pressed, this, &APacManPlayer::MoveRight);
}

void APacManPlayer::MoveUp()
{
	AddMovementInput(FVector::ForwardVector, 1.0f);
}

void APacManPlayer::MoveDown()
{
	AddMovementInput(-FVector::ForwardVector, 1.0f);
}

void APacManPlayer::MoveLeft()
{
	AddMovementInput(-FVector::RightVector, 1.0f);
}

void APacManPlayer::MoveRight()
{
	AddMovementInput(FVector::RightVector, 1.0f);
}