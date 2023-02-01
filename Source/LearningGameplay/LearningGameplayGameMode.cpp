// Copyright Epic Games, Inc. All Rights Reserved.

#include "LearningGameplayGameMode.h"
#include "LearningGameplayCharacter.h"
#include "UObject/ConstructorHelpers.h"

ALearningGameplayGameMode::ALearningGameplayGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/MainChara_BP"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
