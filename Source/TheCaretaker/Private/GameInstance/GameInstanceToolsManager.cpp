/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#include "GameInstance/GameInstanceManager.h"

#include "TimerManager.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Engine/World.h"
#include "Characters/FirstPerson/FirstPersonCharacter.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/GameState.h"
#include "GameModes/Game/GameMode_Game.h"
#include "GameModes/Menu/GameMode_Menu.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Interfaces/GameState/GameStateInterface.h"
#include "Interfaces/Widgets/Achievement/AchievementWidgetInterface.h"
#include "Interfaces/Widgets/LevelSelector/LevelSelectorWidgetInterface.h"
#include "Interfaces/SpiderWeb/SpiderWebInterface.h"
#include "HAL/IConsoleManager.h"
#include "Kismet/GameplayStatics.h"
#include "Log/GlobalLog.h"
#include "SaveGame/TheCaretakerSaveGame.h"
#include "Structs/Achievement/AchievementDefinition.h"
#include "Structs/Secret/SecretSlogan.h"
#include "Widgets/Achievements/AchievementInputBoxUserWidget.h"
#include "Widgets/Main/MainUI.h"
#include "Widgets/Start/StartMenuWidget.h"
#include "Widgets/Menu/MainMenuWidget.h"
#include "Widgets/Information/DebugInformationWidget.h"
#include "Widgets/Inventory/DebugInventoryWidget.h"

void UGameInstanceManager::CheckHighScores()
{
	if (SaveGame == nullptr)
	{
		LOG_WARNING(InitializationLog, "SaveGame was null ! This shouldn't happen !")
	}
	else
	{
		if (SaveGame->HighScoreContainsElements() == false)
		{
			ReadInHighScores();
		}
	}
}

void UGameInstanceManager::ReadInHighScores()
{
	if (HighScoreDefinitionTable == nullptr)
	{
		LOG_WARNING(InitializationLog, "HighscoreDefinitionTable not set in GameInstance Manager !")
	}
	else
	{
		static const FString ContextString(TEXT("CompleteHighScore"));
		LOG_DISPLAY(InitializationLog, "Getting HighScore Information from Data Table.")

		TArray<FHighScoreComplete> NewHighScores = TArray<FHighScoreComplete>();

		TArray<FName> RowNames = HighScoreDefinitionTable->GetRowNames();
		for (int32 i = 0; i < RowNames.Num(); i++)
		{
			FHighScoreComplete* Score = HighScoreDefinitionTable->FindRow<FHighScoreComplete>(RowNames[i], ContextString, true);

			NewHighScores.Add(*Score);
		}
		
		SaveGame->AddDefaultHighScore(NewHighScores);
	}
}

void UGameInstanceManager::TestExtraLevelsSetup()
{	
	//if (bAlreadyAddedExtraLevels == true)
	//{
	//	LOG_DISPLAY(InitializationLog, "Already added extra levels.")
	//	return;
	//}

	bool ExtraLevelsAchieved = false;

	if (SaveGame == nullptr)
	{
		LOG_WARNING(InitializationLog, "SaveGame was null. This shouldn't happen.")
		return;
	}
	else
	{
		TArray<FString> KnowSecretCredentials = SaveGame->GetKnowSecretCredentials();
		

		for (auto KnownCredential : KnowSecretCredentials)
		{
			if (KnownCredential == ExtraLevelsDecryptKey)
			{
				ExtraLevelsAchieved = true;
			}
		}
	}

	if (ExtraLevelsAchieved == false)
	{
		return;
	}

	if (ExtraLevelsGameInformation == nullptr)
	{
		LOG_WARNING(InitializationLog, "Extra Level Game Information is not set in GameInstanceManager.")
		return;
	}

	if (PlayModeInformationTableExtraLevels == nullptr)
	{
		LOG_WARNING(InitializationLog, "Extra Level PlayMode Information is not set in GameInstanceManager.")
		return;
	}


	LOG_DISPLAY(InitializationLog, "Adding Extra Levels Game Information")
	AddExtraLevelGameInformation();

	LOG_DISPLAY(InitializationLog, "Adding Extra Levels PlayMode Information ")
	AddExtraLevelPlayModeInformation();

	LOG_DISPLAY(InitializationLog, "Adding Extra Levels Achievement Information ")
	AddExtraLevelAchievementInformation();

	bAlreadyAddedExtraLevels = true;
}


