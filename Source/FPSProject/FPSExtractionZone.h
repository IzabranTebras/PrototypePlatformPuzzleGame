// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSExtractionZone.generated.h"

class UBoxComponent;

UCLASS()
class FPSPROJECT_API AFPSExtractionZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSExtractionZone();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* overlapBox;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UDecalComponent* decalComp;

	UFUNCTION()
	void HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

#pragma region Sounds
	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundBase* objectiveMissingSound;

	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundBase* missionCompleteSound;
#pragma endregion
};
