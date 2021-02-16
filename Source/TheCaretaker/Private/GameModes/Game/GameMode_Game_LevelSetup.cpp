/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#include "GameMode_Game.h"

#include "fmod_studio.h"
#include "fmod_studio_common.h"
#include "fmod_studio.hpp"

#include "FMODEvent.h"
#include "FMODAudioComponent.h"

#include "Components/Clock/ClockComponent.h"
#include "Engine/World.h"
#include "Interfaces/Clock/ClockInterface.h"
#include "Interfaces/Door/DoorInterface.h"
#include "Interfaces/Fireplace/FireplaceInterface.h"
#include "Interfaces/GameState/GameStateInterface.h"
#include "Interfaces/SpawnPoints/SpiderSpawnPointInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Log/GlobalLog.h"
#include "States/Game/CaretakerGameState.h"
#include "Structs/Game/GameInformation.h"

void AGameMode_Game::DropGarbage()
{
	LOG_DISPLAY(InitializationLog, "Getting All SpawnPoints.")
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
				if (Interface->GetPartOfLevel() == EPartInformation::EPI_LEVEL1)
					FloorInterfaces.Add(Interface);
			}
		}
	}

	ShuffleArray(FloorInterfaces);

	FTransform SpawnLocation = FTransform();

	auto FloorInterface = FloorInterfaces[0];
	
	FVector RotateVector = FVector(0, 0, FMath::RandRange(-180.f, 180.f));
	SpawnLocation.SetLocation(FloorInterface->GetLocation());
	SpawnLocation.SetRotation(FQuat::MakeFromEuler(RotateVector));
	SpawnLocation.AddToTranslation(FVector(FMath::RandRange(-200.f, 200.f), FMath::RandRange(-200.f, 200.f), 60.f));
	
	int32 GarbageCount = GarbageSpawnInformation.Num();
	AGarbageActor* GarbageActor = GetWorld()->SpawnActor<AGarbageActor>(GarbageSpawnInformation[FMath::RandRange(0, GarbageCount - 1)].GarbageBlueprint, SpawnLocation);

	if (GameStateInterface == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Cannot increment TrapCount, because GameStateInterface was null ! This shouldn't happen !")
	}
	else
	{
		GameStateInterface->IncrementGarbageToCollect();
	}
}

void AGameMode_Game::DropGold()
{
	TArray<IObjectiveSpawnPointInterface*> SpawnPoints;
	SpawnPoints.Empty();
	
	LOG_DISPLAY(InitializationLog, "Getting All SpawnPoints.")
	SpawnPoints = GetSpawnPoints(SpawnPoints, ESpawnPointType::SPT_NONE, EPartInformation::EPI_END);

	SpawnPoints = GetSpawnPoints(SpawnPoints, ESpawnPointType::SPT_CHEST, EPartInformation::EPI_END);

	if (SpawnPoints.Num() == 0)
	{
		LOG_WARNING(RuntimeExecutionLog, "No Spawn Points found. Dropping Garbage instead")
		DropGarbage();
		return;
	}

	ShuffleArray(SpawnPoints);

	int32 SpawnPointIndex = 0;
	while (SpawnPoints[SpawnPointIndex]->GetIsSpawned() == true)
	{
		SpawnPointIndex++;

		if (SpawnPointIndex >= SpawnPoints.Num())
		{
			LOG_WARNING(RuntimeExecutionLog, "No more Chestpoints in Level")
			return;
		}
	}

	FTransform SpawnLocation = SpawnPoints[SpawnPointIndex]->GetCurrentTransform();
	int32 ChestCount = ChestSpawnInformation.Num();
	GetWorld()->SpawnActor<AChestActor>(ChestSpawnInformation[FMath::RandRange(0, ChestCount - 1)].ChestBlueprint, SpawnLocation);

	if (GameStateInterface == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Cannot increment ChestCount, because GameStateInterface was null ! This shouldn't happen !")
	}
	else
	{
		GameStateInterface->IncrementChestsToSolve();
	}
}


void AGameMode_Game::DropTrap()
{
	TArray<IObjectiveSpawnPointInterface*> SpawnPoints;
	SpawnPoints.Empty();

	LOG_DISPLAY(InitializationLog, "Getting All SpawnPoints.")
	SpawnPoints = GetSpawnPoints(SpawnPoints, ESpawnPointType::SPT_TRAP, EPartInformation::EPI_END);
	
	if (SpawnPoints.Num() == 0)
	{
		LOG_WARNING(RuntimeExecutionLog, "No Spawn Points found. Dropping Garbage instead")
			DropGarbage();
		return;
	}

	ShuffleArray(SpawnPoints);

	int32 SpawnPointIndex = 0;
	
	while (SpawnPoints[SpawnPointIndex]->GetIsSpawned() == true)
	{
		SpawnPointIndex++;

		if (SpawnPointIndex >= SpawnPoints.Num())
		{
			LOG_WARNING(RuntimeExecutionLog, "No more Trappoints in Level")
			return;
		}
	}

	FTransform SpawnLocation = SpawnPoints[SpawnPointIndex]->GetCurrentTransform();
	int32 TrapCount = TrapSpawnInformation.Num();
	GetWorld()->SpawnActor<ATrapActor>(TrapSpawnInformation[FMath::RandRange(0, TrapCount - 1)].TrapBlueprint, SpawnLocation);

	if (GameStateInterface == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Cannot increment TrapCount, because GameStateInterface was null ! This shouldn't happen !")
	}
	else
	{
		GameStateInterface->IncrementTrapsToSolve();
	}
}

