/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "GameMode_Tutorial.h"

#include "fmod_studio.h"
#include "fmod_studio_common.h"
#include "fmod_studio.hpp"

#include "FMODEvent.h"
#include "FMODAudioComponent.h"

#include "Characters/Spider/TutorialSpiderCharacter.h"
#include "Components/Clock/ClockComponent.h"
#include "Actors/TargetPoints/ConnectedTargetPoint.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "GameFramework/GameStateBase.h"
#include "Interfaces/GameInstance/GameInstanceMenuInterface.h"
#include "Interfaces/GameInstance/GameInstanceAccessoryInterface.h"
#include "Interfaces/TargetPoints/TargetPointInterface.h"
#include "Interfaces/SpawnPoints/MonsterSpawnPointInterface.h"
#include "Interfaces/SpawnPoints/SpawnOnFloorInterface.h"
#include "Interfaces/SpawnPoints/SpiderSpawnPointInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Log/GlobalLog.h"

#pragma region Constructor
AGameMode_Tutorial::AGameMode_Tutorial()
{
	TitleOnStart = FText::FromString("Good Start");
	MessagesOfTutorial.Add(FText::FromString("Welcome, new night watchman. I will now teach you your job."));
	CurrentProgressIndex = 0;
	CurrentTimeTextShown = 0.f;
	TimeToShowJustText = 5.f;
	bStateInitialized = false;
	TutorialNoiseMultiplier = .005f;

	TutorialInformation = TArray<FPlayModeTutorialInformation>();
	FPlayModeTutorialInformation Classic = FPlayModeTutorialInformation();
	Classic.PlayMode = EPlayMode::PM_CLASSIC;
	FPlayModeTutorialInformation Default = FPlayModeTutorialInformation();
	Default.PlayMode = EPlayMode::PM_DEFAULT;
	TutorialInformation.Add(Classic);
	TutorialInformation.Add(Default);

	CurrentPlayMode = EPlayMode::PM_NONE;
}
#pragma endregion

#pragma region BeginPlay
void AGameMode_Tutorial::BeginPlay()
{
	bGameModeTutorial = true;

	Super::BeginPlay();

	PrepareSpawnInformation();

	PrepareGameSpawningInformation();

	InitGameSettings();

	RegisterAllActors();

	SpawnMusic();

	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	GameInstanceUI = Cast<IGameInstanceUIInterface>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (GameInstanceUI == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "GameInstance UI was null ! This shouldn't happen !")
	}
	else
	{
		IGameInstanceAccessoryInterface* Accessory = Cast<IGameInstanceAccessoryInterface>(GameInstanceUI);
		CurrentPlayMode = Accessory->GetPlayMode();

		if (CurrentPlayMode == EPlayMode::PM_CLASSIC)
			CurrentPlayModeInformation = &TutorialInformation[0];
		else if (CurrentPlayMode == EPlayMode::PM_CLASSIC)
			CurrentPlayModeInformation = &TutorialInformation[1];

		ShowMessagesOnScreen();
		GameInstanceUI->SetNoiseMultiplier(TutorialNoiseMultiplier);
	}

	GameStateInterface = Cast<IGameStateInterface>(UGameplayStatics::GetGameState(GetWorld()));
}
#pragma endregion

#pragma region Tick
void AGameMode_Tutorial::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerController == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "PlayerController was null ! This shouldn't happen !")
		return;
	}

	if (GameInstanceUI == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "GameInstance UI was null ! This shouldn't happen !")
		return;
	}

	if (GameStateInterface == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "GameState Interface was null ! This shouldn't happen !")
		return;
	}

	switch (CurrentProgressIndex)
	{
	case 0:
		WaitForMovement();
		break;
	case 3:
		SpawnAGarbage();
		break;
	case 5:
		SpawnASpider();
		break;
	case 6:
		SpawnATrap();
		break;
	case 7:
		ShowClockMessage();
		break;
	case 8:
		SpawnAMonster();
		break;
	case 9:
		WaitForRunning();
		break;
	case 10:
		FinishBasicsMessage();
		break;
	case 11:
		LoadLevel1();
		break;
	default:
		break;
	}
}
#pragma endregion

