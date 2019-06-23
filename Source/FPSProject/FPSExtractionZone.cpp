// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSExtractionZone.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "FPSProjectCharacter.h"
#include "FPSProjectGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFPSExtractionZone::AFPSExtractionZone()
{
	// Create extraction zone box
	overlapBox = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapBoxComponent"));
	overlapBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	overlapBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	overlapBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	overlapBox->SetBoxExtent(FVector(200.0f));
	RootComponent = overlapBox;
	overlapBox->OnComponentBeginOverlap.AddDynamic(this, &AFPSExtractionZone::HandleOverlap);

	decalComp = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalComp"));
	decalComp->DecalSize = FVector(200.0f, 200.0f, 200.0f);
	decalComp->SetupAttachment(RootComponent);
}

void AFPSExtractionZone::HandleOverlap(UPrimitiveComponent * overlappedComponent, AActor * otherActor, UPrimitiveComponent * otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult & sweepResult)
{
	AFPSProjectCharacter* myPawn = Cast<AFPSProjectCharacter>(otherActor);
	if (myPawn)
	{
		if (myPawn->isCarryingObjective) 
		{
			AFPSProjectGameMode* gameMode = Cast<AFPSProjectGameMode>(GetWorld()->GetAuthGameMode());
			if (gameMode)
			{
				gameMode->CompleteMission(myPawn);
				UGameplayStatics::PlaySound2D(this, missionCompleteSound);
			}
		}
		else
		{
			UGameplayStatics::PlaySound2D(this, objectiveMissingSound);
		}

		UE_LOG(LogTemp, Log, TEXT("Overlapped zone"));
	}
}

