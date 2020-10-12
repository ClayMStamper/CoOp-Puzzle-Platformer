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

            if (FVector::Distance(Location, CurrentGoal) < 10.f)
            {
                SwitchDirections();
            }
        }
    }

}

void AMovingPlatform::Activate(UObject* ActivatedBy)
{
    if (bIsActivated)
        return;
    
    bIsActivated = true;
}

void AMovingPlatform::Deactivate(UObject* DeactivatedBy)
{
    bIsActivated = false;
}

void AMovingPlatform::SwitchDirections()
{
    MoveSpeed *= -1;
    // toggle current goal
    CurrentGoal = CurrentGoal == StartPos ? TargetWorldPos : StartPos; 
}

//called once at the start
void AMovingPlatform::CalcMoveParams()
{

    StartPos = GetActorLocation();
    
    // calc move direction towards target
    TargetWorldPos = GetTransform().TransformPosition(TargetLocation);
    MoveDir = (TargetWorldPos- GetActorLocation()).GetSafeNormal();
    CurrentGoal = TargetWorldPos;

    // calc move speed needed to get to target in "TimeToGoal" time
    const float DistanceToTravel = FVector::Distance(TargetWorldPos, GetActorLocation());
    MoveSpeed = DistanceToTravel / TimeToGoal;
}