void AGameMode_Game::SetupLevelDoors()
{
	LOG_DISPLAY(InitializationLog, "Looking for all Doors in Scene")

	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UDoorInterface::StaticClass(), Actors);

	for (auto Actor : Actors)
	{
		IDoorInterface* Door = Cast<IDoorInterface>(Actor);
		if (Door->GetDoorLevel() <= GameStateInterface->GetCurrentPart())
		{
			LOG_DISPLAY(InitializationLog, "Door is part of current Level and ready to use")
			Door->SetDoorEnabled(true);
		}
		else
		{
			LOG_DISPLAY(InitializationLog, "Door is not part of current Level and locked")
			Door->SetDoorEnabled(false);
		}
	}
}

void AGameMode_Game::LoadSublevels()
{
	//UE_LOG(LogTemp, Warning, TEXT("CurrentPart = %s"), GameStateInterface->GetCurrentPart());

	if (GameStateInterface->GetCurrentPart() <= EPartInformation::EPI_LEVEL1)
	{
		LOG_DISPLAY(InitializationLog, "Level 1: Nothing to load. Continuing LevelSpawn")
			CallbackOnLevelLoaded();
	}

	if (GameStateInterface->GetCurrentPart() >= EPartInformation::EPI_LEVEL2)
	{
		LOG_DISPLAY(InitializationLog, "Loading Sublevel 2. Waiting for Callback OnLevelLoaded")
			FLatentActionInfo LatentInfo;
		if (GameStateInterface->GetCurrentPart() == EPartInformation::EPI_LEVEL2)
		{
			LatentInfo.CallbackTarget = this;
			LatentInfo.Linkage = 0;
			LatentInfo.ExecutionFunction = "CallbackOnLevelLoaded";
		}
		UGameplayStatics::LoadStreamLevel(this, LevelInformation[GameStateInterface->GetCurrentLevel()].GetDungeonsInLevel()[GameStateInterface->GetCurrentDungeon()].DungeonParts[1].MapNameOfPart
			, true, true, LatentInfo);


	}

	if (GameStateInterface->GetCurrentPart() >= EPartInformation::EPI_LEVEL3)
	{
		LOG_DISPLAY(InitializationLog, "Loading Sublevel 3. Waiting for Callback OnLevelLoaded")
			FLatentActionInfo LatentInfo;
		LatentInfo.CallbackTarget = this;
		LatentInfo.ExecutionFunction = "CallbackOnLevelLoaded";
		LatentInfo.Linkage = 0;
		LatentInfo.UUID = 2;
		UGameplayStatics::LoadStreamLevel(this, LevelInformation[GameStateInterface->GetCurrentLevel()].GetDungeonsInLevel()[GameStateInterface->GetCurrentDungeon()].DungeonParts[2].MapNameOfPart
			, true, true, LatentInfo);
	}
}