void UGameInstanceManager::AddExtraLevelAchievementInformation()
{
	if (SaveGame == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "SaveGame was null ! This shouldn't happen !")
		return;
	}

	SaveGame->UpdatePlayModeInformationForLevels(PlayModeInformation);

	SaveGameData();
}



#pragma region Count Achievement
void UGameInstanceManager::CountAchievement(EAchievementType AchievementType)
{
	for (int32 i = 0; i < SaveGame->GetAchievements().Num(); i++)
	{
		if (SaveGame->GetAchievements()[i].AchievementType == AchievementType)
		{
			SaveGame->GetAchievements()[i].CurrentCount++;
			FString AchievementTypeString = "";
			switch (AchievementType)
			{
			case AT_NONE:
				AchievementTypeString = "None";
				break;
			case AT_GARBAGE:
				AchievementTypeString = "Garbage";
				break;
			case AT_GOLD:
				AchievementTypeString = "Gold";
				break;
			case AT_MEAT:
				AchievementTypeString = "Meat";
				break;
			case AT_TRAP:
				AchievementTypeString = "Trap";
				break;
			case AT_VICTORY:
				AchievementTypeString = "Victory";
				break;
			case AT_DEATHBYSPIDER:
				AchievementTypeString = "Death by Spider";
				break;
			case AT_DEATHBYMONSTER:
				AchievementTypeString = "Death by Monster";
				break;
			case AT_DEATHBYTRAP:
				AchievementTypeString = "Death by Trap";
				break;
			case AT_DEATHBYTIME:
				AchievementTypeString = "Death by Time";
				break;
			case AT_PROGRESS:
				AchievementTypeString = "Level Progress";
				break;
			case AT_DEATHBYPICKUP:
				AchievementTypeString = "Death by Pickup";
				break;
			case AT_WINCONDITIONMET:
				AchievementTypeString = "Win Condition Met";
				break;
			default:
				break;
			}
			UE_LOG(LogTemp, Display, TEXT("Current Count for '%s': %d"),  *AchievementTypeString, SaveGame->GetAchievements()[i].CurrentCount);
			TestAchievements(AchievementType, SaveGame->GetAchievements()[i].CurrentCount);
			break;
		}
	}

	if (AchievementType == EAchievementType::AT_MEAT)
	{
		IGameStateInterface* GameStateInterface = GetWorld()->GetGameState<IGameStateInterface>();

		if (GameStateInterface == nullptr)
		{
			LOG_WARNING(RuntimeExecutionLog, "Could not count achievement score, because it was null")
		}
		else
		{
			GameStateInterface->AchievementSolved(AchievementType);
		}
	}
}
#pragma endregion

