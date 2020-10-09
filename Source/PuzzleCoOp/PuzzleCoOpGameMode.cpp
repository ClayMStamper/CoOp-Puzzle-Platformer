// Copyright Epic Games, Inc. All Rights Reserved.

#include "PuzzleCoOpGameMode.h"
#include "PuzzleCoOpCharacter.h"
#include "UObject/ConstructorHelpers.h"

APuzzleCoOpGameMode::APuzzleCoOpGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
