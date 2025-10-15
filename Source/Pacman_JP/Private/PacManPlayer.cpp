// Fill out your copyright notice in the Description page of Project Settings.


#include "PacManPlayer.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "Components/InputComponent.h"
#include "Components/BoxComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"

APacManPlayer::APacManPlayer()
{
    AutoPossessPlayer = EAutoReceiveInput::Player0;
    Score = 0;
    Vies = 3;

    bIsMoving = false;
    CurrentDir = EMoveDir::None;
    NextDir = EMoveDir::None;

    // Ajuste ta box pour bien détecter les murs
    if (CollisionBox)
    {
        CollisionBox->SetBoxExtent(FVector(40.f));
        CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
        CollisionBox->SetCollisionResponseToAllChannels(ECR_Block);
        CollisionBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
    }
}

void APacManPlayer::BeginPlay()
{
	Super::BeginPlay();

    APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if (PC)
    {
        PC->SetInputMode(FInputModeGameOnly());
        PC->bShowMouseCursor = false;           
        PC->Possess(this);                      
    }
}

void APacManPlayer::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // --- Vérifie si on peut appliquer la direction souhaitée ---
    if (NextDir != EMoveDir::None && NextDir != CurrentDir)
    {
        // On n'applique PAS si bloqué par un mur
        if (CanMoveInDirection(NextDir))
        {
            CurrentDir = NextDir;
            NextDir = EMoveDir::None;
            FaceDirection(CurrentDir);
        }
    }

    // --- Si la direction actuelle est bloquée, on arrête le mouvement ---
    if (CurrentDir == EMoveDir::None || !CanMoveInDirection(CurrentDir))
    {
        bIsMoving = false;
        return;
    }

    // --- Déplacement normal ---
    FVector DirVec = DirToVector(CurrentDir);
    FVector NewLoc = GetActorLocation() + DirVec * MoveSpeed * DeltaTime;
    SetActorLocation(NewLoc);
    bIsMoving = true;

    // --- Réalignement léger pour éviter le drift ---
    FVector SnapLoc = GetActorLocation();
    if (CurrentDir == EMoveDir::Up || CurrentDir == EMoveDir::Down)
        SnapLoc.Y = FMath::GridSnap(SnapLoc.Y, 10.f);
    else
        SnapLoc.X = FMath::GridSnap(SnapLoc.X, 10.f);
    SetActorLocation(SnapLoc);
}


void APacManPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APacManPlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APacManPlayer::MoveRight);
}

void APacManPlayer::MoveForward(float Value)
{
    if (Value > 0.5f)
        NextDir = EMoveDir::Up;
    else if (Value < -0.5f)
        NextDir = EMoveDir::Down;
}

void APacManPlayer::MoveRight(float Value)
{
    if (Value > 0.5f)
        NextDir = EMoveDir::Right;
    else if (Value < -0.5f)
        NextDir = EMoveDir::Left;
}

FVector APacManPlayer::DirToVector(EMoveDir Dir) const
{
    switch (Dir)
    {
    case EMoveDir::Up: return FVector(1, 0, 0);
    case EMoveDir::Down: return FVector(-1, 0, 0);
    case EMoveDir::Right: return FVector(0, 1, 0);
    case EMoveDir::Left: return FVector(0, -1, 0);
    default: return FVector::ZeroVector;
    }
}

bool APacManPlayer::CanMoveInDirection(EMoveDir Dir) const
{
    if (Dir == EMoveDir::None) return false;

    FVector Direction = DirToVector(Dir);
    FVector Start = GetActorLocation();

    float EffectiveDistance = TileSize * 0.45f;  // < 0.5f = avance un peu plus
    float OverrunDistance = 20.f;                // marge de tolérance (test visuel)

    FVector End = Start + Direction * (EffectiveDistance + OverrunDistance);


    FCollisionQueryParams Params;
    Params.AddIgnoredActor(this);

    // On utilise la vraie Box
    FHitResult Hit;
    FCollisionShape Shape = FCollisionShape::MakeBox(CollisionBox->GetScaledBoxExtent());
    bool bHit = GetWorld()->SweepSingleByChannel(
        Hit,
        Start,
        End,
        FQuat::Identity,
        ECC_WorldStatic,
        Shape,
        Params
    );

#if WITH_EDITOR
    FColor DebugColor = bHit ? FColor::Red : FColor::Green;
    DrawDebugLine(GetWorld(), Start, End, DebugColor, false, 0.1f, 0, 2.f);
#endif

    return !bHit;
}

void APacManPlayer::FaceDirection(EMoveDir Dir)
{
    if (Dir == EMoveDir::None) return;
    FVector DirVector = DirToVector(Dir);
    SetActorRotation(DirVector.Rotation());
}

void APacManPlayer::AutoAlignToGrid(EMoveDir Dir)
{
    FVector Loc = GetActorLocation();

    // Quand on veut aller verticalement, on aligne sur l’axe horizontal
    if (Dir == EMoveDir::Up || Dir == EMoveDir::Down)
    {
        float SnappedY = FMath::GridSnap(Loc.Y, TileSize / 2.f); // demi-case si ton map offset est ainsi
        if (FMath::Abs(Loc.Y - SnappedY) < SnapTolerance)
        {
            Loc.Y = SnappedY;
            SetActorLocation(Loc);
        }
    }
    // Quand on veut aller horizontalement, on aligne sur l’axe vertical
    else if (Dir == EMoveDir::Left || Dir == EMoveDir::Right)
    {
        float SnappedX = FMath::GridSnap(Loc.X, TileSize / 2.f);
        if (FMath::Abs(Loc.X - SnappedX) < SnapTolerance)
        {
            Loc.X = SnappedX;
            SetActorLocation(Loc);
        }
    }
}
