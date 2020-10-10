// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ButtonActivatable.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLECOOP_API AMovingPlatform : public AStaticMeshActor, public IButtonActivatable
{
	GENERATED_BODY()
	
public:

	AMovingPlatform();
	
protected:

	UPROPERTY(EditAnywhere, Category="Movement")
	float TimeToGoal = 3.f;

	UPROPERTY(EditAnywhere, Category="Movement", Meta=(MakeEditWidget=true))
	FVector TargetLocation;

	UPROPERTY(Transient, VisibleAnywhere)	
	float MoveSpeed = 20.f;
	UPROPERTY(Transient, VisibleAnywhere, Category="Movement")
	FVector MoveDir = FVector::ForwardVector;
	UPROPERTY(Transient)
	FTimerHandle SwitchDirTimer;
	UPROPERTY(EditAnywhere, Category="Movement")
	bool NeedsActivationToMove = false;

	UPROPERTY(VisibleAnywhere)
	bool bIsActivated = false;
	
	UFUNCTION()
	void SwitchDirections();
	
public:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Activate(UObject* ActivatedBy) override;
	virtual void Deactivate(UObject* DeactivatedBy) override;
	
private:

	void StartTurnAroundTimer();
	//when platform movement is inactive, timer needs to pause so it can stay on track
	void PauseTurnAroundTimer();
	void CalcMoveParams();

};

