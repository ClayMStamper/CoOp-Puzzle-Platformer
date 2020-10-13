// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "ButtonPlatform.h"

#define MSG(msg) GEngine->AddOnScreenDebugMessage(0, 5, FColor::Green, msg);

UPuzzleGameInstance::UPuzzleGameInstance(const FObjectInitializer& ObjectInitializer)
{
    UE_LOG(LogTemp, Warning, TEXT("Game Instance Constructed"));
    const ConstructorHelpers::FClassFinder<UUserWidget> MenuBP(TEXT("/Game/MenuSystem/WBP_MainMenu"));
    MenuClass = MenuBP.Class;
    if(!ensure(MenuClass))
    {
        UE_LOG(LogTemp, Error, TEXT("Button Class not found"));
    } else
    {
        UE_LOG(LogTemp, Warning, TEXT("Found Class: %s"), *MenuClass->GetName());
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
    // World->GetNetDriver()->SetNetDriverName(NAME_)

    SetPlayInputMode();
    
}

void UPuzzleGameInstance::Join(const FString& Address)
{    
    MSG(FString::Printf(TEXT("Joining: %s"), *Address));
    GetFirstLocalPlayerController()->ClientTravel(Address, ETravelType::TRAVEL_Relative);
    
    SetPlayInputMode();
}

void UPuzzleGameInstance::LoadMenu()
{

    // create menu object
    UUserWidget* Menu = CreateWidget<UUserWidget>(this, MenuClass);
    check(Menu);

    SetMenuInputMode(Menu);
    
}

void UPuzzleGameInstance::SetMenuInputMode(UUserWidget* Menu)
{
    // setup menu params
    Menu->bIsFocusable = true;
    Menu->AddToViewport();
    FInputModeUIOnly InputMode;
    InputMode.SetWidgetToFocus(Menu->TakeWidget());
    InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

    // apply input mode to player
    APlayerController* PlayerController = GetFirstLocalPlayerController();
    PlayerController->SetInputMode(InputMode);
    PlayerController->bShowMouseCursor = true;   
}

void UPuzzleGameInstance::SetPlayInputMode()
{
    FInputModeGameOnly InputMode;
    APlayerController* PlayerController = GetFirstLocalPlayerController();
    PlayerController->SetInputMode(InputMode);
    PlayerController->bShowMouseCursor = false;   

}
