/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "Widgets/NoiseBar/NoiseBarUserWidget.h"

#include "FMODAudioComponent.h"

#include "Actors/Monsters/MonsterFeedingVolumeActor.h"
#include "Characters/FirstPerson/FirstPersonCharacter.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Engine/World.h"
#include "Enums/FMOD/FMODParameterType.h"
#include "GameFramework/Actor.h"
#include "GameFramework/GameModeBase.h"
#include "Interfaces/GameInstance/GameInstanceAccessoryInterface.h"
#include "Interfaces/GameMode/Game/GameModeInterface.h"
#include "Interfaces/DungeonMaster/SpawnDungeonMasterInterface.h"
#include "Log/GlobalLog.h"
#include "Kismet/GameplayStatics.h"
#include "Structs/FMOD/FMODParameterSetList.h"

#pragma region NoiseBar Constructor
UNoiseBarUserWidget::UNoiseBarUserWidget()
{
	if (FMODAudio == nullptr)
		FMODAudio = CreateDefaultSubobject<UFMODAudioComponent>("AudioComponent");
	
	CurrentNoiseLevel = 0.f;
	NoiseMultiplier = .1f;
	DefaultRegainMultiplier = .1f;
	NoiseAdditionAtMonsterAngry = .05;
	IsRunning = false;
	HeartBeatPercent = .5;
	FMODParameterName = EName::NAME_None;
	FMODAngryParameterName = EName::NAME_None;
	CharacterClass = AFirstPersonCharacter::StaticClass();
	bMonsterIsAngry = false;
	
	AngryParameterHeartbeat = .5f;
	AngryParameterMonster = 1.f;
	AngryValue = 0.f;
	NoiseModifier = 1.f;

	bNoiseBarBlock = false;

	bDungeonMasterAwake = false;
}
#pragma endregion;

#pragma region Initialize
void UNoiseBarUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	IGameInstanceAccessoryInterface* GameInstance = Cast<IGameInstanceAccessoryInterface>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GameInstance == nullptr)
	{
		LOG_WARNING(InitializationLog, "Could not find GameInstance. This shouldn't happen!")
		return;
	}

	FMODParameterSet ParameterSet = GameInstance->GetFMODParameterSet(EFMODParameterType::FMOD_PT_HEARTBEAT);

	FMODParameterName = ParameterSet.ParameterName;
	SoundChangeValue = ParameterSet.SoundChangeValue;

	ParameterSet = GameInstance->GetFMODParameterSet(EFMODParameterType::FMOD_PT_MONSTER);
	FMODAngryParameterName = ParameterSet.ParameterName;

	AGameModeBase* GameMode = UGameplayStatics::GetGameMode(GetWorld());
	
	if (GameMode == nullptr)
	{
		LOG_WARNING(InitializationLog, "Could not find GameMode. This shouldn't happen!")
		return ;
	}

	IGameModeInterface* DungeonGameMode = Cast<IGameModeInterface>(GameMode);

	if (DungeonGameMode == nullptr)
	{
		LOG_WARNING(InitializationLog, "Could not cast GameMode to TheCaretakerDungeon GameMode. Is the GameMode setup correctly ?")
		return ;
	}

	FMODAudio = DungeonGameMode->GetFMODComponent();

	ProgressBar->SetPercent(0.f);

	AActor* PlayerActor = UGameplayStatics::GetActorOfClass(GetWorld(), *CharacterClass);

	if (PlayerActor == nullptr)
	{
		LOG_WARNING(InitializationLog, "Could not cast PlayerPawn to AFirstPersonCharacter GameMode. Is the GameMode setup correctly and using a FirstPersonCharacter ?")
		return ;
	}

	AFirstPersonCharacter* PlayerCharacter = Cast<AFirstPersonCharacter>(PlayerActor);

	if (PlayerActor == nullptr)
	{
		LOG_WARNING(InitializationLog, "Could not cast PlayerActor to PlayerCharacter. Is the GameMode setup correctly and using a FirstPersonCharacter ?")
		return ;
	}

	Character = PlayerCharacter;
	
	TArray<AActor*> Monsters;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMonsterFeedingVolumeActor::StaticClass(), Monsters);

	for (AActor* Actor : Monsters)
	{
		AMonsterFeedingVolumeActor* Monster = Cast<AMonsterFeedingVolumeActor>(Actor);
		if (Monster == nullptr)
		{
			LOG_WARNING(InitializationLog, "Could not cast Actor to Monster! This shouldn't happen !")
				continue;
		}
		else
		{
			Monster->MonsterAlarm.AddDynamic(this, &UNoiseBarUserWidget::AddMonsterAngryValue);
		}
	}

	bMonsterIsAngry = false;

	LOG_DISPLAY(InitializationLog, "NoiseBar Initialization okay !")

	HeartBeatModifier = 1 - SoundChangeValue;
	HeartBeatModifierRange = 1 - HeartBeatPercent;
}
#pragma endregion

#pragma region Native Tick
void UNoiseBarUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (bPaused)
	{
		return;
	}

	CalculateCurrentNoise(InDeltaTime);

	SetPercentProgress();

	SetBarColor();

	SetupAudioEvents();

	SetBarVisibility();

	CheckDungeonMasterSleep();

	bMonsterIsAngry = false;
}
#pragma endregion

#pragma region CharacterRunning
void UNoiseBarUserWidget::CharacterRunning(bool Pressed)
{
	IsRunning = Pressed;
	SetBarVisibility();
}
#pragma endregion

void UNoiseBarUserWidget::SetNoiseBarMultiplier(float Value)
{
	NoiseMultiplier = Value;
}

