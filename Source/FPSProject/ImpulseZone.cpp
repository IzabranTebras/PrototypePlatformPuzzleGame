// Fill out your copyright notice in the Description page of Project Settings.

#include "ImpulseZone.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AImpulseZone::AImpulseZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Box trigger
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box trigger"));
	boxComp->SetBoxExtent(FVector(75, 75, 50));
	RootComponent = boxComp;

	// Static mesh
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh component"));
	meshComp->SetupAttachment(RootComponent);

	boxComp->OnComponentBeginOverlap.AddDynamic(this, &AImpulseZone::OverlapBox);

	forceStrength = 1500.0f;
	forceAngle = 45.0f;
}

void AImpulseZone::OverlapBox(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	FRotator impulseRotation = otherActor->GetActorRotation();
	impulseRotation.Pitch += forceAngle;
	FVector impulseVelocity = impulseRotation.Vector() * forceStrength;
	ACharacter* otherCharacter = Cast<ACharacter>(otherActor);

	// Check if is a player and impulse it
	if(otherCharacter)
	{
		otherCharacter->LaunchCharacter(impulseVelocity, true, true);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), fx, GetActorLocation());
	}
	else if (otherComp && otherComp->IsSimulatingPhysics())   // If not, check if it has simulatePhysics activated
	{
		otherComp->AddImpulse(impulseVelocity, NAME_None, true);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), fx, GetActorLocation());
	}
}