void AGameMode_Game::Spawn()
{
	LOG_DISPLAY(InitializationLog, "Spawning")
	

	
	LOG_DISPLAY(InitializationLog, "Game Information found.")

	if (SpawnInformation == nullptr)
	{
		LOG_WARNING(InitializationLog, "Could not Spawn Level. Spawn Information was null.")
		return;
	}
	LOG_DISPLAY(InitializationLog, "Spawn Information found.")
			   
	if (PrepareSpawnInformation() == false)
	{
		return;
	}

	TArray<IObjectiveSpawnPointInterface*> SpawnPoints;
	TArray<ISpawnOnFloorInterface*> GarbageSpawnPoints;
	SpawnPoints.Empty();
	GarbageSpawnPoints.Empty();

	LOG_DISPLAY(InitializationLog, "Getting All SpawnPoints.")
	SpawnPoints = GetSpawnPoints(SpawnPoints, ESpawnPointType::SPT_NONE, EPartInformation::EPI_END);
	GarbageSpawnPoints = GetSpawnPoints(GarbageSpawnPoints, ESpawnPointType::SPT_NONE, EPartInformation::EPI_END);

	//if (SpawnPoints.Num() == 0)
	//{
	//	LOG_WARNING(InitializationLog, "No Spawn Points found. Can't spawn. Are they set up in the Level ?")
	//	return;
	//}

	//SpawnPoints.Empty();

	if (GameStateInterface->GetCurrentPart() >= EPartInformation::EPI_LEVEL1)
	{
		SpawnPoints = GetSpawnPoints(SpawnPoints, ESpawnPointType::SPT_NONE, EPartInformation::EPI_LEVEL1);
		LOG_DISPLAY(InitializationLog, "Spawning Garbage Part 1.")
		SpawnGarbage(GetSpawnPoints(GarbageSpawnPoints, ESpawnPointType::SPT_GARBAGE, EPartInformation::EPI_LEVEL1), EPartInformation::EPI_LEVEL1);
		LOG_DISPLAY(InitializationLog, "Spawning Chests Part 1.")
		SpawnChests(GetSpawnPoints(SpawnPoints, ESpawnPointType::SPT_CHEST, EPartInformation::EPI_LEVEL1), EPartInformation::EPI_LEVEL1);
		LOG_DISPLAY(InitializationLog, "Spawning Traps Part 1.")
		SpawnTraps(GetSpawnPoints(SpawnPoints, ESpawnPointType::SPT_TRAP, EPartInformation::EPI_LEVEL1), EPartInformation::EPI_LEVEL1);
		LOG_DISPLAY(InitializationLog, "Spawning Spiders Part 1.")
		SpawnSpiders(GetSpawnPoints(SpawnPoints, ESpawnPointType::SPT_SPIDER, EPartInformation::EPI_LEVEL1), EPartInformation::EPI_LEVEL1);
			
	}

	SpawnPoints.Empty();

	if (GameStateInterface->GetCurrentPart() >= EPartInformation::EPI_LEVEL2)
	{
		SpawnPoints = GetSpawnPoints(SpawnPoints, ESpawnPointType::SPT_NONE, EPartInformation::EPI_LEVEL2);
		LOG_DISPLAY(InitializationLog, "Spawning Garbage Part 2.")
		SpawnGarbage(GetSpawnPoints(GarbageSpawnPoints, ESpawnPointType::SPT_GARBAGE, EPartInformation::EPI_LEVEL2), EPartInformation::EPI_LEVEL2);
		LOG_DISPLAY(InitializationLog, "Spawning Chests Part 2.")
		SpawnChests(GetSpawnPoints(SpawnPoints, ESpawnPointType::SPT_CHEST, EPartInformation::EPI_LEVEL2), EPartInformation::EPI_LEVEL2);
		LOG_DISPLAY(InitializationLog, "Spawning Traps Part 2.")
		SpawnTraps(GetSpawnPoints(SpawnPoints, ESpawnPointType::SPT_TRAP, EPartInformation::EPI_LEVEL2), EPartInformation::EPI_LEVEL2);
		LOG_DISPLAY(InitializationLog, "Spawning Spiders Part 2.")
		SpawnSpiders(GetSpawnPoints(SpawnPoints, ESpawnPointType::SPT_SPIDER, EPartInformation::EPI_LEVEL2), EPartInformation::EPI_LEVEL2);
	}

	SpawnPoints.Empty();

	if (GameStateInterface->GetCurrentPart() >= EPartInformation::EPI_LEVEL3)
	{
		SpawnPoints = GetSpawnPoints(SpawnPoints, ESpawnPointType::SPT_NONE, EPartInformation::EPI_LEVEL3);
		LOG_DISPLAY(InitializationLog, "Spawning Garbage Part 3.")
		SpawnGarbage(GetSpawnPoints(GarbageSpawnPoints, ESpawnPointType::SPT_GARBAGE, EPartInformation::EPI_LEVEL3), EPartInformation::EPI_LEVEL3);
		LOG_DISPLAY(InitializationLog, "Spawning Chests Part 3.")
		SpawnChests(GetSpawnPoints(SpawnPoints, ESpawnPointType::SPT_CHEST, EPartInformation::EPI_LEVEL3), EPartInformation::EPI_LEVEL3);
		LOG_DISPLAY(InitializationLog, "Spawning Traps Part 3.")
		SpawnTraps(GetSpawnPoints(SpawnPoints, ESpawnPointType::SPT_TRAP, EPartInformation::EPI_LEVEL3), EPartInformation::EPI_LEVEL3);
		LOG_DISPLAY(InitializationLog, "Spawning Spiders Part 3.")
		SpawnSpiders(GetSpawnPoints(SpawnPoints, ESpawnPointType::SPT_SPIDER, EPartInformation::EPI_LEVEL3), EPartInformation::EPI_LEVEL3);
	}
}

