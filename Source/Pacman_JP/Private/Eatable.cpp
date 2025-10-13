// Fill out your copyright notice in the Description page of Project Settings.


#include "Eatable.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "PacManPlayer.h"

// Sets default values
AEatable::AEatable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// --- Collision ---
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	RootComponent = BoxCollision;

	BoxCollision->SetCollisionProfileName("OverlapAllDynamic");
	BoxCollision->SetGenerateOverlapEvents(true);
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AEatable::OnOverlapBegin);

	// --- Mesh visuel ---
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(BoxCollision);
	StaticMesh->SetSimulatePhysics(false);
}

// Called when the game starts or when spawned
void AEatable::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void AEatable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEatable::OnEat(APacManPlayer* Player)
{
}

void AEatable::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent*
	OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor || OtherActor == this) return;

	APacManPlayer* Pacman = Cast<APacManPlayer>(OtherActor);
	if (Pacman)
	{
		// OnEat();
		Destroy();
	}
}