#pragma region Test Achievements
void UGameInstanceManager::TestAchievements(EAchievementType AchievementType, int32 CurrentCount)
{
	TArray<FAchievementDefinition> AchievementsToTest = GetAchievements();

	if (AchievementsToTest.Num() == 0)
	{
		LOG_WARNING(RuntimeExecutionLog, "AchievementDefinition was null. Cannot lookup Achievement Definition Table. Is it set up in the SaveGame ?")
			return;
	}

	for (int32 i = 0; i < AchievementsToTest.Num(); i++)
	{
		if (AchievementsToTest[i].TypeOfAchievement == AchievementType)
		{
			if (AchievementType == EAchievementType::AT_SECRETUNLOCKED)
			{
				if (CurrentCount == AchievementsToTest[i].CountToAchieve)
				{
					if (SaveGame->GetAchievedRewards()[i].bAchieved == false)
					{
						SaveGame->GetAchievedRewards()[i].TimeAchieved = FDateTime::Now();
						SaveGame->GetAchievedRewards()[i].bAchieved = true;
						LOG_WARNING(RuntimeLog, AchievementsToTest[i].Description.ToString())

						if (MainUI == nullptr)
						{
							if (MenuUI == nullptr)
							{
								LOG_WARNING(RuntimeExecutionLog, "No UI found ! This shouldn't happen !")
							}
							else
							{
								MenuUI->PlayAchievementAnimation();
							}
						}
						else
						{
							MainUI->StartAnimation(4);
						}

						TArray<UUserWidget*> Widgets;

						UWidgetBlueprintLibrary::GetAllWidgetsWithInterface(GetWorld(), Widgets, UAchievementWidgetInterface::StaticClass(), false);

						for (auto Widget : Widgets)
						{
							IAchievementWidgetInterface* Interface = Cast<IAchievementWidgetInterface>(Widget);
							Interface->SetAchievementInformation(
								AchievementsToTest[i].ImageToShow,
								AchievementsToTest[i].CountToAchieve > 1 ? AchievementsToTest[i].CountToAchieve : 0,
								AchievementsToTest[i].Name,
								AchievementsToTest[i].Description,
								FText::FromString(SaveGame->GetAchievedRewards()[i].TimeAchieved.ToString())
							);
						}

						return;
					}
				}
			}
			else
			{
				if (CurrentCount >= AchievementsToTest[i].CountToAchieve)
				{
					if (SaveGame->GetAchievedRewards()[i].bAchieved == false)
					{
						SaveGame->GetAchievedRewards()[i].TimeAchieved = FDateTime::Now();
						SaveGame->GetAchievedRewards()[i].bAchieved = true;
						LOG_WARNING(RuntimeLog, AchievementsToTest[i].Description.ToString())

							MainUI->StartAnimation(4);

						TArray<UUserWidget*> Widgets;

						UWidgetBlueprintLibrary::GetAllWidgetsWithInterface(GetWorld(), Widgets, UAchievementWidgetInterface::StaticClass(), false);

						for (auto Widget : Widgets)
						{
							IAchievementWidgetInterface* Interface = Cast<IAchievementWidgetInterface>(Widget);
							Interface->SetAchievementInformation(
								AchievementsToTest[i].ImageToShow,
								AchievementsToTest[i].CountToAchieve > 1 ? AchievementsToTest[i].CountToAchieve : 0,
								AchievementsToTest[i].Name,
								AchievementsToTest[i].Description,
								FText::FromString(SaveGame->GetAchievedRewards()[i].TimeAchieved.ToString())
							);
						}

						return;
					}
				}
			}
		}
	}
}
#pragma endregion

#pragma region Progress

