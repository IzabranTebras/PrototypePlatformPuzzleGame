// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FPSProjectGameMode.generated.h"

UCLASS(minimalapi)
class AFPSProjectGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AFPSProjectGameMode();
	void CompleteMission(APawn* pawnInside);
	UFUNCTION(BlueprintImplementableEvent, Category = "GameMode")
	void OnCompleteMission(APawn* pawnInside);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Spectator")
	TSubclassOf<AActor> spectatingViewportClass;
};