void AGameMode_Game::CallbackOnLevelLoaded()
{
	GameStateInterface->SetShouldWaitForEndOfTime(GameInstanceAccessory->ShouldWaitForEndOfTime());

	LOG_DISPLAY(InitializationLog, "Spawning Actors.");
	Spawn();

	InitGameSettings();

	RegisterAllActors();

	SpawnMusic();

	CheckScoreSetup();

	ShowMessagesOnScreen();
}

IClockInterface* AGameMode_Game::GetClock()
{
	return ClockComponent;
}

bool AGameMode_Game::PrepareSpawnInformation()
{
	LOG_DISPLAY(InitializationLog, "Getting Spawn Information Table from Data Table.")
		static const FString ContextString(TEXT("Spawn Information Table"));
	FSpawnInformationTable* SpawnInformationTable = SpawnInformation->FindRow<FSpawnInformationTable>(FName(TEXT("SpawnInformation")), ContextString, true);
	if (SpawnInformationTable == nullptr)
	{
		LOG_WARNING(InitializationLog, "Could not Spawn Level. Could not Cast SpawnInformation from Spawn Information Table.")
			return false;
	}

	LOG_DISPLAY(InitializationLog, "Getting Information from Spawn Information Table.")
	GarbageSpawnInformation = SpawnInformationTable->GetGarbageInformation();
	ChestSpawnInformation = SpawnInformationTable->GetChestInformation();
	TrapSpawnInformation = SpawnInformationTable->GetTrapInformation();
	SpiderSpawnInformation = SpawnInformationTable->GetSpiderInformation();

	TArray<FStringFormatArg> args;
	args.Add(FStringFormatArg(GarbageSpawnInformation.Num()));
	args.Add(FStringFormatArg(ChestSpawnInformation.Num()));
	args.Add(FStringFormatArg(TrapSpawnInformation.Num()));


	FString Message = FString::Format(TEXT("{0} Garbage to Spawn."), args);
	LOG_DISPLAY(InitializationLog, Message)
	Message = FString::Format(TEXT("{1} Chests to Spawn."), args);
	LOG_DISPLAY(InitializationLog, Message)
	Message = FString::Format(TEXT("{2} Traps to Spawn."), args);
	LOG_DISPLAY(InitializationLog, Message)

	return true;
}

bool AGameMode_Game::PrepareGameSpawningInformation()
{

	LOG_DISPLAY(InitializationLog, "Getting Game Information from Data Table.")
	LevelInformation = GameInstance->GetGameInformation();
	return true;
}

void AGameMode_Game::SpawnMusic()
{
	LOG_DISPLAY(InitializationLog, "Spawning Music.")
	FDungeonInformation Dungeon = FDungeonInformation();
	if (bGameModeTutorial)
	{
		Dungeon = LevelInformation[0].GetDungeonsInLevel()[0];
	}
	else
	{
		Dungeon = LevelInformation[GameStateInterface->GetCurrentLevel()].GetDungeonsInLevel()[GameStateInterface->GetCurrentDungeon()];
	}
	

	MusicComponent->Event = Dungeon.FModEvent;
	MusicComponent->Play();
	MusicComponent->SetParameter(FMODParameterName, 1.0f);
}

bool AGameMode_Game::TestGameStateSetup()
{
	if (LevelInformation.Num() == 0)
	{
		LOG_DISPLAY(InitializationLog, "No Levels Found.")
			return false;
	}

	if (GameStateInterface->GetCurrentLevel() >= LevelInformation.Num())
	{
		LOG_DISPLAY(InitializationLog, "No Levels Found.")
			TArray<FStringFormatArg> args;
		args.Add(FStringFormatArg(GameStateInterface->GetCurrentLevel()));
		FString Message = FString::Format(TEXT("Level Set in GameState not present in Level Setup: {0}."), args);
		LOG_WARNING(InitializationLog, Message)
			return false;
	}

	FLevelInformation CurrentLevel = LevelInformation[GameStateInterface->GetCurrentLevel()];

	if (CurrentLevel.DungeonsInLevel.Num() == 0)
	{
		LOG_DISPLAY(InitializationLog, "No Levels Found.")
			TArray<FStringFormatArg> args;
		args.Add(FStringFormatArg(GameStateInterface->GetCurrentLevel()));
		FString Message = FString::Format(TEXT("No Dungeons found in Level {0}."), args);
		LOG_WARNING(InitializationLog, Message)
			return false;
	}

	if (GameStateInterface->GetCurrentDungeon() >= CurrentLevel.DungeonsInLevel.Num())
	{
		LOG_DISPLAY(InitializationLog, "No Levels Found.")
			TArray<FStringFormatArg> args;
		args.Add(FStringFormatArg(GameStateInterface->GetCurrentDungeon()));
		FString Message = FString::Format(TEXT("Dungeon Set in GameState not present in Level Setup: {0}."), args);
		LOG_WARNING(InitializationLog, Message)
			return false;
	}

	FDungeonInformation CurrentDungeon = CurrentLevel.DungeonsInLevel[GameStateInterface->GetCurrentDungeon()];

	// Fix - does not look nice - but hopefully does its job
	if (GameStateInterface->GetCurrentPart() <= EPartInformation::EPI_NONE)
	{
		GameStateInterface->SetCurrentPart(EPartInformation::EPI_LEVEL1);
	}

	if (GameStateInterface->GetCurrentPart() == EPartInformation::EPI_LEVEL1)
	{
		CurrentDungeonPartInformation = CurrentDungeon.DungeonParts[0];
	}
	else if (GameStateInterface->GetCurrentPart() == EPartInformation::EPI_LEVEL2)
	{
		CurrentDungeonPartInformation = CurrentDungeon.DungeonParts[1];
	}
	else if (GameStateInterface->GetCurrentPart() == EPartInformation::EPI_LEVEL3)
	{
		CurrentDungeonPartInformation = CurrentDungeon.DungeonParts[2];
	}
	else
	{
		LOG_WARNING(InitializationLog, "Returning false - mostly only kitchen setup.")

		return false;
	}
	LOG_DISPLAY(InitializationLog, "Returning true - success setting up current part settings.")
	return true;
}

