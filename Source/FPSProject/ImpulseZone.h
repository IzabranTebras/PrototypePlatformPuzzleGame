// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ImpulseZone.generated.h"

class UBoxComponent;

UCLASS()
class FPSPROJECT_API AImpulseZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AImpulseZone();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* meshComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UBoxComponent* boxComp;

	// Impulse force
	UPROPERTY(EditInstanceOnly, Category = "Impulse Zone")
		float forceStrength;

	// Impulse angle
	UPROPERTY(EditInstanceOnly, Category = "Impulse Zone")
		float forceAngle;

	// Effect particles
	UPROPERTY(EditDefaultsOnly, Category = "Impulse Zone")
		UParticleSystem* fx;

private:
	// Marked with ufunction to bind to overlap event
	UFUNCTION()
		void OverlapBox(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex,
			bool bFromSweep, const FHitResult& SweepResult);

};
