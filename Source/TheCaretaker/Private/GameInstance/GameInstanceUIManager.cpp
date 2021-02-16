/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "GameInstance/GameInstanceManager.h"

#include "Actors/Pickups/PowerUp/PowerUp.h"
#include "Actors/Pickups/Pickup/SingleObjectPickup.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Controllers/Player/CaretakerPlayerController.h"
#include "Components/VerticalBox.h"
#include "Engine/World.h"
#include "GameFramework/GameModeBase.h"
#include "Interfaces/GameState/GameStateInterface.h"
#include "Interfaces/ActorMarker/MarkerWidgetActorInterface.h"
#include "Interfaces/Tutorial/TutorialInterface.h"
#include "Interfaces/Widgets/IngameMenu/IngameMenuWidgetInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Log/GlobalLog.h"
#include "SaveGame/TheCaretakerSaveGame.h"
#include "Widgets/Base/UserWidgetBase.h"
#include "Widgets/Main/MainUI.h"
#include "Widgets/LevelSelect/LevelSelectionUserWidget.h"
#include "Widgets/Extras/ExtrasMenuUserWidget.h"
#include "Widgets/Information/InformationWidget.h"
#include "Widgets/Map/Marker/ActorMarkerWidget.h"
#include "Widgets/Map/MiniMapWidget.h"
#include "Widgets/Monsters/MonsterInformationWidget.h"
#include "Widgets/Monsters/MonsterList/MonsterHungerViewWidget.h"
#include "Widgets/Menu/MainMenuWidget.h"
#include "Widgets/Main/MainUI.h"
#include "Widgets/Pickup/PickupUserWidget.h"
#include "Widgets/NoiseBar/NoiseBarUserWidget.h"
#include "Widgets/Time/TimeInformationWidget.h"
#include "Widgets/Scores/CurrentScoreUserWidget.h"
#include "Widgets/Scores/CurrentHighScoreUserWidget.h"
#include "Widgets/Scores/CurrentFinalScoreUserWidget.h"
#include "Widgets/Secret/SecretCredentialsUserWidget.h"
#include "Widgets/Secret/SecretCredentialUserWidget.h"
#include "Widgets/TrapTimer/TrapTimerUserWidget.h"

void UGameInstanceManager::SetTrapBarValue(float Value)
{
	if (MainUI == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "MainUI was null ! This shouldn't happen !")
	}
	else
	{
		MainUI->TrapTimer->SetTrapTimerValue(Value);
	}
}

void UGameInstanceManager::ResetTrapBar()
{
	if (MainUI == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "MainUI was null ! This shouldn't happen !")
	}
	else
	{
		MainUI->TrapTimer->SetTrapTimerValue(0);
		MainUI->TrapTimer->SetVisibility(ESlateVisibility::Hidden);

	}
}

void UGameInstanceManager::ShowTrapBar()
{
	if (MainUI == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "MainUI was null ! This shouldn't happen !")
	}
	else
	{
		MainUI->TrapTimer->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
}

void UGameInstanceManager::TestCompetitionMode()
{
	if (!CompetitionAvailable())
		return;

	if (MenuUI == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "MenuUI was null !")
	}
	else
	{
		LOG_WARNING(InitializationLog, "Playing Competition Animation")
		MenuUI->PlayCompetitionAnimation();
	}
}

void UGameInstanceManager::PickupCollected(TSubclassOf<APowerUp> NewPowerUpClass)
{
	if (MainUI == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Main UI was null ! This shouldn't happen !")
	}
	else
	{
		ACaretakerPlayerController* PlayerController = Cast<ACaretakerPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

		if (PlayerController == nullptr)
		{
			LOG_WARNING(RuntimeExecutionLog,"PlayerController was null ! This shouldn't happen !")
		}
		else
		{
			if (NewPowerUpClass == nullptr)
			{
				LOG_WARNING(RuntimeExecutionLog,"New PowerUp Class was null ! This shouldn't happen !")
			}
			else
			{
				CurrentPowerUpClass = NewPowerUpClass;
				PlayerController->SetPickupCollected(true);
				MainUI->StartAnimation(11);
			}
		}
	}
}