#pragma region Full Progress
void UGameInstanceManager::FullProgress()
{
	CurrentProgress.CurrentLevel = LevelInformation.Num() - 1;
	CurrentProgress.CurrentDungeon = LevelInformation[CurrentProgress.CurrentLevel].DungeonsInLevel.Num() - 1;
	CurrentProgress.CurrentLevelName = LevelInformation[CurrentProgress.CurrentLevel].DungeonsInLevel[CurrentProgress.CurrentDungeon].MapNameOfPart;
	CurrentProgress.CurrentPart = EPartInformation::EPI_LEVEL3;
	SaveGame->FullProgress();
	CurrentProgress.CurrentDifficulty = SaveGame->CalculateCurrentDifficultyForPart(PlayMode, CurrentProgress.CurrentLevel, CurrentProgress.CurrentDungeon, CurrentProgress.CurrentPart - 1);
	
	CurrentProgress.CurrentLevelPoints = SaveGame->CalculateLevelPoints();

	SaveGameData();

	AcceptPlayMode();
	CurrentProgress.SetCurrentLevelName(MapDefinition.LevelName_Menu);

	if (SaveGame->bIsPart2)
	{
		for (int32 i = 0; i < PlayModeInformation.Num(); i++)
		{			
			for (int32 j = 0; j < PlayModeInformation[i].Levels.Num(); j++)
			{
				for (int32 k = 0; k < PlayModeInformation[i].Levels[j].DungeonsInLevel.Num(); k++)
				{

					for (int32 l = 0; l < PlayModeInformation[i].Levels[j].DungeonsInLevel[k].Difficulties.Num(); l++)
					{
						for (int32 m = 0; m < PlayModeInformation[i].Levels[j].DungeonsInLevel[k].Difficulties[l].DungeonParts.Num(); m++)
						{
							TArray<FSecretCredential> Credentials = PlayModeInformation[i].Levels[j].DungeonsInLevel[k].Difficulties[l].DungeonParts[m].PartsWithDifficulty[0].SecretCredentials;
				
						}
					}
				}

			}
		}
	}
	else
	{

	}
	GetTimerManager().SetTimer(TimerHandle_ReloadMenu, this, &UGameInstanceManager::LoadLevelFinished, .1f, false, TimeToWaitForReloadMenu);
}
#pragma endregion

#pragma region Reset Progress
void UGameInstanceManager::ResetProgress()
{
	CurrentProgress.CurrentLevel = 0;
	CurrentProgress.CurrentDungeon = 0;
	CurrentProgress.CurrentLevelName = LevelInformation[CurrentProgress.CurrentLevel].DungeonsInLevel[CurrentProgress.CurrentDungeon].MapNameOfPart;
	CurrentProgress.CurrentDifficulty = 0;
	CurrentProgress.CurrentLevelPoints = 0;
	CurrentProgress.CurrentPart = EPartInformation::EPI_LEVEL1;

	PlayMode = EPlayMode::PM_CLASSIC;

	SaveGame->ResetProgressData();

	SaveGameData();

	OpenMap(MapDefinition.LevelName_Menu);
}
#pragma endregion

#pragma region Set Progress
void UGameInstanceManager::SetProgress(int32 Level, int32 Dungeon, int32 Part, int32 Difficulty)
{
	if (Level >= LevelInformation.Num())
	{
		Level = LevelInformation.Num() - 1;
	}
	if (Dungeon >= LevelInformation[Level].DungeonsInLevel.Num())
	{
		Dungeon = LevelInformation[Level].DungeonsInLevel.Num() - 1;
	}
	if (Part >= EPartInformation::EPI_END)
	{
		Part = EPartInformation::EPI_LEVEL3;
	}

	LOG_WARNING(RuntimeExecutionLog, "Better check the difficulty here via PlayModeInformation, too")
	
	CurrentProgress.CurrentLevel = Level;
	CurrentProgress.CurrentDungeon = Dungeon;
	CurrentProgress.CurrentPart = (EPartInformation)Part;
	CurrentProgress.CurrentDifficulty = Difficulty;
	CurrentProgress.CurrentLevelName = FName(LevelInformation[CurrentProgress.CurrentLevel].DungeonsInLevel[CurrentProgress.CurrentDungeon].MapNameOfPart);

	SaveGame->UpdateProgressToValues(PlayMode, Level, Dungeon, Difficulty, Part);

	SaveGameData();

	OpenMap(MapDefinition.LevelName_Menu);
}
#pragma endregion

#pragma endregion

