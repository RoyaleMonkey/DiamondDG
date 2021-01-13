// Copyright Epic Games, Inc. All Rights Reserved.

#include "DesignGateGameMode.h"
#include "DesignGateCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADesignGateGameMode::ADesignGateGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
