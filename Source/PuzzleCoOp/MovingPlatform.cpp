// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

#include "DrawDebugHelpers.h"

AMovingPlatform::AMovingPlatform()
{
    PrimaryActorTick.bCanEverTick = true;
    SetMobility(EComponentMobility::Movable);
    MoveDir = FVector::ForwardVector;
    // ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));
    // UStaticMesh* DefaultMesh = MeshAsset.Object;
    // GetStaticMeshComponent()->SetStaticMesh(DefaultMesh);
}

void AMovingPlatform::BeginPlay()
{
    Super::BeginPlay();
    
    if (HasAuthority())
    {
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
        FVector Location = GetActorLocation();
        Location += MoveDir * MoveSpeed * DeltaTime;
        SetActorLocation(Location);
    }

    DrawDebugLine(GetWorld(), GetActorLocation(),GetActorLocation() + MoveDir * 300, FColor::Red);
    
}

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