#pragma region Set Game Information
void UGameInstanceManager::SetGameInformation(int32 Level, int32 Dungeon, int32 Part, int32 NumChests, int32 NumTraps, int32 NumGarbage)
{
	bool okay = true;
	if (Level >= LevelInformation.Num())
	{
		LOG_WARNING(RuntimeExecutionLog,"Could not set game information for this level")
		okay = false;
	}
	if (Dungeon >= LevelInformation[Level].DungeonsInLevel.Num())
	{
		LOG_WARNING(RuntimeExecutionLog,"Could not set game information for this dungeon")
		okay = false;
	}
	if (Part >= EPartInformation::EPI_LEVEL3)
	{
		LOG_WARNING(RuntimeExecutionLog,"Could not set game information for this part")
		okay = false;
	}
	if (Part == 0)
	{
		LOG_WARNING(RuntimeExecutionLog,"Could not set game information for part 0")
		okay = false;
	}

	if (!okay)
	{
		return;
	}

	LOG_WARNING(RuntimeExecutionLog, "Uncommented Functionality - Please Review")
	//LevelInformation[Level].DungeonsInLevel[Dungeon].DungeonParts[Part - 1].NumberOfChests = NumChests;
	//LevelInformation[Level].DungeonsInLevel[Dungeon].DungeonParts[Part - 1].NumberOfTraps = NumTraps;
	//LevelInformation[Level].DungeonsInLevel[Dungeon].DungeonParts[Part - 1].NumberOfGarbage= NumGarbage;

	SaveGameData();

	OpenMap(MapDefinition.LevelName_Menu);
}
#pragma endregion

#pragma region Play FMOD Titles
void UGameInstanceManager::PlayRandomMusicTitle()
{
	AGameModeBase* Mode = UGameplayStatics::GetGameMode(GetWorld());

	if (Mode == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog,"GameMode was null ! This shouldn't happen !")
		return;
	}

	AGameMode_Game* GameMode = Cast<AGameMode_Game>(Mode);

	if (GameMode == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog,"GameMode was null ! This only works in Gameplay!")
	}

	GameMode->SetTitle(EventList.ListOfTitles[FMath::RandRange(0, EventList.ListOfTitles.Num())]);
}

void UGameInstanceManager::PlayMusicTitle(int8 Index)
{
	AGameModeBase* Mode = UGameplayStatics::GetGameMode(GetWorld());

	if (Mode == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "GameMode was null ! This shouldn't happen !")
		return;
	}

	AGameMode_Game* GameMode = Cast<AGameMode_Game>(Mode);

	if (GameMode == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "GameMode was null ! This only works in Gameplay!")
	}

	if (EventList.ListOfTitles.Num() >= Index)
	{
		GameMode->SetTitle(EventList.ListOfTitles[Index]);
		
	}
	else
	{
		LOG_WARNING(RuntimeExecutionLog, "Index too high. Playing Random Title")
		PlayRandomMusicTitle();
	}
}
#pragma endregion

void UGameInstanceManager::UltraSpeed()
{
	AFirstPersonCharacter* Character = Cast<AFirstPersonCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));

	if (Character == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Could not find Character. Maybe not in Game")
		return;
	}

	Character->SetSpeedValue(1500);
}

void UGameInstanceManager::SetWalkSpeed(float Speed)
{
	AFirstPersonCharacter* Character = Cast<AFirstPersonCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if (Character == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Could not find Character. Maybe not in Game")
			return;
	}

	Character->SetSpeedValue(Speed);
}

#pragma region PlayModeSettings

#pragma region PlayMode Types
void UGameInstanceManager::Crazy()
{
	PlayMode = EPlayMode::PM_CRAZY;
	AcceptPlayMode();
}

void UGameInstanceManager::Default()
{
	PlayMode = EPlayMode::PM_DEFAULT;
	AcceptPlayMode();
}

void UGameInstanceManager::Lazy()
{
	PlayMode = EPlayMode::PM_LAZY;
	AcceptPlayMode();
}

void UGameInstanceManager::Unlocked()
{
	PlayModeExtraModifier = EPlayMode::PM_UNLOCKED;
	AcceptPlayMode();
}

void UGameInstanceManager::HopHopMode()
{
	LOG_WARNING(InitializationLog, "HopHop Mode entered")
	if (PlayMode != EPlayMode::PM_TEST && PlayMode != EPlayMode::PM_HOPHOP )
	{
		TempPlayMode = PlayMode;
	}
	PlayMode = EPlayMode::PM_HOPHOP;
	AcceptPlayMode();
}

