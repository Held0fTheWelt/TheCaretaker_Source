/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "GameMode_Game.h"

#include "TimerManager.h"

#include "fmod_studio.h"
#include "fmod_studio_common.h"
#include "fmod_studio.hpp"

#include "FMODEvent.h"
#include "FMODAudioComponent.h"

#include "Components/Clock/ClockComponent.h"
#include "Curves/CurveFloat.h"
#include "Enums/FMOD/FMODParameterType.h"
#include "GameFramework/GameState.h"
#include "Interfaces/GameInstance/GameInstanceAccessoryInterface.h"
#include "Interfaces/GameInstance/GameInstanceMenuInterface.h"
#include "Interfaces/GameInstance/GameInstanceUIInterface.h"
#include "Interfaces/GameInstance/GameInstanceInterface.h"
#include "Interfaces/GameState/GameStateInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Log/GlobalLog.h"
#include "Structs/FMOD/FMODParameterSetList.h"

AGameMode_Game::AGameMode_Game()
{
	PrimaryActorTick.bCanEverTick = true;

	if (ClockComponent == nullptr)
		ClockComponent = CreateDefaultSubobject<UClockComponent>(FName("ClockComponent"));

	RootComponent = ClockComponent;
	
	ClockMaxTime = 590.0f;

	if (MusicComponent == nullptr)
		MusicComponent = CreateDefaultSubobject<UFMODAudioComponent>(FName("MusicComponent"));

	MusicComponent->SetupAttachment(RootComponent);

	FMODParameterType = EFMODParameterType::FMOD_PT_TIME;
	FMODParameterName = EName::NAME_None;
	FMODSoundChangeValue = .5f;	

	bGameModeTutorial = false;
	 
	SpawnSettings = FLocalSpawnInformation();

	DelayClockStart = 4.f;

	if (ScoreAdditionAudioComponent == nullptr)
		ScoreAdditionAudioComponent = CreateDefaultSubobject<UAudioComponent>(FName("ScoreAudioComponent"));
	ScoreAdditionAudioComponent->SetupAttachment(RootComponent);
	ScoreAdditionAudioComponent->bAutoActivate = false;
}

void AGameMode_Game::InitGameSettings()
{
	if (SetupUI() == false) return;

	UWorld* World = GetWorld();

	if (World == nullptr)
	{
		LOG_WARNING(InitializationLog, "GameMode could not find world! Cannot run Game! This shouldn't happen !");
		return;
	}

	RegisterMonstersToFeed(World);

	SetupUIInformation();

	BroadcastNewGameStart(World);

	UpdateClock();
}

void AGameMode_Game::UpdateClock()
{
	if (GameInstanceAccessory == nullptr)
	{
		LOG_WARNING(InitializationLog, "Could not find GameInstance Accessory ! This shouldn't happen !")
	}
	else
	{
		if (GameInstanceAccessory->GetPlayMode() != EPlayMode::PM_HOPHOP)
		{
			EPartInformation CurrentPart = GameInstanceAccessory->GetCurrentProgress().CurrentPart;

			FTimeSet EndTime = FTimeSet();

			switch (CurrentPart)
			{
			case EPI_NONE:
				break;
			case EPI_LEVEL1:
				ClockMaxTime = 180;
				EndTime.Hour = 4;
				ClockComponent->SetEndTime(6, EndTime);
				break;
			case EPI_LEVEL2:
				ClockMaxTime = 240;
				EndTime.Hour = 6;
				ClockComponent->SetEndTime(8, EndTime);
				break;
			case EPI_LEVEL3:
				ClockMaxTime = 300;
				EndTime.Hour = 8;
				ClockComponent->SetEndTime(10, EndTime);
				break;
			case EPI_END:
				break;
			case EPI_SPECIAL:
				break;
			case EPI_MASTER:
				break;
			default:
				break;
			}

			ClockComponent->UpdateClockSettings();

			GetWorld()->GetTimerManager().SetTimer(TimerHandle_ClockDelay, this, &AGameMode_Game::StartClock, DelayClockStart);
		}
	}
}

#pragma region BeginPlay
void AGameMode_Game::BeginPlay()
{
	Super::BeginPlay();

	if (GetInstanceInterfaces() == false) return;

	if (GetFMODParameters() == false) return;
	// GameInstance->GetGameInformation()	
	if (GetGameStateInterface() == false) return;	
	
	if (bGameModeTutorial)
		return;

	if (LoadLevel() == false) return;

	/*if (SetupUI() == false) return;

	UWorld* const World = GetWorld();

	if (World == nullptr)
	{
		LOG_WARNING(InitializationLog, "GameMode could not find world! Cannot run Game! This shouldn't happen !");
		return;
	}

	RegisterMonstersToFeed(World);

	SetupUIInformation();

	BroadcastNewGameStart(World);

	ClockComponent->NewGame()*/
}

void AGameMode_Game::SetTitle(TAssetPtr<class UFMODEvent> Title)
{
	MusicComponent->SetEvent(Title.Get());
	MusicComponent->Play();
}

#pragma endregion