void AGameMode_Game::CheckScoreSetup()
{
	if (GameInstanceAccessory == nullptr)
	{
		LOG_WARNING(InitializationLog,"GameInstanceAccessory was null ! Cannot Check Score Setup")
	}
	else
	{
		ACaretakerGameState* State = GetGameState<ACaretakerGameState>();
		if (GameInstanceAccessory->IsCompeteAccessible())
		{		
			if (State == nullptr)
			{
				LOG_WARNING(InitializationLog,"Could not cast GameState! Is it set in the GameMode ?")
			}
			else
			{
				State->SetupScore();				
			}
		}
		else
		{
			if (State == nullptr)
			{
				LOG_WARNING(InitializationLog, "Could not cast GameState! Is it set in the GameMode ?")
			}
			else
			{
				State->NotCompeting();
			}
		}
	}
}

void AGameMode_Game::RegisterAllActors()
{
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UFireplaceInterface::StaticClass(), Actors);
	LOG_DISPLAY(InitializationLog, "Looking for Fireplaces in Scene")

	for (auto Actor : Actors)
	{
		IFireplaceInterface* Fireplace = Cast<IFireplaceInterface>(Actor);
		if (Fireplace != nullptr)
		{
			Fireplace->AddFireplaceListener();
			LOG_DISPLAY(InitializationLog, "Fireplace is listening for BurnEvents")
		}
		else
		{
			LOG_WARNING(InitializationLog, "Could not register Garbage at Fireplace to countdown, because interface was null! This shouldn't happen !");
		}
	}
}

TArray<ISpawnOnFloorInterface*> AGameMode_Game::GetSpawnPoints(TArray<ISpawnOnFloorInterface*> InputPoints, TEnumAsByte<ESpawnPointType> SpawnPointType, EPartInformation Part) const
{	
		if (SpawnPointType == EPartInformation::EPI_NONE)
		{
			LOG_DISPLAY(InitializationLog, "Receiving all Spawn Points.");
			TArray<AActor*> Actors;
			UGameplayStatics::GetAllActorsWithInterface(GetWorld(), USpawnOnFloorInterface::StaticClass(), Actors);
			InputPoints.Empty();
			for (auto Actor : Actors)
			{
				if (!Actor->IsValidLowLevel())
				{
					continue;
				}

				ISpawnOnFloorInterface* SpawnPoint = Cast<ISpawnOnFloorInterface>(Actor);

				if (SpawnPoint == nullptr)
				{
					LOG_WARNING(InitializationLog, "Current Actor had no SpawnPointInterface, even if it should have.");
					continue;
				}
				else
				{
					InputPoints.Add(SpawnPoint);
				}
			}
			TArray<FStringFormatArg> args;
			args.Add(FStringFormatArg(InputPoints.Num()));
			FString Message = FString::Format(TEXT("{0} SpawnPoints found."), args);
			LOG_DISPLAY(InitializationLog, Message)

				return InputPoints;
		}
		else
		{
			LOG_DISPLAY(InitializationLog, "Sorting Spawn Points for Spawning.");
			TArray<ISpawnOnFloorInterface*> ValidSpawnPoints;

			for (auto SpawnPoint : InputPoints)
			{
				if (SpawnPoint == NULL)
				{

					UE_LOG(LogTemp, Warning, TEXT("Spawn Point was Null. Continuing..."));
					continue;
				}
				if (SpawnPoint->GetPartOfLevel() == Part)
				{
					ValidSpawnPoints.Add(SpawnPoint);
				}				
			}
			TArray<FStringFormatArg> args;
			args.Add(FStringFormatArg(ValidSpawnPoints.Num()));
			FString Message = FString::Format(TEXT("{0} Valid SpawnPoints found."), args);
			LOG_DISPLAY(InitializationLog, Message)

			return ValidSpawnPoints;
		}
}

