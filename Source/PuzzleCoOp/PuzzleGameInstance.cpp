// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "ButtonPlatform.h"

#define MSG(msg) GEngine->AddOnScreenDebugMessage(0, 5, FColor::Green, msg);

UPuzzleGameInstance::UPuzzleGameInstance(const FObjectInitializer& ObjectInitializer)
{
    UE_LOG(LogTemp, Warning, TEXT("Game Instance Constructed"));
    const ConstructorHelpers::FClassFinder<UUserWidget> MenuBP(TEXT("/Game/MenuSystem/WBP_MainMenu"));
    if(!ensure(MenuBP.Class))
    {
        UE_LOG(LogTemp, Error, TEXT("Button Class not found"));
    } else
    {
        UE_LOG(LogTemp, Warning, TEXT("Found Class: %s"), *MenuBP.Class->GetName());
    }
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

    APlayerController* PlayerController = GetFirstLocalPlayerController();
    PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Relative);
}