void UGameInstanceManager::TestMode()
{
	if (PlayMode != EPlayMode::PM_HOPHOP)
	{
		TempPlayMode = PlayMode;
	}
	PlayMode = EPlayMode::PM_TEST;
	AcceptPlayMode();
}

void UGameInstanceManager::ShiftToPartTwo()
{
	if (SaveGame == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "SaveGame was null ! This shouldn't happen !")
			return;
	}
	else
	{
		if (SaveGame->bIsPart2 == true)
		{
			return;
		}
	}


	auto SecretSlogan = SecretSlogans.Slogans[0];

	if (MenuUI != nullptr)
	{
		MenuUI->AchievementInputBox->SecretUnlockedMessage(SecretUnlocked, FText::FromString(SecretSlogan.Slogan), SecretSlogan.Message, true);
		MenuUI->SetNewlyAchieved();
	}
	if (SaveGame == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "SaveGame was null ! This shouldn't happen !")
	}
	else
	{
		for (auto SecretConnection : SecretConnections)
		{
			if (SecretConnection.Index == SecretSlogan.SloganIndex)
			{
				for (auto Credential : SecretConnection.SecretCredentials)
				{
					if (!SaveGame->KnowSecretCredentials.Contains(Credential))
					{
						SaveGame->KnowSecretCredentials.Add(Credential);
					}
				}
			}
		}

		SaveGame->ShiftToPartTwo();
		SaveGame->AddSolvedSecretSloganIndex(0);
		SaveGame->bIsPart2 = true;
		SaveGameData();
	}

	SetCurrentLevelName(MapDefinition.LevelName_Menu);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_ReloadMenu, this, &UGameInstanceManager::LoadLevelFinished, .1f, false, TimeToWaitForReloadMenu);	
}

void UGameInstanceManager::ResetTestModes()
{
	if (PlayMode == EPlayMode::PM_HOPHOP || PlayMode == EPlayMode::PM_TEST)
	{
		PlayMode = TempPlayMode;
	}
	SaveGame->SetGamePlayMode(PlayMode);
	SaveGameData();
}

void UGameInstanceManager::TestSecretSlogan(FString SloganToTest)
{
	LOG_WARNING(RuntimeExecutionLog, "--------------------------")
	LOG_WARNING(RuntimeExecutionLog, "Testing for Secret Slogan")
	LOG_WARNING(RuntimeExecutionLog, "--------------------------")
	bool Success = false;
	for (auto Slogan : SecretSlogans.Slogans)
	{
		if (Slogan.Slogan == SloganToTest)
		{
			LOG_WARNING(RuntimeExecutionLog, "This slogan matched the list !")
			Success = true;
			break;
		}
	}
	if (!Success)
	{
		LOG_WARNING(RuntimeExecutionLog, "Could not find Slogan !")
	}
	LOG_WARNING(RuntimeExecutionLog, "--------------------------")
}

void UGameInstanceManager::AddExtraLevels()
{
	LOG_WARNING(RuntimeExecutionLog, "Adding Extra Levels to Information")
}

void UGameInstanceManager::ShowHideUI(bool Show)
{
	if (MainUI == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Cannot hide UI, because it was null.")
	}
	else
	{
		if (Show)
		{
			MainUI->StartAnimation(7);
		}
		else
		{
			MainUI->StartAnimation(6);
		}
	}
}

void UGameInstanceManager::Classic()
{
	PlayMode = EPlayMode::PM_CLASSIC;
	AcceptPlayMode();
}
#pragma endregion

void UGameInstanceManager::ShowSpiderWebs(int32 OnOff)
{
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), USpiderWebInterface::StaticClass(), Actors);
	
	if (Actors.Num() == 0)
		return;

	switch (OnOff)
	{
	case 0:
		for (auto Actor : Actors)
		{
			Actor->SetActorHiddenInGame(true);
		}
		break;
	case 1:
		for (auto Actor : Actors)
		{
			Actor->SetActorHiddenInGame(false);
		}
		break;
	default:
		break;
	}
}