TArray<IObjectiveSpawnPointInterface*> AGameMode_Game::GetSpawnPoints(TArray<IObjectiveSpawnPointInterface*> InputPoints, TEnumAsByte<ESpawnPointType> SpawnPointType, EPartInformation Part) const
{
	if (SpawnPointType == EPartInformation::EPI_NONE)
	{
		LOG_DISPLAY(InitializationLog, "Receiving all Spawn Points.");
		TArray<AActor*> Actors;
		UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UObjectiveSpawnPointInterface::StaticClass(), Actors);
		InputPoints.Empty();
		for (auto Actor : Actors)
		{
			if (!Actor->IsValidLowLevel())
			{
				continue;
			}

			IObjectiveSpawnPointInterface* SpawnPoint = Cast<IObjectiveSpawnPointInterface>(Actor);

			if (SpawnPoint == nullptr)
			{
				LOG_WARNING(InitializationLog, "Current Actor had no SpawnPointInterface, even if it should have.");
				continue;
			}
			else
			{
				InputPoints.Add(SpawnPoint);
			}
		}
		TArray<FStringFormatArg> args;
		args.Add(FStringFormatArg(InputPoints.Num()));
		FString Message = FString::Format(TEXT("{0} SpawnPoints found."), args);
		LOG_DISPLAY(InitializationLog, Message)
			
		return InputPoints;
	}
	else
	{
		LOG_DISPLAY(InitializationLog, "Sorting Spawn Points for Spawning.");
		TArray<IObjectiveSpawnPointInterface*> ValidSpawnPoints;

		for (auto SpawnPoint : InputPoints)
		{
			if (SpawnPoint == NULL)
			{

				UE_LOG(LogTemp, Warning, TEXT("Spawn Point was Null. Continuing..."));
				continue;
			}
			if (SpawnPoint->GetSpawnPointType() == SpawnPointType)
			{
				if (SpawnPoint->GetCurrentPart() == Part || Part == EPartInformation::EPI_END)
				{
					ValidSpawnPoints.Add(SpawnPoint);
				}
			}
		}
		TArray<FStringFormatArg> args;
		args.Add(FStringFormatArg(ValidSpawnPoints.Num()));
		FString Message = FString::Format(TEXT("{0} Valid SpawnPoints found."), args);
		LOG_DISPLAY(InitializationLog, Message)
			
		return ValidSpawnPoints;
	}
}

void AGameMode_Game::ShuffleArray(TArray<IObjectiveSpawnPointInterface*>& SpawnPointArray)
{
	LOG_DISPLAY(InitializationLog, "Shuffeling Spawn Points for Spawning.");
	if (SpawnPointArray.Num() > 0)
	{
		int32 LastIndex = SpawnPointArray.Num() - 1;
		for (int32 i = 0; i <= LastIndex; ++i)
		{
			int32 Index = FMath::RandRange(i, LastIndex);
			if (i != Index)
			{
				SpawnPointArray.Swap(i, Index);
			}
		}
	}
}

void AGameMode_Game::ShuffleArray(TArray<ISpawnOnFloorInterface*>& SpawnPointArray)
{
	LOG_DISPLAY(InitializationLog, "Shuffeling Spawn Points for Spawning.");
	if (SpawnPointArray.Num() > 0)
	{
		int32 LastIndex = SpawnPointArray.Num() - 1;
		for (int32 i = 0; i <= LastIndex; ++i)
		{
			int32 Index = FMath::RandRange(i, LastIndex);
			if (i != Index)
			{
				SpawnPointArray.Swap(i, Index);
			}
		}
	}
}

