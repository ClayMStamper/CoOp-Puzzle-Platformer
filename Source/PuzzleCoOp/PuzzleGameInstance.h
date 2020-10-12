// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PuzzleGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLECOOP_API UPuzzleGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	
	UPuzzleGameInstance(const FObjectInitializer &ObjectInitializer);
	
	virtual void Init() override;

	UFUNCTION(Exec, BlueprintCallable)
	void Host();
	UFUNCTION(Exec, BlueprintCallable)
	void Join(const FString &Address);

	UFUNCTION(Exec, BlueprintCallable)
	void LoadMenu();

protected:

	TSubclassOf<class UUserWidget> MenuClass;

	void SetMenuInputMode(UUserWidget* Menu);
	void SetPlayInputMode();
	
};