bool AGameMode_Game::GetInstanceInterfaces()
{
	bool Okay = true;

	UGameInstance* Instance = GetGameInstance();

	GameInstance = Cast<IGameInstanceInterface>(Instance);
	GameInstanceUI = Cast<IGameInstanceUIInterface>(Instance);
	GameInstanceAccessory = Cast<IGameInstanceAccessoryInterface>(Instance);
	if (GameInstance == nullptr || GameInstanceUI == nullptr || GameInstanceAccessory == nullptr)
	{
		LOG_WARNING(InitializationLog, "Could not find GameInstance interfaces! Are they set in the Project settings ?");
		Okay = false;
	}
	else
	{
		LOG_DISPLAY(InitializationLog, "Print Current Progress Values")
		GameInstance->UpdateGameStateValues();
	}

	return Okay;
}


bool AGameMode_Game::GetFMODParameters()
{
	FMODParameterSet ParameterSet = GameInstanceAccessory->GetFMODParameterSet(FMODParameterType);

	if (ParameterSet.ParameterType == EFMODParameterType::FMOD_PT_NONE)
	{
		LOG_WARNING(InitializationLog, "Could not find FMOD Parameter in GameInstance List")
		return false;
	}

	FMODParameterName = ParameterSet.ParameterName;
	FMODSoundChangeValue = ParameterSet.SoundChangeValue;

	return true;
}

bool AGameMode_Game::GetGameStateInterface()
{
	if (GameStateInterface == nullptr)
	{
		LOG_DISPLAY(InitializationLog, "Looking for GameState.")

			AGameStateBase* State = UGameplayStatics::GetGameState(GetWorld());

		if (State == nullptr)
		{
			LOG_DISPLAY(InitializationLog, "Could not get GameState.")
			return false;
		}

		GameStateInterface = Cast<IGameStateInterface>(State);
	}
	return true;
}

bool AGameMode_Game::LoadLevel()
{
	if (GameStateInterface != nullptr)
	{
		LOG_DISPLAY(InitializationLog, "Setting up Doors.")
		SetupLevelDoors();

		if (PrepareGameSpawningInformation() == false)
		{
			return false;
		}

		if (TestGameStateSetup() == false)
		{
			LOG_DISPLAY(InitializationLog, "GameState Settings for Level wrong. Cannot Spawn correctly!.")
			return false;
		}
		

		LOG_DISPLAY(InitializationLog, "Loading Sublevels.")
		LoadSublevels();
		
		return true;
	}
	else
	{
		LOG_WARNING(InitializationLog, "CaretakerGameState not found.")
		return false;
	}
}

void AGameMode_Game::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bPaused)
	{
		return;
	}

	if (MusicComponent == nullptr)
	{
		LOG_WARNING(RuntimeLog, "MusicComponent was null in GameMode! This shouldn't happen !")
	}
	float CalculatedValue = 0;
	
	if (MusicDynamics == nullptr)
	{
		// LOG_WARNING(RuntimeExecutionLog, "MusicDynamics was nullptr. Use CurveFloat in Bluepring")
		CalculatedValue = ClockComponent->CurrentTimeValue() / ClockMaxTime;
	}
	else
	{
		CalculatedValue = MusicDynamics->GetFloatValue(ClockComponent->CurrentTimeValue() / ClockMaxTime);
	}


	//UE_LOG(LogTemp, Warning, TEXT("%f"), CalculatedValue);

	CalculatedValue = FMath::Clamp(CalculatedValue, 0.f, 1.f);

	if (CalculatedValue <= FMODSoundChangeValue)
	{
		MusicComponent->SetParameter(FMODParameterName, 0.f);
	}
	else
	{
		MusicComponent->SetParameter(FMODParameterName, CalculatedValue);
	}
}

UFMODAudioComponent* AGameMode_Game::GetFMODComponent()
{
	return MusicComponent;
}

void AGameMode_Game::SetClockActive(bool SetActive)
{
	ClockComponent->SetGamePaused(!SetActive);
}

void AGameMode_Game::ClockRunningBackwards(bool RunningBackwards)
{
	ClockComponent->TimeRunningBackwards(RunningBackwards);
}

void AGameMode_Game::PlayScoreSound(bool Play)
{
	if (Play)
	{
		ScoreAdditionAudioComponent->Play();
	}
	else
	{
		ScoreAdditionAudioComponent->Stop();
	}
}

void AGameMode_Game::AddScoreSound(USoundBase* SoundForAddingScore)
{
	if (SoundForAddingScore == nullptr)
	{
		LOG_WARNING(InitializationLog, "Cannot play adding score sound. Is it set in the widget blueprint ?")
	}
	else
	{
		ScoreAdditionAudioComponent->Sound = SoundForAddingScore;
	}
}

void AGameMode_Game::StartClock()
{
	ClockComponent->NewGame();
}

FTimeSet AGameMode_Game::GetCurrentTime()
{
	return ClockComponent->GetCurrentTime();
}

TArray<FGarbageSpawnInformation> AGameMode_Game::GetGarbageSpawnInformation() const
{
	return GarbageSpawnInformation;
}