void UGameInstanceManager::PickupDropped(FVector Location)
{
	if (MainUI == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Main UI was null ! This shouldn't happen !")
	}
	else
	{
		ACaretakerPlayerController* PlayerController = Cast<ACaretakerPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

		if (PlayerController == nullptr)
		{
			LOG_WARNING(RuntimeExecutionLog, "PlayerController was null ! This shouldn't happen !")
		}
		else
		{
			if (CurrentPickUpClass == nullptr)
			{
				LOG_WARNING(RuntimeExecutionLog, "Current Pickup Class was null ! This must be setup in the GameInstance!")
			}
			else
			{
				PlayerController->SetPickupCollected(false);
				MainUI->StartAnimation(12);

				FTransform SpawnLocation;
				SpawnLocation.AddToTranslation(Location);
				SpawnLocation.AddToTranslation(FVector(0.f,0.f,30.f));

				ASingleObjectPickup* Pickup = GetWorld()->SpawnActor<ASingleObjectPickup>(CurrentPickUpClass, SpawnLocation);
				//Pickup->PowerUpClass = CurrentPowerUpClass;
				//Pickup->SetSpawnLocation(SpawnLocation.GetLocation());
				//Pickup->KillPowerUpActor();
				//Pickup->Respawn();
			}
		}
	}
}

bool UGameInstanceManager::IsNewHighScoreAchieved(const int32 Level, const int32 Dungeon, const int32 Difficulty, const int32 Part, const int32 Score, const float Time)
{
	TArray<FHighScoreEntry> CurrentScores = GetHighScoresForSettings(PlayMode, Level, Dungeon, Difficulty, Part);

	if (CurrentScores.Num() == 0)
	{
		LOG_WARNING(RuntimeExecutionLog, "HighScores were count 0 ! This shouldn't happen !")
			return false;
	}

	if (MainUI == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Not In Game ! Returning !")
			return false;
	}

	if (CurrentScores.Num() >= 10)
	{
		for (int32 i = 9; i >= 0; i--)
		{
			if (CurrentScores[i].Score > Score)
			{
				if (i == 9)
				{
					return false;
				}

				if (i == 8)
				{
					//MainUI->HighScore->SetValues(10, CurrentScores[i + 1].Name, CurrentScores[i + 1].Score);
					MainUI->HighScore->SetFocus(10, Score, Time);
					return true;
				}

				for (int32 j = i+1; j < 9; j++)
				{
					if (j + 2 <= 10)
					{
						MainUI->HighScore->SetValues(j + 2, CurrentScores[j].Name, CurrentScores[j].Score, Time);
					}
				}

				MainUI->HighScore->SetFocus(i + 2, Score, Score);
				return true;
			}
		}
		if (CurrentScores[0].Score < Score)
		{
			for (int32 i = 0; i < 9; i++)
			{
				MainUI->HighScore->SetValues(i+2, CurrentScores[i].Name, CurrentScores[i].Score, CurrentScores[i].TimeSucceeded);
			}
			MainUI->HighScore->SetFocus(1, Score, Time);
			return true;
		}
	}

	return false;
}

void UGameInstanceManager::UpdateHighScoreWidget(int32 Level, int32 Dungeon, int32 Difficulty, int32 Part)
{
	if (MainUI == nullptr)
	{
		LOG_DISPLAY(RuntimeExecutionLog, "Not In Game. Skipping")
	}
	else
	{
		TArray<FHighScoreEntry> HighScore = GetHighScoresForSettings(PlayMode, Level, Dungeon, Difficulty, Part);

		if (HighScore.Num() == 0)
		{
			LOG_WARNING(RuntimeExecutionLog, "No Highscores found ! This shouldn't happen !")
			return;
		}

		LOG_DISPLAY(RuntimeExecutionLog, "Updating Highscore")

		if (HighScore.Num() < 10)
		{
			for (int32 i = 0; i < HighScore.Num(); i++)
			{
				MainUI->HighScore->SetValues(i + 1, HighScore[i].Name, HighScore[i].Score, HighScore[i].TimeSucceeded);
			}
		}
		else
		{
			for (int32 i = 0; i < 10; i++)
			{
				MainUI->HighScore->SetValues(i + 1, HighScore[i].Name, HighScore[i].Score, HighScore[i].TimeSucceeded);
			}
		}
	}
}

