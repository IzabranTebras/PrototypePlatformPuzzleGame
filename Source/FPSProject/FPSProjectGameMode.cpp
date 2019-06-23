// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "FPSProjectGameMode.h"
#include "FPSProjectHUD.h"
#include "FPSProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

AFPSProjectGameMode::AFPSProjectGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSProjectHUD::StaticClass();
}

void AFPSProjectGameMode::CompleteMission(APawn* pawnInside)
{
	if (pawnInside) 
	{
		pawnInside->DisableInput(nullptr);

		if (spectatingViewportClass)
		{
			TArray<AActor*> returnedActors;
			UGameplayStatics::GetAllActorsOfClass(this, spectatingViewportClass, returnedActors);

			// Change view target if any valid actor found
			if (returnedActors.Num() > 0)
			{
				AActor* newViewTarget = returnedActors[0];
				APlayerController* pc = Cast<APlayerController>(pawnInside->GetController());
				if (pc)
				{
					pc->SetViewTargetWithBlend(newViewTarget, 0.5f, EViewTargetBlendFunction::VTBlend_Cubic);
				}
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("SpectatingViewportClass is nullptr. Please update game mode class with valid subclass. Cannot change spectating view target."))
		}
		OnCompleteMission(pawnInside);
	}
}
