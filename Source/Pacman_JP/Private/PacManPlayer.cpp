// Fill out your copyright notice in the Description page of Project Settings.


#include "PacManPlayer.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/InputComponent.h"

APacManPlayer::APacManPlayer()
{
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	Score = 0;
}

void APacManPlayer::BeginPlay()
{
	Super::BeginPlay();
}

void APacManPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APacManPlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APacManPlayer::MoveRight);
}

void APacManPlayer::MoveForward(float Value)
{
	if (Value != 0.f)
	{
		UE_LOG(LogTemp, Warning, TEXT("MoveForward: %f"), Value);
		AddMovementInput(FVector::ForwardVector, Value);
	}
}

void APacManPlayer::MoveRight(float Value)
{
	if (Value != 0.f)
	{
		UE_LOG(LogTemp, Warning, TEXT("MoveRight: %f"), Value);
		AddMovementInput(FVector::RightVector, Value);
	}
}