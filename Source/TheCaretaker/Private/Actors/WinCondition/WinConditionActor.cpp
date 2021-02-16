/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "WinConditionActor.h"

#include "Components/BoxComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Log/GlobalLog.h"

#pragma region Constructor
AWinConditionActor::AWinConditionActor()
{

	if (!TriggerVolume)
		TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerVolumeComponent"));

	// This is a query only trigger volume
	TriggerVolume->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	// This is a static object in scene
	TriggerVolume->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	// This trigger volume does ignore all channels by default
	TriggerVolume->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	// This volume responses to overlap events with pawns
	TriggerVolume->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	TriggerVolume->SetBoxExtent(FVector(750.f, 750.f, 250.f));

	RootComponent = TriggerVolume;

	bShouldWaitUntilEndOfTime = true;
}
#pragma endregion

#pragma region Should Wait For End Of Time
bool AWinConditionActor::ShouldWaitForEndOfTime() const
{
	return bShouldWaitUntilEndOfTime;
}
#pragma endregion


#pragma region BeginPlay
void AWinConditionActor::BeginPlay()
{
	Super::BeginPlay();
	
	if (TriggerVolume != nullptr)
	{
		TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &AWinConditionActor::OnOverlapBegin);
		TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &AWinConditionActor::OnOverlapEnd);
	}
	else
	{
		LOG_WARNING(InitializationLog, "TriggerVolume was null ! This shouldn't happen!")
	}
}
#pragma endregion

#pragma region On Overlap Begin
void AWinConditionActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{	
	// if is PlayerPawn
	if (OtherActor == UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
	{
		bIsInSafeZone = true;

		if (!bShouldWaitUntilEndOfTime)
		{
			WinConditionUpdate.ExecuteIfBound();
		}
	}
}
#pragma endregion

#pragma region On Overlap End
void AWinConditionActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// if is PlayerPawn
	if (OtherActor == UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
	{
		bIsInSafeZone = false;
	}
}
#pragma endregion

#pragma region Is In SafeZone
bool AWinConditionActor::IsInSafeZone() const
{
	return bIsInSafeZone;
}
#pragma endregion

#pragma region Call Win Condition Update
void AWinConditionActor::CallWinConditionUpdate()
{
	if (!bShouldWaitUntilEndOfTime)
	{
		WinConditionUpdate.ExecuteIfBound();
	}
}
#pragma endregion