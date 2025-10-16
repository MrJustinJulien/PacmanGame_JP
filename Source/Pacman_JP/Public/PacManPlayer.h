// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PacEntity.h"
#include "PacManPlayer.generated.h"

UENUM(BlueprintType)
enum class EMoveDir : uint8
{
	None,
	Up,
	Down,
	Left,
	Right
};

/**
 * 
 */
UCLASS()
class PACMAN_JP_API APacManPlayer : public APacEntity
{
	GENERATED_BODY()

public:

	APacManPlayer();

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MoveSpeed = 400.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float TileSize = 100.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	EMoveDir CurrentDir;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	EMoveDir NextDir;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	bool bIsMoving;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float SnapTolerance = 30.f;

	bool CanMoveInDirection(const FVector& Direction) const;
	void FaceDirection(const FVector& Direction);
	void AutoAlignToGrid(EMoveDir Dir);

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visuals")
	UMaterialInterface* M_Normal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visuals")
	UMaterialInterface* M_Dead;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Gameplay")
	int32 Score;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Gameplay")
	int32 Vies;

	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundBase* DamageSound;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "State")
	bool bIsInvincible;

	void MoveForward(float Value);
	void MoveRight(float Value);

	bool CanMoveInDirection(EMoveDir Dir) const;
	FVector DirToVector(EMoveDir Dir) const;
	FTimerHandle InvincibleTimerHandle;
	void FaceDirection(EMoveDir Dir);
	bool IsAlignedForTurn(EMoveDir DesiredDir) const;

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void ActivateInvincibility(float Duration);
	virtual void DeactivateInvincibility();


};