void UGameInstanceManager::HideWinInformation()
{
	TArray<UUserWidget*> Widgets;
	UWidgetBlueprintLibrary::GetAllWidgetsWithInterface(GetWorld(), Widgets, UIngameMenuWidgetInterface::StaticClass(), false);
	if (Widgets.Num() == 0)
	{
		LOG_WARNING(RuntimeExecutionLog, "Could not find Ingame Menu Interface ! This shouldn't happen !")
	}
	else
	{
		IIngameMenuWidgetInterface* Interface = Cast<IIngameMenuWidgetInterface>(Widgets[0]);
		if (Interface == nullptr)
		{
			LOG_WARNING(RuntimeExecutionLog, "Could not cast Widget to Interface ! This shouldn't happen !")
		}
		else
		{
			Interface->HideInformationCall();
		}
	}
}

void UGameInstanceManager::CallHideHighscore()
{
	if (MainUI == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Main UI was null ! This shouldn't happen !")
	}
	else
	{
		MainUI->StartAnimation(10);
	}
}

void UGameInstanceManager::CallShowHighscore()
{
	if (MainUI == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Main UI was null ! This shouldn't happen !")
	}
	else
	{
		MainUI->StartAnimation(9);
	}
}

void UGameInstanceManager::SetScoreInGame(int32 ScoreInGame)
{
	if (MainUI == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Could not Set Game Score, because MainUI was null ! This shouldn't happen !")
	}
	else
	{
		MainUI->FinalScore->SetScoreInGame(ScoreInGame);
	}
}

void UGameInstanceManager::SetMeatBonus(int32 MeatBonus)
{
	if (MainUI == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Could not Set Meat Score, because MainUI was null ! This shouldn't happen !")
	}
	else
	{
		MainUI->FinalScore->SetMeatBonus(MeatBonus);
	}
}

void UGameInstanceManager::SetHungerBonus(int32 HungerBonus)
{
	if (MainUI == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Could not Set Hunger Bonus Score, because MainUI was null ! This shouldn't happen !")
	}
	else
	{
		MainUI->FinalScore->SetHungerBonus(HungerBonus);
	}
}

void UGameInstanceManager::SetFinishBonus(int32 FinishBonus)
{
	if (MainUI == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Could not Set Finish Bonus Score, because MainUI was null ! This shouldn't happen !")
	}
	else
	{
		MainUI->FinalScore->SetFinishBonus(FinishBonus);
	}
}

void UGameInstanceManager::SetPickupBonus(int32 PickupBonus)
{
	if (MainUI == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Could not Set Pickup Bonus Score, because MainUI was null ! This shouldn't happen !")
	}
	else
	{
		MainUI->FinalScore->SetPickupBonus(PickupBonus);
	}
}

void UGameInstanceManager::SetFinalScore(int32 FinalScore)
{
	if (MainUI == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Could not Set Final Score, because MainUI was null ! This shouldn't happen !")
	}
	else
	{
		MainUI->FinalScore->SetFinalScore(FinalScore);
	}
}

void UGameInstanceManager::ShowFinalScore()
{
	if (MainUI == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Could not Show Final Score, because MainUI was null ! This shouldn't happen !")
	}
	else
	{
		//MainUI->Monsters->
		MainUI->FinalScore->PlaySound();
		MainUI->FinalScore->PlayFinalScoreAnimation();
	}
}

void UGameInstanceManager::HideFinalScore()
{
	if (MainUI == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Could not hide Final Score, because MainUI was null ! This shouldn't happen !")
	}
	else
	{
		MainUI->FinalScore->HideScore();
	}
}

TArray<int32> UGameInstanceManager::GetSlogansIndicesLevelpoints() const
{
	TArray<int32> ReturnValue = TArray<int32>();
	for (int32 i = 0; i < SecretSlogans.Slogans.Num(); i++)
	{
		ReturnValue.Add(SecretSlogans.GetLevelPointsForIndex(i));
	}
	return ReturnValue;
}

void UGameInstanceManager::ShowPickupWidget(bool Show)
{
	if (MainUI == nullptr)
	{
		LOG_WARNING(InitializationLog, "")
	}
	else
	{	
		MainUI->PickupWidget->PlayPickupAnimation(Show);		
	}
}

