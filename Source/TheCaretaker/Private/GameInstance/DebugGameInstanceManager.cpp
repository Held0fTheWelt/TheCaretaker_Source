// /* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "DebugGameInstanceManager.h"

#include "Log/GlobalLog.h"
#include "SaveGame/TheCaretakerSaveGame.h"

FTestDifficultySetup::FTestDifficultySetup()
{
	Dungeons = TArray<FTestDungeonSetup>();
	bSolvedComplete = false;
}

FTestLevelSetup::FTestLevelSetup()
{
	Difficulties = TArray<FTestDifficultySetup>();
	bSolvedComplete = false;
}

FTestDungeonSetup::FTestDungeonSetup()
{
	bSolvedPart1 = false;
	bSolvedPart2 = false;
	bSolvedPart3 = false;
}

FTestSetup::FTestSetup()
{
	PlayMode = EPlayMode::PM_NONE;
	Levels = TArray<FTestLevelSetup>();
}

UDebugGameInstanceManager::UDebugGameInstanceManager(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bUseDebugSetup = false;
	bPart2 = false;
	bCompetition = false;
	bExtraLevels = false;
	bSpeedPickups = false;
	bInvisibilityPickups = false;
	bNoisePickups = false;
	bInventoryPickups = false;
	bTimePickups1 = false;
	bTimePickups2 = false;

	TestSetup = TArray<FTestSetup>();

	FTestSetup Classic = FTestSetup();
	Classic.PlayMode = EPlayMode::PM_CLASSIC;
	
	for (int32 i = 0; i < 3; i++)
	{
		FTestLevelSetup Level = FTestLevelSetup();
		for (int32 j = 0; j < 3; j++)
		{
			FTestDifficultySetup Difficulty = FTestDifficultySetup();
			for (int32 k = 0; k < 3; k++)
			{
				FTestDungeonSetup Dungeon = FTestDungeonSetup();
				Difficulty.Dungeons.Add(Dungeon);
			}
			
			Level.Difficulties.Add(Difficulty);
		}
		Classic.Levels.Add(Level);
	}
	
	FTestSetup Default = FTestSetup();
	Default.PlayMode = EPlayMode::PM_DEFAULT;


	for (int32 i = 0; i < 3; i++)
	{
		FTestLevelSetup Level = FTestLevelSetup();
		for (int32 j = 0; j < 9; j++)
		{
			FTestDifficultySetup Difficulty = FTestDifficultySetup();
			for (int32 k = 0; k < 3; k++)
			{
				FTestDungeonSetup Dungeon = FTestDungeonSetup();
				Difficulty.Dungeons.Add(Dungeon);
			}

			Level.Difficulties.Add(Difficulty);
		}
		Default.Levels.Add(Level);
	}

	TestSetup.Add(Classic);
	TestSetup.Add(Default);
}

void UDebugGameInstanceManager::Init()
{
	Super::Init();

	if (bUseDebugSetup)
	{
		if (SaveGame == nullptr)
		{
			LoadSaveGame();
		}		

		// Calculate new Progress
		CalculateNewProgress();

		// Add on Add-Ons
		AddOnAddOns();
	}
}

void UDebugGameInstanceManager::CalculateNewProgress()
{
	SaveGame->ClearAchievedLevels();

}

void UDebugGameInstanceManager::AddOnAddOns()
{
	SaveGame->ClearKnownSecretSlogans();

	if (bPart2)
	{
		LOG_WARNING(InitializationLog, "Is Part 2")
		SaveGame->SetSecretSloganIndex(0);
	}

	if (bCompetition)
	{
		SaveGame->SetSecretSloganIndex(1);
	}

	if (bExtraLevels)
	{
		SaveGame->SetSecretSloganIndex(2);
	}

	if (bSpeedPickups)
	{
		SaveGame->SetSecretSloganIndex(3);
	}

	if (bInvisibilityPickups)
	{
		SaveGame->SetSecretSloganIndex(4);
	}

	if (bNoisePickups)
	{
		SaveGame->SetSecretSloganIndex(5);
	}

	if (bInventoryPickups)
	{
		SaveGame->SetSecretSloganIndex(7);
	}

	if (bTimePickups1)
	{
		SaveGame->SetSecretSloganIndex(6);
	}

	if (bTimePickups2)
	{
		SaveGame->SetSecretSloganIndex(8);
	}
}
