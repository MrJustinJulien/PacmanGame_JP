// Fill out your copyright notice in the Description page of Project Settings.


#include "PacmanPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "PacManPlayer.h"
#include "Camera/CameraActor.h"

APacmanPlayerController::APacmanPlayerController()
{
	bShowMouseCursor = false;
	bEnableClickEvents = false;
	bEnableTouchEvents = false;
	bAutoManageActiveCameraTarget = false;
}

void APacmanPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ACameraActor* Camera = Cast<ACameraActor>(UGameplayStatics::GetActorOfClass(GetWorld(), ACameraActor::StaticClass()));
	if (Camera)
	{
		SetViewTarget(Camera);
	}
}