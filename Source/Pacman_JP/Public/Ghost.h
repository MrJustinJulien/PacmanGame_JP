// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PacEntity.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Ghost.generated.h"

/**
 * 
 */
UCLASS()
class PACMAN_JP_API AGhost : public APacEntity
{
	GENERATED_BODY()

public:
	// --- Constructeur ---
	AGhost();

protected:
	// --- Overrides Unreal ---
	virtual void BeginPlay() override;

private:
	// --- Collision event ---
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

public:
	virtual void Tick(float DeltaTime) override;
	// === VISUELS ===
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Visuals")
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visuals")
	UMaterialInterface* M_Normal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visuals")
	UMaterialInterface* M_Frightened;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visuals")
	UMaterialInterface* M_Dead;

	// === ÉTATS ===
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "State")
	bool IsDead;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "State")
	bool IsFrightened;

	// === AI ===
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	class UBehaviorTree* TreeAsset;

	// === MÉTHODES D’ÉTAT ===
	void SetAliveMode();

	void SetDeadMode();

	void SetFrightenMode();

	void UpdateBlackboard();

	// Le fantôme ne reçoit pas d’input, mais on laisse l’override vide
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
};