void AGameMode_Game::SpawnGarbage(TArray<ISpawnOnFloorInterface*> SpawnPointArray, EPartInformation Part)
{
	if (SpawnPointArray.Num() == 0)
	{
		LOG_DISPLAY(InitializationLog, "No Garbage Spawn Points found. Can't spawn. Are they set up in the Level ?")
		return;
	}

	int32 NumberOfGarbage = GameInstanceAccessory->GetNumberToSpawn(ESpawnPointType::SPT_GARBAGE, Part);

	if (NumberOfGarbage == 0)
	{
		LOG_DISPLAY(InitializationLog, "No garbage to spawn")
		return;
	}

	TArray<FStringFormatArg> args;
	args.Add(FStringFormatArg(NumberOfGarbage));
	FString Message = FString::Format(TEXT("Spawning {0} Garbage."), args);
	LOG_DISPLAY(InitializationLog, Message)

	ShuffleArray(SpawnPointArray);
	for (int i = 0; i < NumberOfGarbage; i++)
	{
		ISpawnOnFloorInterface* GarbagePoint = SpawnPointArray[i];
		if (GarbagePoint == nullptr)
		{
			LOG_WARNING(InitializationLog, "Error getting SpawnPoint for Garbage on Spawning.");
			i--;
			continue;
		}

		FTransform SpawnLocation = FTransform();
		FVector RotateVector = FVector(0, 0, FMath::RandRange(-180.f, 180.f));
		SpawnLocation.SetLocation(GarbagePoint->GetLocation());
		SpawnLocation.SetRotation(FQuat::MakeFromEuler(RotateVector));
		SpawnLocation.AddToTranslation(FVector(FMath::RandRange(-SpawnSettings.RangeSpawnOnX, SpawnSettings.RangeSpawnOnX), FMath::RandRange(-SpawnSettings.RangeSpawnOnY, SpawnSettings.RangeSpawnOnY), 60.f));

		int32 GarbageCount = GarbageSpawnInformation.Num();
		AGarbageActor* GarbageActor = GetWorld()->SpawnActor<AGarbageActor>(GarbageSpawnInformation[FMath::RandRange(0, GarbageCount - 1)].GarbageBlueprint, SpawnLocation);
		if (GarbageActor == nullptr)
		{
			LOG_WARNING(InitializationLog, "GarbageActor was null ! This shouldn't happen !")
		}
		else
		{
			GarbageActor->Part = Part;
		}
	}
}

void AGameMode_Game::SpawnChests(TArray<IObjectiveSpawnPointInterface*> ChestPoints, EPartInformation Part)
{
	if (ChestPoints.Num() == 0)
	{
		LOG_DISPLAY(InitializationLog, "No Chest Points found. Can't spawn. Are they set up in the Level ?")
		return;
	}

	int32 NumberOfChests = GameInstanceAccessory->GetNumberToSpawn(ESpawnPointType::SPT_CHEST, EPartInformation::EPI_LEVEL1);

	if (NumberOfChests == 0)
	{
		LOG_DISPLAY(InitializationLog, "No chests  to spawn")
			return;
	}

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
		
		//if (ChestPoint->GetCurrentPart() != Part)
		//{
		//	i--;
		//	continue;
		//}

		FTransform SpawnLocation = ChestPoint->GetCurrentTransform();
		int32 ChestCount = ChestSpawnInformation.Num();
		AChestActor* ChestActor = GetWorld()->SpawnActor<AChestActor>(ChestSpawnInformation[FMath::RandRange(0, ChestCount - 1)].ChestBlueprint, SpawnLocation);

		if (ChestActor == nullptr)
		{
			LOG_WARNING(InitializationLog, "GarbageActor was null ! This shouldn't happen !")
		}
		else
		{
			ChestActor->Part = Part;
		}
		ChestPoint->SetSpawned(true);
	}

}

void AGameMode_Game::SpawnTraps(TArray<IObjectiveSpawnPointInterface*> TrapPoints, EPartInformation Part)
{
	if (TrapPoints.Num() == 0)
	{
		LOG_DISPLAY(InitializationLog, "No Trap Points found. Can't spawn. Are they set up in the Level ?")
			return;
	}

	int32 NumberOfTraps = GameInstanceAccessory->GetNumberToSpawn(ESpawnPointType::SPT_TRAP, Part);

	if (NumberOfTraps == 0)
	{
		LOG_DISPLAY(InitializationLog, "No traps to spawn")
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

		GameStateInterface->AddTrapObjective(Part);

		int32 TrapCount = TrapSpawnInformation.Num();
		int32 CurrentTrap = FMath::RandRange(0, TrapCount - 1);

		FTransform SpawnLocation = TrapPoint->GetCurrentTransform();

		SpawnLocation.AddToTranslation(TrapSpawnInformation[CurrentTrap].LocalRelocation);
		ATrapActor* TrapActor = GetWorld()->SpawnActor<ATrapActor>(TrapSpawnInformation[CurrentTrap].TrapBlueprint, SpawnLocation);

		if (TrapActor == nullptr)
		{
			LOG_WARNING(InitializationLog, "GarbageActor was null ! This shouldn't happen !")
		}
		else
		{
			TrapActor->Part = Part;
		}

		TrapPoint->SetSpawned(true);
	}
}