#pragma region Spawn Music
void AGameMode_Tutorial::SpawnMusic()
{
	MusicComponent->Play();
}
#pragma endregion

#pragma region Show Messages On Screen
void AGameMode_Tutorial::ShowMessagesOnScreen()
{
	LOG_DISPLAY(InitializationLog, "Showing Messages on Start")
	if (CurrentPlayModeInformation == nullptr)
	{
		LOG_WARNING(InitializationLog, "Playmode did not match needed setup")
	}
	else 
	{
		GameInstanceUI->ShowUITutorialInformation(TitleOnStart, CurrentPlayModeInformation->MessagesOfTutorial[0], 0);
	}
}
#pragma endregion

#pragma region Spawn Chests
void AGameMode_Tutorial::SpawnChests(TArray<IObjectiveSpawnPointInterface*> ChestPoints, EPartInformation Part)
{
	if (ChestPoints.Num() == 0)
	{
		LOG_DISPLAY(InitializationLog, "No Chest Points found. Can't spawn. Are they set up in the Level ?")
		return;
	}

	int32 NumberOfChests = 1;
		
	TArray<FStringFormatArg> args;
	args.Add(FStringFormatArg(NumberOfChests));
	FString Message = FString::Format(TEXT("Spawning {0} Chests."), args);
	LOG_DISPLAY(InitializationLog, Message)

	ShuffleArray(ChestPoints);
	for (int i = 0; i < NumberOfChests; i++)
	{
		IObjectiveSpawnPointInterface* ChestPoint = ChestPoints[i];
		if (ChestPoint == nullptr)
		{
			LOG_WARNING(InitializationLog, "Error getting SpawnPoint for Chest on Spawning.");
			i--;
			continue;
		}

		FTransform SpawnLocation = ChestPoint->GetCurrentTransform();
		int32 ChestCount = ChestSpawnInformation.Num();
		GetWorld()->SpawnActor<AChestActor>(ChestSpawnInformation[FMath::RandRange(0, ChestCount - 1)].ChestBlueprint, SpawnLocation);
	}
}
#pragma endregion

#pragma region Spawn Traps
void AGameMode_Tutorial::SpawnTraps(TArray<IObjectiveSpawnPointInterface*> TrapPoints, EPartInformation Part)
{
	if (TrapPoints.Num() == 0)
	{
		LOG_DISPLAY(InitializationLog, "No Trap Points found. Can't spawn. Are they set up in the Level ?")
			return;
	}

	int32 NumberOfTraps = 1;

	if (NumberOfTraps == 0)
	{
		LOG_WARNING(InitializationLog, "No traps to spawn")
			return;
	}

	TArray<FStringFormatArg> args;
	args.Add(FStringFormatArg(NumberOfTraps));
	FString Message = FString::Format(TEXT("Spawning {0} Traps."), args);
	LOG_DISPLAY(InitializationLog, Message)

	ShuffleArray(TrapPoints);
	for (int i = 0; i < NumberOfTraps; i++)
	{
		IObjectiveSpawnPointInterface* TrapPoint = TrapPoints[i];
		if (TrapPoint == nullptr)
		{
			LOG_WARNING(InitializationLog, "Error getting SpawnPoint for Trap on Spawning.");
			i--;
			continue;
		}

		int32 TrapCount = TrapSpawnInformation.Num();
		int32 CurrentTrap = FMath::RandRange(0, TrapCount - 1);

		FTransform SpawnLocation = TrapPoint->GetCurrentTransform();

		SpawnLocation.AddToTranslation(TrapSpawnInformation[CurrentTrap].LocalRelocation);
		GetWorld()->SpawnActor<ATrapActor>(TrapSpawnInformation[CurrentTrap].TrapBlueprint, SpawnLocation);
	}
}
#pragma endregion

