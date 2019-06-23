// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPSProjectCharacter.h"
#include "FPSObjectiveActor.generated.h"

class USphereComponent;

UCLASS()
class FPSPROJECT_API AFPSObjectiveActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSObjectiveActor();

protected:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* meshComp;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* sphereComp;
	UPROPERTY(EditDefaultsOnly, Category = "FX")
	UParticleSystem* PickupFX;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void PlayEffects();

public:	

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
