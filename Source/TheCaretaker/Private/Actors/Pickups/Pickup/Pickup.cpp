/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#include "Actors/Pickups/Pickup/Pickup.h"

#include "TimerManager.h"

#include "Actors/Pickups/PowerUp/PowerUp.h"
#include "Components/SphereComponent.h"
#include "Components/DecalComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Log/GlobalLog.h"
#include "Particles/ParticleSystemComponent.h"

APickup::APickup()
{
	PrimaryActorTick.bCanEverTick = false;
	
	if (!TriggerVolume)
		TriggerVolume = CreateDefaultSubobject<USphereComponent>(FName("TriggerVolumeComponent"));

	TriggerVolume->SetSphereRadius(75);
	TriggerVolume->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TriggerVolume->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	TriggerVolume->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	TriggerVolume->SetupAttachment(RootComponent);

	RootComponent = TriggerVolume;
	if (!Decals)
		Decals = CreateDefaultSubobject<UDecalComponent>(FName("DecalsComponent"));

	Decals->SetRelativeRotation(FRotator(90, 0.f, 0.f));
	Decals->DecalSize = FVector(64,75,75);
	Decals->SetupAttachment(RootComponent);

	CoolDownDuration = 5;

	ParticleDelayDuration = 1.f;

	if (bUsesMultiplayer)
	{
		SetReplicates(true);
	}

	if (ParticleSystemComponent == nullptr)
		ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(FName("ParticleSystemComponent"));

	ParticleSystemComponent->SetupAttachment(RootComponent);
	ParticleSystemComponent->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	ParticleSystemComponent->SetRelativeScale3D(FVector(.5f, .5f, .5f));

	CurrentPowerUpClass = nullptr;
	CurrentPowerUpActor = nullptr;

	bSpawnOnBeginPlay = true;
	ReactsOnAllPlayers = false;
}


void APickup::BeginPlay()
{
	Super::BeginPlay();

	if (!bSpawnOnBeginPlay)
	{
		return;
	}

	if (!bUsesMultiplayer || GetLocalRole() == ROLE_Authority)
	{
		bOnStart = true;
		Respawn();
	}
}

void APickup::PlayParticleEffect()
{
	ParticleSystemComponent->Activate();
	GetWorldTimerManager().SetTimer(TimerHandle_RespawnPickup, this, &APickup::Respawn, ParticleDelayDuration);
}

void APickup::Respawn()
{
	if (CurrentPowerUpClass == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("PowerUpTemplate is not nullptr in %s.\n This shouldn't happen."), *GetName());
		return;
	}

	if (CurrentPowerUpActor != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("PowerUpActor is not nullptr in %s.\n This shouldn't happen."), *GetName());
		if (bOnStart)
		{
			CurrentPowerUpActor->Destroy();
			CurrentPowerUpActor = nullptr;
			bOnStart = false;
		}
		return;
	}

	if (ParticleSystemComponent->Template != nullptr)
	{
		ParticleSystemComponent->Deactivate();
	}

	FActorSpawnParameters SpawnParams;

	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	CurrentPowerUpActor = GetWorld()->SpawnActor<APowerUp>(CurrentPowerUpClass, GetTransform(), SpawnParams);
}

void APickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (bUsesMultiplayer && GetLocalRole() < ROLE_Authority) return;

	if (OtherActor != nullptr)
	{
		if (ReactsOnAllPlayers == false)
		{
			if (OtherActor != UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
			{
				return;
			}
		}

		if (CurrentPowerUpActor)
		{
			// Grant a Powerup to the player if available
			CurrentPowerUpActor->Activated(OtherActor);
			CurrentPowerUpActor = nullptr;

			if (ParticleSystemComponent->Template == nullptr)
			{
				// Set Timer to respawn
				GetWorldTimerManager().SetTimer(TimerHandle_RespawnPickup, this, &APickup::Respawn, CoolDownDuration);
			}
			else
			{
				GetWorldTimerManager().SetTimer(TimerHandle_RespawnPickup, this, &APickup::PlayParticleEffect, CoolDownDuration);
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor is not nullptr in %s.\n This shouldn't happen."), *GetName());
	}
}