void UGameInstanceManager::AcceptPlayMode()
{
	for (auto Modifier : PlayModeModifiers)
	{
		if (Modifier.PlayMode == PlayMode)
		{
			if (Modifier.GameTypeAudioApplier != nullptr)
			{
				UGameplayStatics::SpawnSound2D(GetWorld(), Modifier.GameTypeAudioApplier);
			}
		}
	}

	SaveGame->SetGamePlayMode(PlayMode);

	SaveGameData();

	UpdateCurrentProgress();

	if (LevelSelector != nullptr)
	{
		LevelSelector->RemoveFromViewport();
		LevelSelector = nullptr;
	}
}

#pragma endregion

#pragma region Game Stats Debugger
void UGameInstanceManager::ShowGameStats(bool On)
{
	if (MainUI == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog,"Not Ingame. Can't show Stats")
		return;
	}

	if (On)
	{
		MainUI->StartAnimation(2);
	}
	else
	{
		MainUI->StartAnimation(3);
	}
}
#pragma endregion

#pragma region IsSecret Accessible
bool UGameInstanceManager::IsSecretAccessible(FString SecretCode)
{
	TArray<FString> KnownCodes = SaveGame->GetKnowSecretCredentials();
	switch (PlayMode)
	{
	case EPlayMode::PM_LAZY:
	case EPlayMode::PM_CLASSIC:
		return false;
		break;
	case EPlayMode::PM_CRAZY:
	case EPlayMode::PM_DEFAULT:
		if (KnownCodes.Num() == 0)
		{
			//LOG_WARNING(RuntimeExecutionLog, "No Credentials Known")
			break;
		}
		else
		{
			for (auto KnownCode : KnownCodes)
			{
				//UE_LOG(LogTemp, Warning, TEXT("Known Credential: %s, SecretCode: %s"), *KnownCode, *SecretCode);
				if (KnownCode.Equals(SecretCode))
				{
					return true;
				}
			}
		}
		break;
	case EPlayMode::PM_IRREGULAR:
		return false;
		break;
	default:
		break;
	}

	if(PlayModeExtraModifier == EPlayMode::PM_UNLOCKED)
	{
		return true;
	}	

	return false;
}
#pragma endregion
UENUM(BlueprintType)
enum class ESolveSuccess : uint8
{
	No,
	TooEarly,
	Yes
};

