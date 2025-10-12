// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Eatable.generated.h"

UCLASS(Abstract)
class PACMAN_JP_API AEatable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEatable();

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;	

	UPROPERTY(VisibleAnywhere, blueprintReadOnly, category = "Components")
	class UBoxComponent* BoxCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "Components")
	class UStaticMeshComponent* StaticMesh;

	virtual void OnEat();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent*
		OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
