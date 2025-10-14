// Fill out your copyright notice in the Description page of Project Settings.


#include "PacmanGameMode.h"
#include "PacmanPlayerController.h"
#include "PacmanPlayer.h"

APacmanGameMode::APacmanGameMode()
{
	DefaultPawnClass = APacManPlayer::StaticClass();
	PlayerControllerClass = APacmanPlayerController::StaticClass();
}
