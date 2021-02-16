/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#include "Actors\Pickups\PowerUp\PowerUp.h"

#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PointLightComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "Interfaces/Characters/Character/CharacterInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Log/GlobalLog.h"
#include "Net/UnrealNetwork.h"
#include "TimerManager.h"


APowerUp::APowerUp()
{
	PrimaryActorTick.bCanEverTick = false;

	if (!Root)
		Root = CreateDefaultSubobject<USceneComponent>(FName("RootComponent"));

	RootComponent = Root;

	if (!Mesh)
		Mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("MeshComponent"));
	
	Mesh->SetRelativeLocation(FVector(0.f, 0.f, 30.f));
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	Mesh->SetupAttachment(RootComponent);

	if (!Light)
		Light = CreateDefaultSubobject<UPointLightComponent>(FName("PointLightComponent"));

	Light->AttenuationRadius = 200.f;
	Light->CastShadows = 0;

	Light->SetupAttachment(Mesh);

	if (!RotatingComponent)
		RotatingComponent = CreateDefaultSubobject<URotatingMovementComponent>(FName("RotatingMovementComponent"));

	if (bUsesMultiplayer)
	{
		SetReplicates(true);
	}

	PowerUpInterval = 0;
	TotalNumberOfTicks = 0;
}


void APowerUp::OnRep_PowerUpActive()
{
	OnPowerUpStateChanged(bIsPowerUpActive);
}

void APowerUp::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APowerUp, bIsPowerUpActive);
	DOREPLIFETIME(APowerUp, ActorToInvoke);
}

// Called when the game starts or when spawned
void APowerUp::BeginPlay()
{
	Super::BeginPlay();

	TicksLeft = TotalNumberOfTicks;
}

void APowerUp::Expired()
{
	if (bUsesMultiplayer && ROLE_Authority)
	{
		bIsPowerUpActive = false;
		OnRep_PowerUpActive();
	}

	OnExpired();
	
	GetWorldTimerManager().ClearTimer(TimerHandle_PowerUpTick);

	if (PowerDownSound != nullptr)
	{
		ICharacterInterface* CharacterInterface = Cast<ICharacterInterface>(ActorToInvoke);

		if (CharacterInterface == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("CharacterInterface was nullptr in SpeedUp Activated"));
		}
		else
		{
			UGameplayStatics::SpawnSoundAtLocation(GetWorld(), PowerDownSound, CharacterInterface->GetLocation());
		}
	}
	else
	{
		LOG_DISPLAY(RuntimeExecutionLog,"No PowerDown Sound Set")
	}

	Destroy(true);
}

void APowerUp::Activated(AActor* OtherActor)
{
	if (OtherActor == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Other Actor was nullptr in PowerUp Activated"));
		return;
	}
	if (PowerUpSound != nullptr)
	{
		ICharacterInterface* CharacterInterface = Cast<ICharacterInterface>(OtherActor);

		if (CharacterInterface == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("CharacterInterface was nullptr in SpeedUp Activated"));
		}
		else
		{
			UGameplayStatics::SpawnSoundAtLocation(GetWorld(), PowerUpSound, CharacterInterface->GetLocation());
		}
	}
	else
	{
		LOG_DISPLAY(RuntimeExecutionLog, "No PowerUp Sound Set")
	}

	OnActivated(OtherActor);

	if (bUsesMultiplayer && ROLE_Authority)
	{
		ActorToInvoke = OtherActor;
		bIsPowerUpActive = true;
		OnRep_PowerUpActive();
	}
	if (!bUsesMultiplayer)
	{
		ActorToInvoke = OtherActor;
		bIsPowerUpActive = true;
	}

	Mesh->SetVisibility(false, true);

	if (PowerUpInterval > 0)
		GetWorldTimerManager().SetTimer(TimerHandle_PowerUpTick, this, &APowerUp::OnTickPowerUp, PowerUpInterval, true);
	else
		OnTickPowerUp();
}

void APowerUp::OnTickPowerUp()
{

	if (TicksLeft <= 0)
	{
		Expired();

		// Delete Timer
		GetWorldTimerManager().ClearTimer(TimerHandle_PowerUpTick);
	}
	else
	{
		OnTick();

		if (PowerPulseSound != nullptr)
		{

		}
		else
		{
			LOG_DISPLAY(RuntimeExecutionLog, "No PowerPulse Sound Set")
		}
	}

	TicksLeft--;
}

