// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

#include "DrawDebugHelpers.h"

AMovingPlatform::AMovingPlatform()
{
    PrimaryActorTick.bCanEverTick = true;
    SetMobility(EComponentMobility::Movable);
    MoveDir = FVector::ForwardVector;
}

void AMovingPlatform::BeginPlay()
{
    Super::BeginPlay();

    if (HasAuthority())
    {

        // if it doesn't rely on activation, then start as activated
        bIsActivated = !NeedsActivationToMove;
    
        SetReplicates(true);
        SetReplicateMovement(true);

        //set MoveSpeed and MoveDir
        CalcMoveParams();
        
        StartTurnAroundTimer();
    }
}

void AMovingPlatform::Tick(float DeltaTime)
{
    
    Super::Tick(DeltaTime);
    
    if (HasAuthority())
    {
        // if activated, then move
        if (bIsActivated)
        {
            FVector Location = GetActorLocation();
            Location += MoveDir * MoveSpeed * DeltaTime;
            SetActorLocation(Location);
        }
    }

}

void AMovingPlatform::Activate_Implementation(UObject* ActivatedBy)
{
    UE_LOG(LogTemp, Warning, TEXT("I, %s have been activated!"), *GetOwner()->GetName());
}

void AMovingPlatform::Deactivate_Implementation(UObject* DeactivatedBy)
{
}

//
// void AMovingPlatform::Activate(AButtonPlatform* ActivatedBy)
// {
//     if (HasAuthority())
//         bIsActivated = true;
// }

void AMovingPlatform::SwitchDirections()
{
    MoveSpeed *= -1;
    StartTurnAroundTimer();
}

void AMovingPlatform::StartTurnAroundTimer()
{
    GetWorld()->GetTimerManager().SetTimer(SwitchDirTimer, this, &AMovingPlatform::SwitchDirections, TimeToGoal, false);
}

void AMovingPlatform::CalcMoveParams()
{
    // calc move direction towards target
    const FVector TargetWorldPos = GetTransform().TransformPosition(TargetLocation);
    MoveDir = (TargetWorldPos- GetActorLocation()).GetSafeNormal();

    // calc move speed needed to get to target in "TimeToGoal" time
    const float DistanceToTravel = FVector::Distance(TargetWorldPos, GetActorLocation());
    MoveSpeed = DistanceToTravel / TimeToGoal;
}