#pragma region Spawn Spiders
void AGameMode_Tutorial::SpawnSpiders(TArray<IObjectiveSpawnPointInterface*> SpiderPoints, EPartInformation Part)
{
	if (SpiderPoints.Num() == 0)
	{
		LOG_DISPLAY(InitializationLog, "No Trap Points found. Can't spawn. Are they set up in the Level ?")
			return;
	}

	int32 NumberOfSpiders = 1;

	TArray<FStringFormatArg> args;
	args.Add(FStringFormatArg(NumberOfSpiders));
	FString Message = FString::Format(TEXT("Spawning {0} Spiders."), args);
	LOG_DISPLAY(InitializationLog, Message)
				
	for (int i = 0; i < NumberOfSpiders; i++)
	{
		IObjectiveSpawnPointInterface* SpiderSpawnPoint = SpiderPoints[i];
		if (SpiderSpawnPoint == nullptr)
		{
			LOG_WARNING(InitializationLog, "Error getting SpawnPoint for Spider on Spawning.");
			i--;
			continue;
		}

		int32 SpiderCount = SpiderSpawnInformation.Num();
		int32 CurrentSpider = FMath::RandRange(0, SpiderCount - 1);

		FTransform SpawnLocation = SpiderSpawnPoint->GetCurrentTransform();

		SpawnLocation.AddToTranslation(SpiderSpawnInformation[CurrentSpider].LocalRelocation);
		
		ATutorialSpiderCharacter* Spider = GetWorld()->SpawnActor<ATutorialSpiderCharacter>(SpiderSpawnInformation[CurrentSpider].SpiderBlueprint, SpawnLocation);
		if (Spider == nullptr)
		{
			LOG_WARNING(RuntimeExecutionLog, "Could not spawn spider ! This shouldn't happen !")
		}
		else
		{
			ISpiderSpawnPointInterface* SpiderSpawnPointInterface = Cast<ISpiderSpawnPointInterface>(SpiderSpawnPoint);

			if (SpiderSpawnPointInterface == nullptr)
			{
				LOG_WARNING(RuntimeExecutionLog,"Could not cast Spawn Point to Spider Spawn Point Interface. This shouldn't happen !")
			}
			else
			{
				Spider->SetPatrolPoints(SpiderSpawnPointInterface->GetTargetPoints());
			}
			Spider->SpawnDefaultController();
		}
	}
}
#pragma endregion

#pragma region Wait for Movement
void AGameMode_Tutorial::WaitForMovement()
{
	if (PlayerController->IsInputKeyDown(EKeys::W)
		|| PlayerController->IsInputKeyDown(EKeys::A)
		|| PlayerController->IsInputKeyDown(EKeys::S)
		|| PlayerController->IsInputKeyDown(EKeys::D))
	{
		SetNextIndex();
		SpawnAChest();
	}
}
#pragma endregion

#pragma region Spawn A Chest
void AGameMode_Tutorial::SpawnAChest()
{
	GameStateInterface->SetChestsToSolve(1);

	TArray<IObjectiveSpawnPointInterface*> SpawnPoints;
	SpawnPoints.Empty();

	LOG_DISPLAY(InitializationLog, "Getting All SpawnPoints.")
	SpawnPoints = GetSpawnPoints(SpawnPoints, ESpawnPointType::SPT_NONE, EPartInformation::EPI_END);

	SpawnPoints = GetSpawnPoints(SpawnPoints, ESpawnPointType::SPT_NONE, EPartInformation::EPI_LEVEL1);
	LOG_DISPLAY(InitializationLog, "Spawning Chests.")
	SpawnChests(GetSpawnPoints(SpawnPoints, ESpawnPointType::SPT_CHEST, EPartInformation::EPI_LEVEL1), EPartInformation::EPI_LEVEL1);
}
#pragma endregion

