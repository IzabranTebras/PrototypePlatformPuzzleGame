// Fill out your copyright notice in the Description page of Project Settings.

#include "AttractorPoint.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AAttractorPoint::AAttractorPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Static mesh
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh component"));
	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Outter Sphere
	outterSphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Outter sphere component"));
	outterSphereComp->SetSphereRadius(3000.0f);
	outterSphereComp->SetupAttachment(meshComp);

	// Inner Sphere
	innerSphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Inner sphere component"));
	innerSphereComp->SetSphereRadius(100.0f);
	innerSphereComp->SetupAttachment(meshComp);

	// Bind to event
	innerSphereComp->OnComponentBeginOverlap.AddDynamic(this, &AAttractorPoint::OverlapInnerSphere);
}

void AAttractorPoint::OverlapInnerSphere(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, 
	bool bFromSweep, const FHitResult& SweepResult)
{
	if(otherActor)
	{
		otherActor->Destroy();
	}
}

// Called every frame
void AAttractorPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Find all overlapping components that can collide and may be physically simulating
	TArray<UPrimitiveComponent*> overlappingComps;
	outterSphereComp->GetOverlappingComponents(overlappingComps);

	for(int32 i=0; i<overlappingComps.Num(); ++i)
	{
		if(overlappingComps[i]->IsSimulatingPhysics())
		{
			overlappingComps[i]->AddRadialForce(GetActorLocation(), outterSphereComp->GetScaledSphereRadius(), forceStrength, ERadialImpulseFalloff::RIF_Constant, true);
		}
	}
}

