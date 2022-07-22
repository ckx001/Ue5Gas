// Copyright Epic Games, Inc. All Rights Reserved.

#include "Ue5GasGameMode.h"
#include "Ue5GasCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUe5GasGameMode::AUe5GasGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