#pragma region SetBarVisibility
void UNoiseBarUserWidget::SetBarVisibility()
{
	if (CurrentNoiseLevel == 0)
	{
		Text->SetVisibility(ESlateVisibility::Hidden);
		Background->SetVisibility(ESlateVisibility::Hidden);
		Bar->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		Text->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		Background->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		Bar->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
}
#pragma endregion

#pragma region Calculate Current Noise
void UNoiseBarUserWidget::CalculateCurrentNoise(float InDeltaTime)
{
	if (Character == nullptr)
	{
		LOG_WARNING(RuntimeLog, "Cannot calculate CurrentNoiseLevel, because access to Characters is null. This shouldn't happen !")
		return;
	}

	if (bNoiseBarBlock)
	{
		return;
	}

	if (IsRunning && Character->GetVelocity().Size() > 0.f)
	{
		if (bMonsterIsAngry && AngryValue == 1.f)
		{
			CurrentNoiseLevel += InDeltaTime * (NoiseModifier *(NoiseMultiplier + NoiseAdditionAtMonsterAngry));
			CurrentNoiseLevel = FMath::Clamp(CurrentNoiseLevel, 0.f, 1.f);
		}
		else
		{
			CurrentNoiseLevel += InDeltaTime * NoiseMultiplier * NoiseModifier;
			CurrentNoiseLevel = FMath::Clamp(CurrentNoiseLevel, 0.f, 1.f);
		}
	}
	else
	{
		if (bMonsterIsAngry && AngryValue == 1.f)
		{
			CurrentNoiseLevel += InDeltaTime * NoiseAdditionAtMonsterAngry;
		}
		else
		{
			CurrentNoiseLevel -= InDeltaTime * DefaultRegainMultiplier;
			CurrentNoiseLevel = FMath::Clamp(CurrentNoiseLevel, 0.f, 1.f);
		}
	}
}
#pragma endregion

#pragma region Setup AudioEvents
void UNoiseBarUserWidget::SetupAudioEvents()
{
	if (FMODAudio == nullptr)
	{
		LOG_WARNING(RuntimeLog, "Cannot set AudioEvents, because access to FMODAudio is null. This shouldn't happen !")
		return;
	}

	if (CurrentNoiseLevel > HeartBeatPercent)
	{		
		// calculating range for heartbeat modification
		float ValueToSet = (CurrentNoiseLevel - HeartBeatPercent) / HeartBeatModifierRange;
		// Making it a squared curve
		ValueToSet = ValueToSet * ValueToSet;
		// implementing the modification value to Heartbeat value of 1
		ValueToSet = ValueToSet * HeartBeatModifier;


		if (bMonsterIsAngry)
		{
			FMODAudio->SetParameter(FMODAngryParameterName, AngryParameterMonster);
			FMODAudio->SetParameter(FMODParameterName, (SoundChangeValue + ValueToSet));
		}
		else
		{
			FMODAudio->SetParameter(FMODParameterName, (SoundChangeValue + ValueToSet));
		}
	}
	else
	{
		if(bMonsterIsAngry)
		{
			FMODAudio->SetParameter(FMODAngryParameterName, AngryValue);
		}
		else
		{
			FMODAudio->SetParameter(FMODAngryParameterName, 0.f);
		}
		FMODAudio->SetParameter(FMODParameterName, 0.f);
	}

}
#pragma endregion

#pragma region Set Percent Progress
void UNoiseBarUserWidget::SetPercentProgress()
{
	ProgressBar->SetPercent(CurrentNoiseLevel);
}
#pragma endregion

void UNoiseBarUserWidget::SetBarColor()
{
	// 0 - 0R 1G
	// 0,5 = 1R 1G
	// 1 = 1R 0G

	float temp = CurrentNoiseLevel/2;

	FLinearColor NewColor = FLinearColor::White;
	if (CurrentNoiseLevel < .5f)
	{
		NewColor = FLinearColor(CurrentNoiseLevel * 2, 1, 0, 1);
	}
	else
	{
		NewColor = FLinearColor(1, 1 - (CurrentNoiseLevel - .5f)* 2, 0, 1);
	}

	ProgressBar->SetFillColorAndOpacity(NewColor);
}

void UNoiseBarUserWidget::CheckDungeonMasterSleep()
{
	if (CurrentNoiseLevel == 1.f && bDungeonMasterAwake == false)
	{
		TArray<AActor*> Actors;
		UGameplayStatics::GetAllActorsWithInterface(GetWorld(), USpawnDungeonMasterInterface::StaticClass(), Actors);

		if (Actors.Num() == 0)
			return;

		for (auto Actor : Actors)
		{
			if (Actor == nullptr)
			{
				LOG_WARNING(RuntimeExecutionLog, "Could not find Actor. Is it null ?")
				return;
			}
			ISpawnDungeonMasterInterface* Interface = Cast<ISpawnDungeonMasterInterface>(Actor);
			if (Interface == nullptr)
			{

			}
			else
			{
				Interface->SpawnChasingDungeonMaster();
			}
		}
		bDungeonMasterAwake = true;
	}
}

void UNoiseBarUserWidget::AddMonsterAngryValue(float Value)
{
	bMonsterIsAngry = true;
	AngryValue = Value;
}

void UNoiseBarUserWidget::SetGamePaused(bool SetGamePaused)
{
	bPaused = SetGamePaused;
}

bool UNoiseBarUserWidget::IsPaused() const
{
	return bPaused;
}

void UNoiseBarUserWidget::NoisePickupBlockingNoise(bool IsBlockingNoise)
{
	bNoiseBarBlock = IsBlockingNoise;

	if(bNoiseBarBlock)
	{
		CurrentNoiseLevel = 0.f;
	}
}

void UNoiseBarUserWidget::NoisyPickup(float Modifier)
{
	NoiseModifier = Modifier;
}