#pragma region Spawn A Garbage
void AGameMode_Tutorial::SpawnAGarbage()
{
	if (bStateInitialized == false)
	{
		GameStateInterface->SetGarbageToCollect(1);

		int32 NumberOfGarbage = 1;

		TArray<FStringFormatArg> args;
		args.Add(FStringFormatArg(NumberOfGarbage));
		FString Message = FString::Format(TEXT("Spawning {0} Garbage."), args);
		LOG_DISPLAY(InitializationLog, Message)


		TArray<AActor*> FloorActors = TArray<AActor*>();
		TArray<ISpawnOnFloorInterface*> FloorInterfaces = TArray<ISpawnOnFloorInterface*>();
		UGameplayStatics::GetAllActorsWithInterface(GetWorld(), USpawnOnFloorInterface::StaticClass(), FloorActors);
		if (FloorActors.Num() == 0)
		{
			LOG_WARNING(RuntimeExecutionLog, "Could not find any Floor Actors! This shouldn't happen !")
				return;
		}
		else
		{
			for (auto Actor : FloorActors)
			{
				ISpawnOnFloorInterface* Interface = Cast<ISpawnOnFloorInterface>(Actor);
				if (Interface == nullptr)
				{
					LOG_WARNING(RuntimeExecutionLog, "Could not cast floor actor to interface. This shouldn't happen !")
						continue;
				}
				else
				{
					if(Interface->GetPartOfLevel() == EPartInformation::EPI_LEVEL1)
						FloorInterfaces.Add(Interface);
				}
			}
		}

		ShuffleArray(FloorInterfaces);
		ShuffleArray(FloorInterfaces);
		ShuffleArray(FloorInterfaces);

		
		for (int i = 0; i < NumberOfGarbage; i++)
		{
			FTransform SpawnLocation = FTransform();

			for (auto FloorInterface : FloorInterfaces)
			{
				if (FloorInterface->GetPartOfLevel() == EPartInformation::EPI_LEVEL1)
				{
					FVector RotateVector = FVector(0, 0, FMath::RandRange(-180.f, 180.f));
					SpawnLocation.SetLocation(FloorInterface->GetLocation());
					SpawnLocation.SetRotation(FQuat::MakeFromEuler(RotateVector));
					SpawnLocation.AddToTranslation(FVector(FMath::RandRange(-200.f, 200.f), FMath::RandRange(-200.f, 200.f), 60.f));
					
					break;
				}
			}

			int32 GarbageCount = GarbageSpawnInformation.Num();
			AGarbageActor* GarbageActor = GetWorld()->SpawnActor<AGarbageActor>(GarbageSpawnInformation[FMath::RandRange(0, GarbageCount - 1)].GarbageBlueprint, SpawnLocation);		
		}

		bStateInitialized = true;
	}
}
#pragma endregion

#pragma region Spawn A Spider
void AGameMode_Tutorial::SpawnASpider()
{
	if (bStateInitialized == false)
	{
		TArray<IObjectiveSpawnPointInterface*> SpawnPoints;
		SpawnPoints.Empty();

		LOG_DISPLAY(InitializationLog, "Getting All SpawnPoints.")
		SpawnPoints = GetSpawnPoints(SpawnPoints, ESpawnPointType::SPT_NONE, EPartInformation::EPI_END);

		SpawnPoints = GetSpawnPoints(SpawnPoints, ESpawnPointType::SPT_NONE, EPartInformation::EPI_LEVEL1);
		LOG_DISPLAY(InitializationLog, "Spawning Spiders.")
		SpawnSpiders(GetSpawnPoints(SpawnPoints, ESpawnPointType::SPT_SPIDER, EPartInformation::EPI_LEVEL1), EPartInformation::EPI_LEVEL1);

		bStateInitialized = true;
	}
}
#pragma endregion

