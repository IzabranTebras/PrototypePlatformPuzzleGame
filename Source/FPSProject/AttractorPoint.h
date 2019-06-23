// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AttractorPoint.generated.h"

class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class FPSPROJECT_API AAttractorPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAttractorPoint();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* meshComp;

	// Inner sphere destroys 
	UPROPERTY(VisibleAnywhere, Category = "Components")
		USphereComponent* innerSphereComp;

	// Outter sphere attracts
	UPROPERTY(VisibleAnywhere, Category = "Components")
		USphereComponent* outterSphereComp;

	// Marked with ufunction to bind to overlap event
	UFUNCTION()
		void OverlapInnerSphere(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, 
			bool bFromSweep, const FHitResult& SweepResult);

public:	

	// Force to attract (negative to attract)
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	float forceStrength;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
