// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleGameInstance.h"

#define MSG(msg) GEngine->AddOnScreenDebugMessage(0, 5, FColor::Green, msg);

UPuzzleGameInstance::UPuzzleGameInstance(const FObjectInitializer& ObjectInitializer)
{
    UE_LOG(LogTemp, Warning, TEXT("Game Instance Constructed"));
}

void UPuzzleGameInstance::Init()
{
    Super::Init();
    UE_LOG(LogTemp, Warning, TEXT("Game Instance Init"));
}

void UPuzzleGameInstance::Host()
{
    
    MSG(TEXT("Hosting!"));

    UWorld* World = GetWorld();
    check(World);

    World->ServerTravel("/Game/Maps/Level_01?Listen");
    
}

void UPuzzleGameInstance::Join(const FString& Address)
{
    MSG(FString::Printf(TEXT("Joining: %s"), *Address));
}