void AGameMode_Game::SpawnSpiders(TArray<IObjectiveSpawnPointInterface*> SpiderPoints, EPartInformation Part)
{
	if (SpiderPoints.Num() == 0)
	{
		LOG_DISPLAY(InitializationLog, "No Spider Points found. Can't spawn spiders. Are they set up in the Level ?")
			return;
	}

	LOG_DISPLAY(RuntimeExecutionLog, "Look for the numbers of spiders to spawn. Not done yet.")
	int32 NumberOfSpiders = GameInstanceAccessory->GetNumberToSpawn(ESpawnPointType::SPT_SPIDER, Part);
	LOG_DISPLAY(RuntimeExecutionLog, "Look for the numbers of paths to spawn spiders. Not done yet.")
	int32 NumberOfPaths = GameInstanceAccessory->GetNumberToSpawn(ESpawnPointType::SPT_SPIDERPATH, Part);
	LOG_DISPLAY(RuntimeExecutionLog, "Look for the values of spiders to spread on pathes. Not done yet.")
	TArray<float> PathSpreadValues = GameInstanceAccessory->GetSpiderPathSpreadValues(Part);

	if (NumberOfSpiders == 0)
	{
		LOG_WARNING(InitializationLog, "No spiders to spawn")
			return;
	}

	TArray<FStringFormatArg> args;
	args.Add(FStringFormatArg(NumberOfSpiders));
	FString Message = FString::Format(TEXT("Spawning {0} Spiders."), args);
	LOG_DISPLAY(InitializationLog, Message)
			
	LOG_DISPLAY(InitializationLog, "Creating Arrays to split Spawn Points per Path.")
	TArray<TArray<IObjectiveSpawnPointInterface*>> SpawnPointsPerPath = TArray<TArray<IObjectiveSpawnPointInterface*>>();

	for (int32 i = 0; i < NumberOfPaths; i++)
	{
		SpawnPointsPerPath.Add(TArray<IObjectiveSpawnPointInterface*>());
	}

	LOG_DISPLAY(InitializationLog, "Adding SpawnPoints to PathIndexed Arrays")
	for (int32 i = 0; i < SpiderPoints.Num(); i++)
	{
		ISpiderSpawnPointInterface* SpiderSpawnPoint = Cast<ISpiderSpawnPointInterface>(SpiderPoints[i]);

		if (SpiderSpawnPoint == nullptr)
		{
			LOG_WARNING(InitializationLog, "Could not cast SpawnPoint to SpiderSpawnPoint. This shouldn't happen.")
			continue;
		}

		if (SpiderSpawnPoint->GetPathIndex() >= NumberOfPaths || SpiderSpawnPoint->GetPathIndex() < 0)
		{
			args = TArray<FStringFormatArg>();
			args.Add(FStringFormatArg(SpiderSpawnPoint->GetName()));
			args.Add(FStringFormatArg(NumberOfPaths));
			Message = FString::Format(TEXT("SpawnPoint {0} has invalid PathIndex. Index has to be within 0 and {1}."), args);
			LOG_WARNING(InitializationLog, Message)
			continue;
		}

		SpawnPointsPerPath[SpiderSpawnPoint->GetPathIndex()].Add(SpiderPoints[i]);
	}

	for (int32 i = 0; i < NumberOfPaths; i++)
	{
		ShuffleArray(SpawnPointsPerPath[i]);
	}

	TArray<int32> NumbersOfSpidersPerPath = TArray<int32>();
	for (int32 i = 0; i < NumberOfPaths; i++)
	{
		NumbersOfSpidersPerPath.Add(NumberOfPaths * PathSpreadValues[i]);
	}

	for (int32 i = 0; i < NumberOfPaths; i++)
	{
		for (int32 j = 0; j < NumbersOfSpidersPerPath.Num(); j++)
		{

		}
	}

	for (int i = 0; i < NumberOfSpiders; i++)
	{
		IObjectiveSpawnPointInterface* SpiderSpawnPoint = SpiderPoints[i];
		if (SpiderSpawnPoint == nullptr)
		{
			LOG_WARNING(InitializationLog, "Error getting SpawnPoint for Spiders on Spawning.");
			i--;
			continue;
		}

		int32 SpiderCount = SpiderSpawnInformation.Num();
		int32 CurrentSpider = FMath::RandRange(0, SpiderCount - 1);

		FTransform SpawnLocation = SpiderSpawnPoint->GetCurrentTransform();

		SpawnLocation.AddToTranslation(SpiderSpawnInformation[CurrentSpider].LocalRelocation);
		ASpiderCharacter* NewSpider = GetWorld()->SpawnActor<ASpiderCharacter>(SpiderSpawnInformation[CurrentSpider].SpiderBlueprint, SpawnLocation);

		if (NewSpider == nullptr)
		{
			LOG_WARNING(InitializationLog, "Something went wrong during spawning spider. This shouldn't happen !")
		}
		else
		{
			ISpiderSpawnPointInterface* SpawnPointInterface = Cast<ISpiderSpawnPointInterface>(SpiderSpawnPoint);
			if (SpawnPointInterface == nullptr)
			{
				LOG_WARNING(InitializationLog, "Could not cast SpiderSpawnPointInterface. This shouldn't happen !")
			}
			else
			{
				NewSpider->SetPatrolPoints(SpawnPointInterface->GetTargetPoints());
				LOG_DISPLAY(InitializationLog, "Added Target Patrol Points")
			}
			NewSpider->SpawnDefaultController();
		}
	}
}