UCurrentScoreUserWidget* UGameInstanceManager::AddScoreWidget()
{
	LOG_WARNING(InitializationLog, "Adding Score Widget to UI")
	if (CurrentScoreBlueprint == nullptr)
	{
		LOG_WARNING(InitializationLog, "Could not add ScoreWidget, because Blueprint was null. Is it setup in the Game Instance Blueprint ?")
	}
	else
	{
		if (MainUI == nullptr)
		{
			LOG_WARNING(InitializationLog, "Could not add ScoreWidget, because MainUI was null. This shouldn't happen!")
		}
		else
		{
			UCurrentScoreUserWidget* ScoreWidget = CreateWidget<UCurrentScoreUserWidget>(GetWorld(), CurrentScoreBlueprint);

			if (ScoreWidget == nullptr)
			{
				LOG_WARNING(InitializationLog, "Could not add ScoreWidget, because it was null after creation. This shouldn't happen!")
				return nullptr;
			}
			else
			{
				MainUI->Monsters->AddScoreWidget(ScoreWidget);
				return ScoreWidget;
			}
		}
	}
	return nullptr;
}

void UGameInstanceManager::SetNoiseMultiplier(float Value)
{
	if (MainUI == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Could not set NoiseMultiplier, because MainUI was null ! ")
	}
	else
	{
		MainUI->Noisebar->SetNoiseBarMultiplier(Value);
	}
}

