// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLECOOP_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:

	AMovingPlatform();
	
protected:

	UPROPERTY(EditAnywhere, Category="Movement")
	FVector MoveDir = FVector::ForwardVector;

	UPROPERTY(EditAnywhere, Category="Movement")
	float MaxSpeed = 20.f;

	UPROPERTY(EditAnywhere, Category="Movement")
	float TurnCooldown = 3.f;
	
	float MoveSpeed = 20.f;
	
	UPROPERTY(Transient)
	FTimerHandle SwitchDirTimer;

	UFUNCTION()
	void SwitchDirections();
	
public:
	
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

private:

	void StartTurnAroundTimer();
	
};

