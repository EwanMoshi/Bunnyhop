// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BunnyhopHUD.generated.h"

UCLASS()
class ABunnyhopHUD : public AHUD
{
	GENERATED_BODY()

public:
	ABunnyhopHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