void UGameInstanceManager::HideUnwantedUIElementsOnFinish()
{
	if (MainUI == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Could not set NoiseMultiplier, because MainUI was null ! ")
	}
	else
	{
		MainUI->Noisebar->SetVisibility(ESlateVisibility::Hidden);
		MainUI->Clock->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UGameInstanceManager::OpenDialog(const EMenuDialog TypeOfDialog, ISwitchableWidgetInterface* CurrentParent)
{
	UUserWidgetBase* CurrentDialog = nullptr;

	switch (TypeOfDialog)
	{
	case EMenuDialog::MD_NONE:
		break;
	case EMenuDialog::MD_OPTIONS:
		CurrentDialog = OptionsWidget;
		break;
	case EMenuDialog::MS_LEVELSELECT:
		CurrentDialog = LevelSelector;
		break;
	case EMenuDialog::MS_CREDENTIALS:
		CurrentDialog = CredentialsView;
		break;
	default:
		break;
	}

	if (CurrentDialog != nullptr)
	{
		CurrentDialog->SetParent(CurrentParent);
		CurrentDialog->ShowWidget(true);
		CurrentDialog->ShowParent();
		CurrentDialog->AddToViewport();
		LOG_WARNING(RuntimeExecutionLog, "Already having widget")
	}
	else
	{
		LOG_WARNING(RuntimeExecutionLog,"Creatingwidget")
		CreateNewUserWidget(TypeOfDialog, CurrentParent);
	}
}

void UGameInstanceManager::CallUI(const EUIEnum UiToCall)
{
	if (UiToCall == EUIEnum::UI_GAME)
	{
		if (MainUiTemplate != nullptr)
		{
			// Create the widget and store it.
			MainUI = CreateWidget<UMainUI>(this, MainUiTemplate);

			ITutorialInterface* IsTutorial = Cast<ITutorialInterface>(UGameplayStatics::GetGameMode(GetWorld()));

			if (IsTutorial != nullptr)
			{
				MainUI->bTutorialPlaying = true;
			}

			// now you can use the widget directly since you have a referance for it.
			// Extra check to  make sure the pointer holds the widget.
			if (MainUI)
			{
				//let add it to the view port
				MainUI->AddToViewport();

				SetMouseEvents(false);
			}
			else
			{
				LOG_WARNING(InitializationLog, "Creation of Main UI failed ! This shouldn't happen !");
			}
		}
		else
		{
			LOG_WARNING(RuntimeExecutionLog, "UI Blueprint was null in GameMode. Please set up UIWidgetBlueprint with a valid UserWidget");
		}
	}
	else if (UiToCall == EUIEnum::UI_MENU)
	{
		if (MainMenuTemplate)
		{
			// Create the widget and store it.
			MenuUI = CreateWidget<UMainMenuWidget>(this, MainMenuTemplate);

			if (SaveGame == nullptr)
			{
				LOG_WARNING(InitializationLog, "SaveGame was null ! This shouldn't happen !")
			}
			else
			{
				MenuUI->SetPart2(SaveGame->bIsPart2);
			}

			// now you can use the widget directly since you have a referance for it.
			// Extra check to  make sure the pointer holds the widget.
			if (MenuUI)
			{
				//let add it to the view port
				MenuUI->AddToViewport();

				SetMouseEvents(true);
			}
			else
			{
				LOG_WARNING(RuntimeExecutionLog, "Creation of Menu UI failed ! This shouldn't happen !");
			}
		}
		else
		{
			LOG_WARNING(RuntimeExecutionLog, "UI Blueprint was null in GameMode. Please set up MenuWidgetBlueprint with a valid UserWidget");
		}
	}
}

bool UGameInstanceManager::GetNewProgressBarWidget(UMonsterInformationWidget* &MonsterInformation)
{
	UWorld* World = GetWorld();
	if (World == nullptr)
	{
		LOG_WARNING(InitializationLog, "GameInstance could not find world! Cannot Create Feeding ProgressBar!");
		return false;
	}
	if (MainUI == nullptr)
	{
		LOG_WARNING(InitializationLog, "GameInstance could not find MainUI! Cannot Create Feeding ProgressBar!");
		return false;
	}
	if (MonsterInformationTemplate == nullptr)
	{
		LOG_WARNING(InitializationLog, "GameInstance could not find ProgressBar Widget! Cannot Create Feeding ProgressBar!");
		return false;
	}
	if (MainUI->Monsters == nullptr)
	{
		LOG_WARNING(InitializationLog, "GameInstance could not find Monsters widget in Main UI! Cannot Create Feeding ProgressBar!");
		return false;
	}
	if (MainUI->Monsters->MonsterList == nullptr)
	{
		LOG_WARNING(InitializationLog, "GameInstance could not find MonstersList in Monster Widget! Cannot Create Feeding ProgressBar!");

		return false;
	}
		
	MonsterInformation = CreateWidget<UMonsterInformationWidget>(World, MonsterInformationTemplate);

	MainUI->Monsters->MonsterList->AddChild(MonsterInformation);
	MainUI->Monsters->AddMonster(MonsterInformation);
	
	return true;
}

void UGameInstanceManager::CreateNewUserWidget(const EMenuDialog TypeOfDialog, ISwitchableWidgetInterface* CurrentParent)
{
	UUserWidgetBase* CurrentDialog = nullptr;

	switch (TypeOfDialog)
	{
	case EMenuDialog::MD_NONE:
		break;
	case EMenuDialog::MD_OPTIONS:
	{
		if (MainSettingsTemplate)
		{
			// Create the widget and store it.
			OptionsWidget = CreateWidget<UUserWidgetBase>(this, MainSettingsTemplate);
			CurrentDialog = OptionsWidget;
		}
		break;
	}
	case EMenuDialog::MS_LEVELSELECT:
	{
		if (MainSettingsTemplate)
		{
			// Create the widget and store it.
			LevelSelector = CreateWidget<UUserWidgetBase>(this, LevelSelectorBlueprint);
			CurrentDialog = LevelSelector;
		}
		break;
	}
	case EMenuDialog::MS_CREDENTIALS:
	{
		if (MainSettingsTemplate)
		{
			// Create the widget and store it.
			CredentialsView = CreateWidget<UUserWidgetBase>(this, CredentialsViewBlueprint);
			CurrentDialog = CredentialsView;
		}
		break;
	}
	default:
		break;
	}

	// now you can use the widget directly since you have a referance for it.
	// Extra check to  make sure the pointer holds the widget.
	if (CurrentDialog != nullptr)
	{
		CurrentDialog->SetParent(CurrentParent);
		CurrentDialog->ShowWidget(true);
		if (TypeOfDialog == EMenuDialog::MS_LEVELSELECT)
		{
			CurrentDialog->ShowParent();
		}
		//let add it to the view port
		CurrentDialog->AddToViewport();
	}
	else
	{
		LOG_DEFAULT(RuntimeLog, "Creation of OptionsMenu failed ! This shouldn't happen !");
	}
}

UActorMarkerWidget* UGameInstanceManager::AttachActorMarkerWidget(AActor* Actor, UTexture2D* MarkerImage, bool IsMonster)
{
	if (MainUI == nullptr)
	{
		LOG_DISPLAY(InitializationLog, "Main UI was null ! Putting Actor Marker on Temp List. Too Early in Game")
		TempMarkerInfo.Add(FSpawnMarkerWidgetInformation(Actor, MarkerImage, IsMonster));
		return nullptr;
	}

	if (ActorMarkerTemplate == nullptr)
	{
		LOG_WARNING(InitializationLog, "Actor Marker Template was null ! This shouldn't happen ! Not Spawning MonsterMarker on MiniMap")
		return nullptr;
	}

	while (TempMarkerInfo.Num() > 0)
	{
		FSpawnMarkerWidgetInformation Information = TempMarkerInfo.Pop();

		UActorMarkerWidget* TempMarkerWidget = CreateWidget<UActorMarkerWidget>(GetWorld(), ActorMarkerTemplate);

		if (TempMarkerWidget != nullptr)
		{
			TempMarkerWidget->SetActorImage(Information.Texture);
			TempMarkerWidget->SetSize(FVector2D(50.f, 50.f));
			TempMarkerWidget->SetActor(Information.Actor);
			TempMarkerWidget->SetMiniMapInterface(MainUI->MiniMap);
			TempMarkerWidget->SetIsMonster(Information.bIsMonster);
			MainUI->MiniMap->AddActorMarker(TempMarkerWidget);
			TempMarkerWidget->RegisterActorMarkerWidget();

			IMarkerWidgetActorInterface* ActorInterface = Cast<IMarkerWidgetActorInterface> (Information.Actor);
			if (ActorInterface == nullptr)
			{
				LOG_DISPLAY(InitializationLog, "Actor Interface was null ! This shouldn't happen !")
			}
			else
			{
				ActorInterface->SetMarkerWidget(TempMarkerWidget);
				LOG_DISPLAY(InitializationLog, "Actor Marker built")
			}
		}
		else
		{
			LOG_WARNING(InitializationLog, "Could not create MarkerWidget! This shouldn't happen !")
			return nullptr;
		}
	}

	LOG_DISPLAY(InitializationLog,"Building Actor Marker Widget")
	UActorMarkerWidget* MarkerWidget = CreateWidget<UActorMarkerWidget>(GetWorld(), ActorMarkerTemplate);

	if (MarkerWidget != nullptr)
	{
		MarkerWidget->SetActorImage(MarkerImage);
		MarkerWidget->SetSize(FVector2D(50.f, 50.f));	
		MarkerWidget->SetActor(Actor);
		MarkerWidget->SetMiniMapInterface(MainUI->MiniMap);
		MarkerWidget->SetIsMonster(IsMonster);
		MainUI->MiniMap->AddActorMarker(MarkerWidget);
		MarkerWidget->RegisterActorMarkerWidget();
		LOG_DISPLAY(InitializationLog,"Actor Marker built")
		return MarkerWidget;
	}
	else
	{
		LOG_WARNING(InitializationLog, "Could not create MarkerWidget! This shouldn't happen !")
		return nullptr;
	}


}

void UGameInstanceManager::ShowUIEntryMessageInformation()
{
	if (PlayMode == EPlayMode::PM_HOPHOP)
	{
		return;
	}

	FPlayModeInformation Mode = GetPlayModeInformation(PlayMode);

	if (Mode.Levels.Num() <= CurrentProgress.CurrentLevel)
	{
		LOG_WARNING(InitializationLog, "Setup is wrong. CurrentLevel Value exceeds")
		return;
	}

	if (SaveGame == nullptr)
	{
		LOG_WARNING(InitializationLog, "SaveGame was null ! This shouldn't happen !")
		return;
	}
	else
	{
		if (SaveGame->HasPartAchieved(PlayMode, CurrentProgress.CurrentLevel, CurrentProgress.CurrentDungeon, CurrentProgress.CurrentDifficulty, CurrentProgress.CurrentPart - 1))
		{
			LOG_WARNING(InitializationLog, "Already achieved ! Not showing PartInformation")
			return;
		}
	}

	if (Mode.Levels[CurrentProgress.CurrentLevel].DungeonsInLevel.Num() <= CurrentProgress.CurrentDungeon)
	{
		LOG_WARNING(InitializationLog, "Setup is wrong. Current Dungeon Value exceeds")
		return;
	}
	if (Mode.Levels[CurrentProgress.CurrentLevel].DungeonsInLevel[CurrentProgress.CurrentDungeon].Difficulties.Num() <= CurrentProgress.CurrentDifficulty)
	{
		LOG_WARNING(InitializationLog, "Setup is wrong. Current Difficulty Value exceeds")
		return;
	}

	FPartDifficultyInformation Info;
	
	if (GetGameState()->GetCurrentPart() == 0)
	{
		if (Mode.Levels[CurrentProgress.CurrentLevel].DungeonsInLevel[CurrentProgress.CurrentDungeon].Difficulties[CurrentProgress.CurrentDifficulty].DungeonParts.Num() <= GetGameState()->GetCurrentPart())
		{
			LOG_WARNING(InitializationLog, "Setup is wrong. Current Part Value exceeds")
				UE_LOG(LogTemp, Warning, TEXT("%d"), GetGameState()->GetCurrentPart());
			return;
		}

		Info = Mode.Levels[CurrentProgress.CurrentLevel]
			.DungeonsInLevel[CurrentProgress.CurrentDungeon]
			.Difficulties[CurrentProgress.CurrentDifficulty]
			.DungeonParts[GetGameState()->GetCurrentPart()]
			.PartsWithDifficulty[0];
	}
	else
	{
		if (Mode.Levels[CurrentProgress.CurrentLevel].DungeonsInLevel[CurrentProgress.CurrentDungeon].Difficulties[CurrentProgress.CurrentDifficulty].DungeonParts.Num() <= GetGameState()->GetCurrentPart() - 1)
		{
			LOG_WARNING(InitializationLog, "Setup is wrong. Current Part Value exceeds")
				UE_LOG(LogTemp, Warning, TEXT("%d"), GetGameState()->GetCurrentPart() - 1);
			return;
		}

		Info = Mode.Levels[CurrentProgress.CurrentLevel]
											  .DungeonsInLevel[CurrentProgress.CurrentDungeon]
											  .Difficulties[CurrentProgress.CurrentDifficulty]
											  .DungeonParts[GetGameState()->GetCurrentPart() -1]
											  .PartsWithDifficulty[0];
	}	

	MainUI->ShowPartInformation(Info.PartTitleMessage, Info.PartEntryMessage, 1);
}

void UGameInstanceManager::ShowUITutorialInformation(FText Title, FText Message, int32 index)
{
	MainUI->ShowPartInformation(Title, Message, index);
	MainUI->Information->PlayTutorialAnimation(index);
}

void UGameInstanceManager::ShowNewCredentials()
{
	if (MainUI != nullptr)
	{
		for(int i = 0; i < PlayModeInformation.Num(); i++)
		{
			auto ModeInformation = PlayModeInformation[i];
			if (ModeInformation.PlayMode == (PlayMode == EPlayMode::PM_HOPHOP ? TempPlayMode : PlayMode))
			{
				if(CurrentProgress.CurrentPart == 0)
				{
					CurrentProgress.SetCurrentPart(EPartInformation::EPI_LEVEL1);
				}
				TArray<FSecretCredential> Credentials = PlayModeInformation[i].Levels[CurrentProgress.CurrentLevel].DungeonsInLevel[CurrentProgress.CurrentDungeon].Difficulties[CurrentProgress.CurrentDifficulty].DungeonParts[CurrentProgress.CurrentPart - 1].PartsWithDifficulty[0].SecretCredentials;
				if (Credentials.Num() > 1)
				{
					MainUI->SecretCredentials->SetCredentials(Credentials[0].Character, Credentials[0].TextColorCode, Credentials[0].OutlineColorCode, Credentials[1].Character, Credentials[1].TextColorCode, Credentials[1].OutlineColorCode);
				}
				else if (Credentials.Num() > 0)
				{
					MainUI->SecretCredentials->SetCredentials(Credentials[0].Character, Credentials[0].TextColorCode, Credentials[0].OutlineColorCode, "", FLinearColor::White, FLinearColor::White);
				}
				MainUI->SecretCredentials->PlayWidgetAnimation(0,true);
				MainUI->StartAnimation(8);
				break;
			}
		}
	}
	else
	{
		LOG_WARNING(RuntimeExecutionLog, "Could not show credentials, because MainUI was null ! This shouldn't happen !")
	}
}

TArray<FSecretCredential> UGameInstanceManager::GetCredentials() const
{
	TArray<FSecretCredential> Return = TArray<FSecretCredential>();

	int SolveCount = 0;

	if (SaveGame == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Could not find SaveGame!")
		return Return;
	}
	else
	{	
		switch (CurrentProgress.CurrentPart)
		{
		case EPartInformation::EPI_NONE:
		case EPartInformation::EPI_LEVEL1:
			SolveCount  = SaveGame->GetCredentialSolveCount((PlayMode == EPlayMode::PM_HOPHOP) ? TempPlayMode : PlayMode, CurrentProgress.CurrentLevel, CurrentProgress.CurrentDungeon, 0, CurrentProgress.CurrentDifficulty);
			break;
		case EPartInformation::EPI_LEVEL2:
			SolveCount  = SaveGame->GetCredentialSolveCount((PlayMode == EPlayMode::PM_HOPHOP) ? TempPlayMode : PlayMode, CurrentProgress.CurrentLevel, CurrentProgress.CurrentDungeon, 1, CurrentProgress.CurrentDifficulty);
			break;
		case EPartInformation::EPI_LEVEL3:
			SolveCount  = SaveGame->GetCredentialSolveCount((PlayMode == EPlayMode::PM_HOPHOP) ? TempPlayMode : PlayMode, CurrentProgress.CurrentLevel, CurrentProgress.CurrentDungeon, 2, CurrentProgress.CurrentDifficulty);
			break;
		default:
			break;
		}
	}

	if (SolveCount > 0)
	{
		for (int i = 0; i < PlayModeInformation.Num(); i++)
		{
			auto ModeInformation = PlayModeInformation[i];
			if (ModeInformation.PlayMode == (PlayMode == EPlayMode::PM_HOPHOP ? TempPlayMode : PlayMode))
			{
				for (int32 j = 0; j < SolveCount; j++)
				{				
					TArray<FSecretCredential> Credentials = TArray<FSecretCredential>();
					switch (CurrentProgress.CurrentPart)
					{
					case EPartInformation::EPI_NONE:
					case EPartInformation::EPI_LEVEL1:
						Credentials = PlayModeInformation[i].Levels[CurrentProgress.CurrentLevel].DungeonsInLevel[CurrentProgress.CurrentDungeon].Difficulties[j].DungeonParts[0].PartsWithDifficulty[0].SecretCredentials;
						break;
					case EPartInformation::EPI_LEVEL2:
						Credentials = PlayModeInformation[i].Levels[CurrentProgress.CurrentLevel].DungeonsInLevel[CurrentProgress.CurrentDungeon].Difficulties[j].DungeonParts[1].PartsWithDifficulty[0].SecretCredentials;
						break;
					case EPartInformation::EPI_LEVEL3:
						Credentials = PlayModeInformation[i].Levels[CurrentProgress.CurrentLevel].DungeonsInLevel[CurrentProgress.CurrentDungeon].Difficulties[j].DungeonParts[2].PartsWithDifficulty[0].SecretCredentials;
						break;
					default:
						break;
					}
						
					
					if (Credentials.Num() > 0)
					{
						for (auto Credential : Credentials)
						{
							Return.Add(Credential);
						}
					}
				}
				break;
			}
		}
		LOG_DISPLAY(RuntimeExecutionLog, "Solved Credentials added!")
	}
	else
	{
		LOG_DISPLAY(RuntimeExecutionLog, "No Levels solved yet!")
	}

	return Return;
}

void UGameInstanceManager::SetUIActive(bool IsActive)
{
	if (MainUI == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Could not find MainUI. This shouldn't happen.")
	}
	else
	{
		if (IsActive)
		{
			MainUI->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			MainUI->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void UGameInstanceManager::SetMapActive(bool IsActive)
{
	if (MainUI == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Could not find MainUI. This shouldn't happen.")
	}
	else
	{
		if (IsActive)
		{
			MainUI->MiniMap->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			MainUI->MiniMap->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}