void UGameInstanceManager::CheckSecretMessageTypedIn(const FText& Text)
{
	FString SloganToTest = Text.ToString();
	ESolveSuccess Success = ESolveSuccess::No;
	FSecretSlogan SecretSlogan = FSecretSlogan();
	for(int i = 0; i < SecretSlogans.Slogans.Num(); i++)
	{
		auto Slogan = SecretSlogans.Slogans[i];
		if (Slogan.Slogan == SloganToTest)
		{
			if (Slogan.LevelPointsToSolve > CurrentProgress.CurrentLevelPoints)
			{
				LOG_DISPLAY(RuntimeExecutionLog, "This slogan matched the list, but you have not enought levelpoints to solve. !")
				Success = ESolveSuccess::TooEarly;
				MenuUI->AchievementInputBox->SecretUnlockedMessage(SecretUnlockedToEarlyTitle, SecretUnlockedToEarlyGrats, SecretUnlockedToEarlyMessage, false);
				break;
			}
			else
			{
				MenuUI->HideElementsForAchievementMessage();
				LOG_DISPLAY(RuntimeExecutionLog, "This slogan matched the list !")
				SecretSlogan = SecretSlogans.Slogans[i];
				SaveGame->AddSolvedSecretSloganIndex(i);
				if (MenuUI != nullptr)
				{
					MenuUI->AchievementInputBox->SecretUnlockedMessage(SecretUnlocked, FText::FromString(SecretSlogan.Slogan), SecretSlogan.Message, true);
				}
				if (SaveGame == nullptr)
				{
					LOG_WARNING(RuntimeExecutionLog,"SaveGame was null ! This shouldn't happen !")
				}
				else
				{
					for (auto SecretConnection : SecretConnections)
					{
						if (SecretConnection.Index == Slogan.SloganIndex)
						{
							for (auto Credential : SecretConnection.SecretCredentials)
							{
								if (!SaveGame->KnowSecretCredentials.Contains(Credential))
								{
									SaveGame->KnowSecretCredentials.Add(Credential);
								}
							}
							if(SaveGame->bIsPart2 == false)
								SaveGame->bIsPart2 = true;

							MenuUI->SetNewlyAchieved();
							SaveGameData();
							SetCurrentLevelName(MapDefinition.LevelName_Menu);
							TestAchievements(EAchievementType::AT_SECRETUNLOCKED, SecretConnection.Index);
							GetWorld()->GetTimerManager().SetTimer(TimerHandle_ReloadMenu, this, &UGameInstanceManager::LoadLevelFinished, .1f, false, TimeToWaitForReloadMenu);
							break;
						}
					}
				}

				Success = ESolveSuccess::Yes;
				break;
			}
		}
	}
	if (Success == ESolveSuccess::No)
	{
		LOG_DISPLAY(RuntimeExecutionLog, "Could not find Slogan !")
		MenuUI->AchievementInputBox->SecretUnlockedMessage(SecretUnlockedFailTitle, SecretUnlockedFailGrats, SecretUnlockedFailMessage, false);
	}

	if (GetMenuGameMode() != nullptr)
	{
		GetMenuGameMode()->bAchievementInputVisible = false;
	}
}



TArray<FHighScoreEntry> UGameInstanceManager::GetHighScoresForSettings(EPlayMode ViewedPlayMode, int32 Level, int32 Dungeon, int32 Difficulty, int32 Part)
{
	if (SaveGame == nullptr)
	{
		return TArray<FHighScoreEntry>();
	}
	else
	{
		return SaveGame->GetHighScoresForSettings(ViewedPlayMode, Level, Dungeon, Difficulty, Part);
	}
}

void UGameInstanceManager::AddHighScoreEntry(FString Name)
{
	if (SaveGame == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "SaveGame was null ! This shouldn't happen !")
	}
	else
	{
		FHighScoreComplete NewEntry = FHighScoreComplete();

		NewEntry.PlayMode = PlayMode;
		NewEntry.Name = Name;
		NewEntry.BonusPickups = 0;
		NewEntry.DateOfPlayedScore = FDateTime::Now();

		IGameStateInterface* GameState = Cast<IGameStateInterface> (UGameplayStatics::GetGameState(GetWorld()));

		if (GameState == nullptr)
		{
			LOG_WARNING(RuntimeExecutionLog, "Could not cast GameState ! This shouldn't happen !")
		}
		else
		{
			FHighScoreEntry NewScore = GameState->GetHighScoreEntry();
			NewEntry.Score = NewScore.Score;
			NewEntry.TimeSucceeded = NewScore.TimeSucceeded;
			NewEntry.Difficulty = GameState->GetCurrentDifficulty();
			NewEntry.Dungeon = GameState->GetCurrentDungeon();
			NewEntry.Level = GameState->GetCurrentLevel();
			NewEntry.Part = GameState->GetCurrentPart();

			GameState->ContinueGamePlay();
		}

		SaveGame->AddHighScore(NewEntry);

		SaveGameData(); 
	}
}


bool UGameInstanceManager::TestCredentials(FString Credentials)
{
	if (SaveGame == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "SaveGame was null ! This shouldn't happen !")
		return false;
	}
	else
	{
		if (SaveGame->KnowSecretCredentials.Contains(Credentials))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}
