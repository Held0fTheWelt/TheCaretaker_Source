/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "Actors/ScareSounds/ScareSoundActor.h"

#include "TimerManager.h"

#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/World.h"

#pragma region Constructor
AScareSoundActor::AScareSoundActor()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	if (TriggerVolume == nullptr)
		TriggerVolume = CreateDefaultSubobject<USphereComponent>(FName("TriggerVolume"));

	TriggerVolume->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	// This is a static object in scene
	TriggerVolume->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	// This trigger volume does ignore all channels by default
	TriggerVolume->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	// This volume responses to overlap events with pawns
	TriggerVolume->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	TriggerVolume->SetSphereRadius(300);

	RootComponent = TriggerVolume;

	if (ScareSoundComponent == nullptr)
		ScareSoundComponent = CreateDefaultSubobject<UAudioComponent>(FName("ScareSoundComponent"));

	ScareSoundComponent->SetupAttachment(RootComponent);

	MinSeconds = 5.f;
	MaxSeconds = 25.f;
}
#pragma endregion

#pragma region Begin Play
void AScareSoundActor::BeginPlay()
{
	Super::BeginPlay();
	
	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &AScareSoundActor::OnOverlapBegin);
	TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &AScareSoundActor::OnOverlapEnd);
}
#pragma endregion

#pragma region Trigger Volume
#pragma region On Overlap Begin
void AScareSoundActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{	
	GetWorld()->GetTimerManager().SetTimer(ScareSoundTimerHandle, this, &AScareSoundActor::OnScareSoundEvent, FMath::RandRange(MinSeconds, MaxSeconds), true);
}
#pragma endregion

#pragma region On Overlap End
void AScareSoundActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GetWorld()->GetTimerManager().ClearTimer(ScareSoundTimerHandle);
}
#pragma endregion
#pragma endregion

void AScareSoundActor::OnScareSoundEvent()
{
	GetWorld()->GetTimerManager().ClearTimer(ScareSoundTimerHandle);

	if (ScareSounds.ScareSounds.Num() > 0)
	{
		ScareSoundComponent->Sound = ScareSounds.ScareSounds[FMath::RandRange(0,ScareSounds.ScareSounds.Num()-1)];
		ScareSoundComponent->Play();

	}

	GetWorld()->GetTimerManager().SetTimer(ScareSoundTimerHandle, this, &AScareSoundActor::OnScareSoundEvent, FMath::RandRange(MinSeconds, MaxSeconds), true);
}


