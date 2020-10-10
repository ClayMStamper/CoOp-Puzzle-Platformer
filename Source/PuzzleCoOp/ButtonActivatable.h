// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ButtonActivatable.generated.h"


// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UButtonActivatable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PUZZLECOOP_API IButtonActivatable
{
	GENERATED_BODY()
	
public:

	UFUNCTION()
	virtual void Activate(UObject* ActivatedBy){};
	UFUNCTION()
	virtual void Deactivate(UObject* DeactivatedBy){};
	
};

