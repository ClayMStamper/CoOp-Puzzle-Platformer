// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
    PrimaryActorTick.bCanEverTick = true;
    SetMobility(EComponentMobility::Movable);
    MoveDir = FVector::ForwardVector;
    MaxSpeed = 20.f;
    MoveSpeed = MaxSpeed;
}

void AMovingPlatform::BeginPlay()
{
    Super::BeginPlay();
    
    if (HasAuthority())
    {
        MoveSpeed = MaxSpeed;
        StartTurnAroundTimer();
    }
}

void AMovingPlatform::Tick(float DeltaTime)
{
    
    Super::Tick(DeltaTime);
    
    if (HasAuthority())
    {
        FVector Location = GetActorLocation();
        Location += MoveDir * MoveSpeed * DeltaTime;
        SetActorLocation(Location);
    }
}

void AMovingPlatform::SwitchDirections()
{
    MoveSpeed *= -1;
    StartTurnAroundTimer();
}

void AMovingPlatform::StartTurnAroundTimer()
{
    GetWorld()->GetTimerManager().SetTimer(SwitchDirTimer, this, &AMovingPlatform::SwitchDirections, TurnCooldown, false);
}