#pragma region Spawn a Trap
void AGameMode_Tutorial::SpawnATrap()
{
	if (bStateInitialized == false)
	{
		GameStateInterface->SetTrapsToSolve(1);

		TArray<IObjectiveSpawnPointInterface*> SpawnPoints;
		SpawnPoints.Empty();

		LOG_DISPLAY(InitializationLog, "Getting All SpawnPoints.")
		SpawnPoints = GetSpawnPoints(SpawnPoints, ESpawnPointType::SPT_NONE, EPartInformation::EPI_END);

		SpawnPoints = GetSpawnPoints(SpawnPoints, ESpawnPointType::SPT_NONE, EPartInformation::EPI_LEVEL1);
		LOG_DISPLAY(InitializationLog, "Spawning Traps.")
		SpawnTraps(GetSpawnPoints(SpawnPoints, ESpawnPointType::SPT_TRAP, EPartInformation::EPI_LEVEL1), EPartInformation::EPI_LEVEL1);

		bStateInitialized = true;
	}
}
#pragma endregion

#pragma region Show Clock Message
void AGameMode_Tutorial::ShowClockMessage()
{
	if (bStateInitialized == false)
	{
		ClockComponent->SetCurrentTimeToMidnight();

		bStateInitialized = true;
	}
	else
	{
		if (CurrentTimeTextShown <= TimeToShowJustText)
		{
			CurrentTimeTextShown += GetWorld()->GetDeltaSeconds();
		}
		else
		{
			SetNextIndex();
		}
	}
}
#pragma endregion

#pragma region Spawn A Monster
void AGameMode_Tutorial::SpawnAMonster()
{
	if (bStateInitialized == false)
	{
		TArray<AActor*> Actors;

		UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UMonsterSpawnPointInterface::StaticClass(), Actors);

		for (auto Actor : Actors)
		{
			IMonsterSpawnPointInterface* Interface = Cast<IMonsterSpawnPointInterface>(Actor);
			if (Interface == nullptr)
			{
				LOG_WARNING(RuntimeExecutionLog, "Could not cast Actor to Interface. This shouldn't happen !")
			}
			else
			{
				Interface->ShowMonster();
				
			}
		}

		bStateInitialized = true;
	}
}
#pragma endregion

#pragma region Wait For Running
void AGameMode_Tutorial::WaitForRunning()
{
	if (PlayerController->IsInputKeyDown(EKeys::LeftShift))
	{
		SetNextIndex();
	}
}
#pragma endregion

#pragma region Finish Basics Message
void AGameMode_Tutorial::FinishBasicsMessage()
{
	if (bStateInitialized == false)
	{
		CurrentTimeTextShown = -3.f;

		bStateInitialized = true;
	}
	else
	{
		if (CurrentTimeTextShown <= TimeToShowJustText)
		{
			CurrentTimeTextShown += GetWorld()->GetDeltaSeconds();
		}
		else
		{
			SetNextIndex();
		}
	}
}
#pragma endregion

#pragma region Load Level 1
void AGameMode_Tutorial::LoadLevel1()
{
	IGameInstanceMenuInterface* Menu = Cast<IGameInstanceMenuInterface>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (Menu == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Couldn't find GameInstance ! This shouldn't happen !")
	}
	else
	{
		Menu->TutorialFinished();
		Menu->OpenMenuMap();
	}
}
#pragma endregion

#pragma region Set Next Index
void AGameMode_Tutorial::SetNextIndex()
{
	bStateInitialized = false;
	CurrentProgressIndex++;
	if (CurrentProgressIndex <= MessagesOfTutorial.Num() - 1)
	{
		GameInstanceUI->ShowUITutorialInformation(FText::FromString(""), MessagesOfTutorial[CurrentProgressIndex], CurrentProgressIndex);
	}
}
#pragma endregion

#pragma region Commit False Message
void AGameMode_Tutorial::CommitFalseMessage(FText Message)
{
	GameInstanceUI->ShowUITutorialInformation(FText::FromString(""), Message, CurrentProgressIndex);
}
#pragma endregion

#pragma region Get Current Tutorial Index
int32 AGameMode_Tutorial::GetCurrentTutorialIndex()
{
	return CurrentProgressIndex;
}
#pragma endregion