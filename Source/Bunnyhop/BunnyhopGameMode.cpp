// Copyright Epic Games, Inc. All Rights Reserved.

#include "BunnyhopGameMode.h"
#include "BunnyhopHUD.h"
#include "BunnyhopCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABunnyhopGameMode::ABunnyhopGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ABunnyhopHUD::StaticClass();
}
