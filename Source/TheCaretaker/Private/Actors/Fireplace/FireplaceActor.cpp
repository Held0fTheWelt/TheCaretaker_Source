/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#include "Actors/Fireplace/FireplaceActor.h"

#include "TimerManager.h"


#include "Components/SceneComponent.h"
#include "Engine/World.h"
#include "Interfaces/Achievements/AchievementCountInterface.h"
#include "Interfaces/WinCondition/WinConditionVolumeInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Log/GlobalLog.h"
#include "Particles/ParticleSystemComponent.h"
#include "States/Game/CaretakerGameState.h"

AFireplaceActor::AFireplaceActor()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	if (BurnSoundSpawnLocation == nullptr)
		BurnSoundSpawnLocation = CreateDefaultSubobject<USceneComponent>(FName("FireSoundSpawnLocation"));

	BurnSoundSpawnLocation->SetupAttachment(RootComponent);

	if (ParticleSystemComponent == nullptr)
		ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(FName("ParticleSystemComponent"));
	
	ParticleSystemComponent->SetupAttachment(RootComponent);
	ParticleSystemComponent->SetRelativeLocation(FVector(-50.f, 0.f, -40.f));
	ParticleSystemComponent->SetRelativeScale3D(FVector(.3f, .3f, .3f));
	
}

#pragma region Begin Play
void AFireplaceActor::BeginPlay()
{
	Super::BeginPlay();
}
#pragma endregion
void AFireplaceActor::DeActivateParticleSystem()
{
	if(ParticleSystemComponent->IsActive())
		ParticleSystemComponent->Deactivate();
}

#pragma region Add Fireplace Listener
void AFireplaceActor::AddFireplaceListener()
{
	TArray<AActor*>GameStateActors;
	// Pick only Actors with Interface, instead of iterating whole World:
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACaretakerGameState::StaticClass(), GameStateActors);
	for (const auto& Actor : GameStateActors) {

		ACaretakerGameState* GameStateActor = Cast<ACaretakerGameState>(Actor);
		if (GameStateActor != nullptr)
		{
			FirePlaceAction.AddDynamic(GameStateActor, &ACaretakerGameState::CountDownGarbage);
		}
	}
}
#pragma endregion

#pragma region Add ResourceEvent Implementation
void AFireplaceActor::AddResourceEvent_Implementation()
{
	if (BurnSound != nullptr)
	{
		UGameplayStatics::SpawnSoundAttached(BurnSound, BurnSoundSpawnLocation);		
		LOG_DISPLAY(RuntimeExecutionLog, "Playing Burn Sound")
	}
	else
	{
		LOG_DISPLAY(RuntimeExecutionLog, "Could not play Burn Sound, because BurnSound was null. Is it missing in the Fireplace Actor ?")
	}

	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	if (GameInstance == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Could not get GameInstance. This shouldn't happen!")
		return;
	}

	IAchievementCountInterface* AchievementInstance = Cast<IAchievementCountInterface>(GameInstance);
	if (AchievementInstance == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Could not cast GameInstance to AchievementCountInterface. This shouldn't happen!")
		return;
	}

	LOG_DISPLAY(RuntimeExecutionLog, "Counting Achievement")
	AchievementInstance->CountAchievement(EAchievementType::AT_GARBAGE);

	ParticleSystemComponent->Activate();

	GetWorldTimerManager().SetTimer(TimerHandle_FireParticle_Deactivate, this, &AFireplaceActor::DeActivateParticleSystem, .025f, false);
}
#pragma endregion

#pragma region Left MouseButton Clicked
void AFireplaceActor::LeftMouseButtonClicked(ICollectableInterface*& CollectableRef)
{
	if (FirePlaceAction.IsBound())
	{
		LOG_DISPLAY(RuntimeExecutionLog, "Broadcasting Fireplace Action")
		FirePlaceAction.Broadcast(this);
	}
}
#pragma endregion