/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "States/Game/CaretakerGameState.h"

#include "TimerManager.h"

#include "Actors/Fireplace/FireplaceActor.h"
#include "Actors/WinCondition/WinConditionActor.h"
#include "Engine/World.h"
#include "Characters/DungeonMaster/DungeonMasterCharacter.h"
#include "Engine/GameInstance.h"
#include "GameFramework/PlayerState.h"
#include "GameInstance/GameInstanceManager.h"
#include "GameModes/Game/GameMode_Game.h"
#include "Interfaces/WinCondition/WinConditionVolumeInterface.h"
#include "Interfaces/GameMode/Menu/MenuGameModeInterface.h"
#include "Interfaces/GameInstance/GameInstanceUIInterface.h"
#include "Interfaces/GameInstance/GameInstanceAccessoryInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Log/GlobalLog.h"
#include "States/Player/CaretakerPlayerState.h"
#include "Structs/Score/ScoreDefinition.h"
#include "Structs/Score/ScoreMultiplier.h"
#include "Structs/Score/TimeToScore.h"
#include "Widgets/Generic/ProgressBar/GenericProgressBarWidget.h"
#include "Widgets/Information/InformationWidget.h"
#include "Widgets/Inventory/InventoryWidget.h"
#include "Widgets/Main/MainUI.h"
#include "Widgets/Scores/CurrentScoreUserWidget.h"

#pragma region Constructor
ACaretakerGameState::ACaretakerGameState()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = .5f;
	TimeToShowCredentials = 5.f;

	CurrentScore = 0;

	ScoreCalculator = FScoreCalculator();

	bScoreSetupOkay = true;
	TimeToShowScore = 6.f;

	Clock = nullptr;
	
	CurrentScoreWidget = nullptr;
}
#pragma endregion



void ACaretakerGameState::UpdateCurrentHighScore()
{
	UGameInstance* Instance = UGameplayStatics::GetGameInstance(GetWorld());

	IGameInstanceAccessoryInterface* Accessory = Cast<IGameInstanceAccessoryInterface>(Instance);

	if (Accessory == nullptr)
	{
		LOG_WARNING(InitializationLog, "Accessory was null ! This shouldn't happen !")
	}
	else
	{
		Accessory->UpdateHighScoreWidget(CurrentLevel, CurrentDungeon, CurrentDifficulty, CurrentPart);
	}
}

#pragma region BeginPlay
void ACaretakerGameState::BeginPlay()
{
	Super::BeginPlay();

	UGameInstance* Instance = UGameplayStatics::GetGameInstance(GetWorld());

	if (Instance == nullptr)
	{
		LOG_WARNING(InitializationLog, "Could not get GameInstance ! This shouldn't happen !");
	}
	else
	{
		UGameInstanceManager* GameInstance = Cast<UGameInstanceManager>(Instance);
		if (GameInstance == nullptr)
		{
			LOG_WARNING(InitializationLog, "Could not cast GameInstance to MenuGameInstance! This shouldn't happen !");
		}
		else
		{
			CurrentLevel = GameInstance->GetCurrentLevel();
			CurrentDungeon = GameInstance->GetCurrentDungeon();
			CurrentDifficulty = GameInstance->GetCurrentDifficulty();
			CurrentPart = GameInstance->GetCurrentPart();
		}		
	}

	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UWinConditionVolumeInterface::StaticClass(), Actors);

	for (auto Actor : Actors)
	{
		AWinConditionActor* WinCondition = Cast<AWinConditionActor>(Actor);

		if (WinCondition != nullptr)
		{
			auto funName = GET_FUNCTION_NAME_CHECKED(ACaretakerGameState, WinConditionEntered);
			WinCondition->WinConditionUpdate.BindUFunction(this, funName);
		}
		else
		{

		}
	}

	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);


	FTimerHandle TimerHandle_SmallStartDelay;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_SmallStartDelay, this, &ACaretakerGameState::UpdateCurrentHighScore, .5f, false);
}
#pragma endregion

#pragma region Handle BeginPlay
void ACaretakerGameState::HandleBeginPlay()
{
	Super::HandleBeginPlay();

	UGameInstance* Instance = UGameplayStatics::GetGameInstance(GetWorld());

	if (Instance == nullptr)
	{
		LOG_WARNING(InitializationLog, "GameState could not get GameInstance ! This shouldn't happen !")
	}
	else
	{
		UGameInstanceManager* GameInstance = Cast<UGameInstanceManager>(Instance);
		if (GameInstance == nullptr)
		{
			LOG_WARNING(InitializationLog, "GameInstance could not be cast to MenuGameInstance! This shouldn't happen ! Is it set in the projects Game Settings ?")
		}
		else
		{
			CurrentLevel = GameInstance->GetCurrentLevel();
			CurrentDungeon = GameInstance->GetCurrentDungeon();
			CurrentDifficulty = GameInstance->GetCurrentDifficulty();
			CurrentPart = GameInstance->GetCurrentPart();
			if (GameInstanceInterface == nullptr)
			{
				GameInstanceInterface = Cast<IGameInstanceAccessoryInterface>(GameInstance);
			}

			if (GameInstanceInterface == nullptr)
			{
				LOG_WARNING(InitializationLog,"GameInstance could not be cast to interface")
			}
			else
			{
				if (GameInstanceInterface->GetPlayMode() == EPlayMode::PM_HOPHOP)
				{
					LOG_WARNING(InitializationLog,"HopHop Mode entering WinCondition")
					WinConditionEntered();
				}
			}
		}
	}

	AGameMode_Game* GameMode = Cast<AGameMode_Game>(UGameplayStatics::GetGameMode(GetWorld()));

	IMenuGameModeInterface* IsMenu = Cast<IMenuGameModeInterface>(UGameplayStatics::GetGameMode(GetWorld()));

	if (IsMenu != nullptr)
	{
		CurrentScore = 0;		
		return;
	}
	else
	{
		if (GameMode == nullptr)
		{
			LOG_WARNING(RuntimeLog, "Could not find GameMode ! This shouldn't happen !")
		}
		else
		{
			ClockInterface = GameMode->GetClock();

			CurrentScore = 0;
		}
	}
}
#pragma endregion

#pragma region Tick
void ACaretakerGameState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MostAngryMonster.Anger = 0;

	for (auto Monster : MonstersAnger)
	{
		if (Monster.Anger > MostAngryMonster.Anger + .0005)
		{
			MostAngryMonster.MonsterName = Monster.MonsterName;
			MostAngryMonster.Anger = Monster.Anger;
			Information->SetMostAngryMonster(FText::FromName(MostAngryMonster.MonsterName));
		}
		//UE_LOG(LogTemp, Warning, TEXT("Current Monster is %s with anger of %f"), *Monster.GetName(), Monster.Anger);
	}
	//MonstersAnger.Empty();
}
#pragma endregion

#pragma region Setup GameState
bool ACaretakerGameState::SetupGameState(UMainUI* UI)
{
	if (UI != nullptr)
	{
		MainUI = UI;
		ScreenNotifications = MainUI->ScreenNotifications;
		MiniMap = MainUI->MiniMap;
		Monsters = MainUI->Monsters;
		Information = MainUI->Information;
		Clock = MainUI->Clock;

		for (auto Player : PlayerArray)
		{			
			if (Player->IsPrimaryPlayer())
			{
				ACaretakerPlayerState* PS = Cast<ACaretakerPlayerState>(Player);
				if (PS != nullptr)
				{
					PS->SetupWidgets(MainUI->Inventory, MainUI->DebugInventory, MainUI->Information, MainUI->DebugInformation);
					PlayerState = PS;
				}
			}
		}		

		LOG_DISPLAY(InitializationLog, "GameState setup complete !");
		return true;
	}
	else
	{
		LOG_WARNING(InitializationLog, "Received Main UI of GameInstance was null! This shouldn't happen !");
		return false;
	}
}
#pragma endregion

#pragma region Win Condition Entered
void ACaretakerGameState::WinConditionEntered()
{
	LOG_DISPLAY(RuntimeExecutionLog, "WinCondition Volume entered ! Testing for game solution ...")
		
	IGameInstanceMenuInterface* Menu = Cast<IGameInstanceMenuInterface>(UGameplayStatics::GetGameInstance(GetWorld()));
	
	if (WinConditionMet())
	{	
		if (bScoreSetupOkay)
		{
			if (ClockInterface == nullptr)
			{
				LOG_WARNING(RuntimeExecutionLog, "ClockInterface was null ! This shouldn't happen !")
			}
			else
			{
				ScoreCalculator.SetFinishingTime(ClockInterface->GetCurrentTime());
			}
		}

		if (!Menu->HasPartAchieved(CurrentLevel, CurrentDungeon, CurrentDifficulty, CurrentPart - 1)
			&& CurrentDifficulty == 0
			&& CurrentLevel == 0
			&& CurrentDungeon == 0
			&& CurrentPart - 1 == 0
			)
		{
			Menu->CountAchievement(EAchievementType::AT_WINCONDITIONMET);
		}

		if (bShouldWaitForEndOfTime == true)
		{
			if (ClockInterface == nullptr)
			{
				LOG_WARNING(RuntimeExecutionLog, "ClockInterface was null ! This shouldn't happen !")
			}
			else
			{
				if (ClockInterface->IsTimeUp() == false)
				{
					bool HopHopMode = false;
					if (GameInstanceInterface != nullptr)
					{
						if (GameInstanceInterface->GetPlayMode() == EPlayMode::PM_HOPHOP)
						{
							HopHopMode = true;
						}
					}
					if (!HopHopMode)
					{
						LOG_DISPLAY(RuntimeExecutionLog, "Waiting for End of Time");
						return;
					}
				}
			}
		}

		Menu->HideUnwantedUIElementsOnFinish();
		//if (bShouldWaitForEndOfTime == false)
		//{
		//	FTimerHandle TimerHandle_ShortDelay;
		//	GetWorld()->GetTimerManager().SetTimer(TimerHandle_ShortDelay, this, &ACaretakerGameState::CountVictory, .5f, false);
		//}
		//else
		//{
			CountVictory();
		//}
		Menu->OpenIngameMenu(EIngameMenuCall::IMC_VICTORY);

		if (bScoreSetupOkay && GameInstanceInterface->GetPlayMode() != EPlayMode::PM_HOPHOP)
		{
			GetWorld()->GetTimerManager().SetTimer(TimerHandle_FinishDelay, this, &ACaretakerGameState::FinishLevel, 4.f, false);
		}
		else
		{
			GetWorld()->GetTimerManager().SetTimer(TimerHandle_FinishDelay, this, &ACaretakerGameState::SmallCredentialsDelay, 4.f, false);			
		}
	}
	else
	{
		if (ClockInterface == nullptr)
		{
			LOG_WARNING(RuntimeExecutionLog, "ClockInterface was null ! This shouldn't happen !")
		}
		else
		{
			if (ClockInterface->IsTimeUp() == true)
			{
				if (Menu == nullptr)
				{
					LOG_WARNING(RuntimeExecutionLog, "Couldn't find GameInstance on Level End while Time is Up, but not solved! This shouldn't happen !")
				}
				else
				{
					Menu->OpenIngameMenu(EIngameMenuCall::IMC_TIME);
					LOG_DISPLAY(RuntimeExecutionLog, "Time is up, but level not solved");
					return;
				}
			}
		}
	}
}

void ACaretakerGameState::SmallCredentialsDelay()
{
	IGameInstanceMenuInterface* Menu = Cast<IGameInstanceMenuInterface>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (Menu == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Couldn't find GameInstance ! This shouldn't happen !")
	}
	else
	{
		if (Menu->IsCaretakerOne())
		{
			LevelComplete();
			PerformLevelChange();
			return;
		}

		if (!bScoreSetupOkay)
		{
			Menu->HideWinInformation();
			GetWorld()->GetTimerManager().SetTimer(TimerHandle_ShowCredentials, this, &ACaretakerGameState::ShowNewCredentials, .1f, false, .3f);
		}
		else
		{
			ShowNewCredentials();
		}
	}
}

void ACaretakerGameState::FinishLevel()
{
	IGameInstanceMenuInterface* Menu = Cast<IGameInstanceMenuInterface>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (Menu == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Couldn't find GameInstance ! This shouldn't happen !")
	}
	else
	{
		Menu->HideWinInformation();

		if (!TimerHandle_ScoreDelay.IsValid())
			TimerHandle_ScoreDelay = FTimerHandle();

		Menu->HideUnwantedUIElementsOnFinish();
		IGameInstanceUIInterface* UIInterface = Cast<IGameInstanceUIInterface>(Menu);

		if (bScoreSetupOkay == true)
		{
			CurrentScoreWidget->ShowAddedScoreImplementation(4);
			if(UIInterface == nullptr)
			{
				LOG_WARNING(RuntimeExecutionLog,"Could not cast GameInstance to UI Manager. This shouldn't happen !")
			}
			else
			{
				UIInterface->SetScoreInGame(CurrentScore);
				UIInterface->SetMeatBonus(ScoreCalculator.GetMeatBonus());
				CurrentScore += ScoreCalculator.GetMeatBonus();
				TArray<float> HungerAverages = UIInterface->GetFinalMonsterHungerAverages();
				float HungerAverage = 0;
				for (auto Average : HungerAverages)
				{
					HungerAverage += Average;
				}
				
				//UE_LOG(LogTemp, Warning, TEXT("Hunger Average = %f"), HungerAverage / HungerAverages.Num());

				UIInterface->SetHungerBonus(ScoreCalculator.GetMonsterHungerBonus(HungerAverages.Num(), HungerAverage / HungerAverages.Num()));
				CurrentScore += ScoreCalculator.GetMonsterHungerBonus(1, HungerAverage / 1);
				UIInterface->SetFinishBonus(ScoreCalculator.GetFinishBonus());
				CurrentScore += ScoreCalculator.GetFinishBonus();
				UIInterface->SetPickupBonus(ScoreCalculator.CalculateExtraBonus());
				CurrentScore *= ScoreCalculator.CalculateExtraBonus();
				UIInterface->SetFinalScore(CurrentScore);
				UIInterface->ShowFinalScore();
			}
		}

		GetWorld()->GetTimerManager().SetTimer(TimerHandle_ScoreDelay, this, &ACaretakerGameState::HideFinalScore, TimeToShowScore, false);
	}
}
#pragma endregion
void ACaretakerGameState::ShowHighScore()
{
	IGameInstanceUIInterface* UI = Cast<IGameInstanceUIInterface>(UGameplayStatics::GetGameInstance(GetWorld()));
	IGameInstanceAccessoryInterface* Accessory = Cast<IGameInstanceAccessoryInterface>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (UI == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "MenuInstance was null ! This shouldn't happen !")
	}
	else
	{
		UI->CallShowHighscore();
		if (!Accessory->IsNewHighScoreAchieved(CurrentLevel, CurrentDungeon, CurrentDifficulty, CurrentPart - 1, CurrentScore, ScoreCalculator.FinishTime))
		{
			// Show HigScore
			GetWorld()->GetTimerManager().SetTimer(TimerHandle_ShowCredentials, this, &ACaretakerGameState::HideHighScore, .1f, false, .25f);
		}
	}
}

void ACaretakerGameState::HideHighScore()
{
	IGameInstanceUIInterface* UI = Cast<IGameInstanceUIInterface>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (UI == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "MenuInstance was null ! This shouldn't happen !")
	}
	else
	{
		UI->CallHideHighscore();
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_ShowCredentials, this, &ACaretakerGameState::SmallCredentialsDelay, .1f, false, 5.5f);
	}
}

void ACaretakerGameState::StopCredentialTimer()
{
	if (GetWorldTimerManager().IsTimerActive(TimerHandle_ShowCredentials))
	{
		GetWorldTimerManager().ClearTimer(TimerHandle_ShowCredentials);
	}
}

#pragma region Monster Report
void ACaretakerGameState::MonsterReport(FMonsterAnger MonsterAnger)
{
	bool bIsNewMonster = true;
	for(int i = 0; i < MonstersAnger.Num(); i++)
	{
		if (MonstersAnger[i].MonsterName == MonsterAnger.MonsterName)
		{
			MonstersAnger[i].SetAnger(MonsterAnger.Anger);
			bIsNewMonster = false;
		//	UE_LOG(LogTemp, Warning, TEXT("Monster stating is %s with anger of %f"), *Monster.GetName(), Monster.Anger);

			break;
		}
	}

	if (bIsNewMonster)
	{
		MonstersAnger.Add(MonsterAnger);
	}
}
#pragma endregion

#pragma region Register DungeonMaster
void ACaretakerGameState::RegisterDungeonMaster(IDungeonMasterInterface * Interface)
{
	ADungeonMasterCharacter* Master = Cast<ADungeonMasterCharacter>(Interface);
	if (Master == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "DungeonMaster was null ! This shouldn't happen !")
		return;
	}

	Master->CharacterDead.BindUFunction(this, "PlayerKilledByMaster");
}
#pragma endregion

#pragma region Perform Level Change
void ACaretakerGameState::PerformLevelChange()
{
	IGameInstanceMenuInterface* Menu = Cast<IGameInstanceMenuInterface>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (Menu == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Couldn't find GameInstance ! This shouldn't happen !")
	}
	else
	{
		Menu->PerformLevelChange();
	}
}
#pragma endregion

#pragma region Player Killed By Master
void ACaretakerGameState::PlayerKilledByMaster()
{
	LOG_DISPLAY(RuntimeExecutionLog,"Player Killed")

	IGameInstanceMenuInterface* Menu = Cast<IGameInstanceMenuInterface>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (Menu == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Couldn't find GameInstance ! This shouldn't happen !")
	}
	else
	{
		Menu->OpenIngameMenu(EIngameMenuCall::IMC_DEATHBYMONSTER);
	}
}
#pragma endregion

void ACaretakerGameState::ReadInScoreSetup()
{
	ReadInScoreDefinition();
	ReadInScoreMultiplier();
	ReadInTimesToScore();
	ReadInMaxTime();
	ReadInDifficulty();
	ResetCalculationScoreValues();
	//ShowScoreCalculatorValues();
}

void ACaretakerGameState::ReadInScoreDefinition()
{
	static const FString ContextString(TEXT("ScoreDefinition"));

	TArray<FName> RowNames = ScoreDefinition->GetRowNames();
	for (int32 i = 0; i < RowNames.Num(); i++)
	{
		FScoreDefinition* Score = ScoreDefinition->FindRow<FScoreDefinition>(RowNames[i], ContextString, true);
		
		switch (Score->ScoreType)
		{
		case EScoreType::ST_GARBAGE:
			ScoreCalculator.ScorePerGarbage = Score->ScoreValue;
			break;
		case EScoreType::ST_CHEST:
			ScoreCalculator.ScorePerChest = Score->ScoreValue;
			break;
		case EScoreType::ST_TRAP:
			ScoreCalculator.ScorePerTrap= Score->ScoreValue;
			break;
		case EScoreType::ST_MEAT:
			ScoreCalculator.ScorePerMeat = Score->ScoreValue;
		case EScoreType::ST_HUNGER:
			ScoreCalculator.MonsterHungerScore= Score->ScoreValue;
			break;
		case EScoreType::ST_FINISH:
			ScoreCalculator.FinishingScore = Score->ScoreValue;
			break;
		default:
			break;
		}
	}
}

void ACaretakerGameState::ReadInScoreMultiplier()
{
	static const FString ContextString(TEXT("ScoreMultiplier"));

	TArray<FName> RowNames = ScoreMultiplier->GetRowNames();
	for (int32 i = 0; i < RowNames.Num(); i++)
	{
		FScoreMultiplier* Multiplier = ScoreMultiplier->FindRow<FScoreMultiplier>(RowNames[i], ContextString, true);

		switch (Multiplier->ScoreModifierType)
		{
		case EScoreModifierType::SMT_PICKUP_BONUS:
			ScoreCalculator.PickupMultiplicator = Multiplier->ModifierValue;
			break;
		case EScoreModifierType::SMT_SPEED_BONUS:
			ScoreCalculator.SpeedMultiplicator = Multiplier->ModifierValue;
			break;
		case EScoreModifierType::SMT_TIME_BONUS:
			ScoreCalculator.TimeMultiplicator = Multiplier->ModifierValue;
			break;
		default:
			break;
		}
	}
}

void ACaretakerGameState::ReadInTimesToScore()
{
	static const FString ContextString(TEXT("TimeToScore"));

	TArray<FName> RowNames = TimeToScore->GetRowNames();
	for (int32 i = 0; i < RowNames.Num(); i++)
	{
		FTimeToScore* ScoreTime = TimeToScore->FindRow<FTimeToScore>(RowNames[i], ContextString, true);
		switch (ScoreTime->ScoreType)
		{
		case EScoreType::ST_GARBAGE:
			ScoreCalculator.TimeForScoreGarbage = ScoreTime->TimeToScore;
			break;
		case EScoreType::ST_CHEST:
			ScoreCalculator.TimeForScoreChest = ScoreTime->TimeToScore;
			break;
		case EScoreType::ST_TRAP:
			ScoreCalculator.TimeForScoreTrap = ScoreTime->TimeToScore;
			break;
		default:
			break;
		}
	}
}

void ACaretakerGameState::ReadInMaxTime()
{
	AGameMode_Game* GameMode = Cast<AGameMode_Game>(UGameplayStatics::GetGameMode(GetWorld()));

	if (GameMode == nullptr)
	{
		LOG_WARNING(RuntimeLog, "Could not find GameMode ! This shouldn't happen !")
	}
	else
	{
		ClockInterface = GameMode->GetClock();
	}

	if (ClockInterface == nullptr) {
		LOG_WARNING(InitializationLog, "ClockInterface was null ! This shouldn't happen !")
	}
	else
	{
		ScoreCalculator.MaxTime = ClockInterface->GetMaxTime();
	}
}

void ACaretakerGameState::ReadInDifficulty()
{

	if (GameInstanceInterface == nullptr)
	{
		LOG_WARNING(InitializationLog, "GameInstance could not be cast to interface")
	}
	else
	{
		int32 CurrentDifficultyBonus = GameInstanceInterface->GetCurrentDifficulty();
		CurrentDifficultyBonus++;
		if (GameInstanceInterface->GetPlayMode() == EPlayMode::PM_CLASSIC)
		{
			CurrentDifficultyBonus = CurrentDifficultyBonus * CurrentDifficultyBonus;

		}
		ScoreCalculator.CalculateDifficultyModifier(CurrentDifficultyBonus);
	}
}

void ACaretakerGameState::ShowScoreCalculatorValues()
{
	UE_LOG(LogTemp, Warning, TEXT("----------------------------"));
	UE_LOG(LogTemp, Warning, TEXT("SpeedMultiplicator: %f "), ScoreCalculator.SpeedMultiplicator);
	UE_LOG(LogTemp, Warning, TEXT("TimeMultiplicator: %f "), ScoreCalculator.TimeMultiplicator);
	UE_LOG(LogTemp, Warning, TEXT("PickupMultiplicator: %f "), ScoreCalculator.PickupMultiplicator);
	UE_LOG(LogTemp, Warning, TEXT("----------------------------"));
	UE_LOG(LogTemp, Warning, TEXT("Score per Garbage: %d "), ScoreCalculator.ScorePerGarbage);
	UE_LOG(LogTemp, Warning, TEXT("Score per Chest: %d "), ScoreCalculator.ScorePerChest);
	UE_LOG(LogTemp, Warning, TEXT("Score per Trap: %d "), ScoreCalculator.ScorePerTrap);
	UE_LOG(LogTemp, Warning, TEXT("Score per Meat: %d "), ScoreCalculator.ScorePerMeat);
	UE_LOG(LogTemp, Warning, TEXT("----------------------------"));
	UE_LOG(LogTemp, Warning, TEXT("Monster Hunger Score: %d "), ScoreCalculator.MonsterHungerScore);
	UE_LOG(LogTemp, Warning, TEXT("Finishing Score: %d "), ScoreCalculator.FinishingScore);
	UE_LOG(LogTemp, Warning, TEXT("----------------------------"));
	UE_LOG(LogTemp, Warning, TEXT("Time for score Garbage: %f "), ScoreCalculator.TimeForScoreGarbage);
	UE_LOG(LogTemp, Warning, TEXT("Time for score Chest: %f "), ScoreCalculator.TimeForScoreChest);
	UE_LOG(LogTemp, Warning, TEXT("Time for score Garbage: %f "), ScoreCalculator.TimeForScoreTrap);
	UE_LOG(LogTemp, Warning, TEXT("----------------------------"));
	UE_LOG(LogTemp, Warning, TEXT("Difficulty Bonus: %f "), ScoreCalculator.DifficultyBonus);
	UE_LOG(LogTemp, Warning, TEXT("----------------------------"));
	UE_LOG(LogTemp, Warning, TEXT("Max Time: %f "), ScoreCalculator.MaxTime);
	UE_LOG(LogTemp, Warning, TEXT("----------------------------"));
	UE_LOG(LogTemp, Warning, TEXT("Meat Count: %d "), ScoreCalculator.MeatCount);
	UE_LOG(LogTemp, Warning, TEXT("Pickup Count: %d "), ScoreCalculator.PickupCount);
	UE_LOG(LogTemp, Warning, TEXT("----------------------------"));
}

void ACaretakerGameState::ResetCalculationScoreValues()
{
	ScoreCalculator.MeatCount = 0;
	ScoreCalculator.PickupCount = 0;
	ScoreCalculator.FinishTime = 0.f;
	ScoreCalculator.BPickupActive = false;
}

FHighScoreEntry ACaretakerGameState::GetHighScoreEntry() const
{
	FHighScoreEntry ReturnValue = FHighScoreEntry();

	ReturnValue.Score = CurrentScore;
	ReturnValue.TimeSucceeded = ScoreCalculator.FinishTime;

	return ReturnValue;
}

void ACaretakerGameState::AddTrapObjective(EPartInformation Part)
{
	if (bScoreSetupOkay == false)
	{
		return;
	}
	ScoreCalculator.AddScoreTypeInformation(EScoreType::ST_TRAP, 0, Part);
}

void ACaretakerGameState::AddGoldObjective()
{
	if (bScoreSetupOkay == false)
	{
		return;
	}
	if (ClockInterface == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Cannot add Gold Objective for scoring, because ClockInterface is null ! This shouldn't happen !")
	}
	else
	{
		ScoreCalculator.AddScoreTypeInformation(EScoreType::ST_CHEST, ClockInterface->GetCurrentTime(), EPartInformation::EPI_NONE);
	}
}

void ACaretakerGameState::RemoveGoldObjective()
{
	if (bScoreSetupOkay == false)
	{
		return;
	}
	if (ClockInterface == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Cannot add Gold Objective for scoring, because ClockInterface is null ! This shouldn't happen !")
	}
	else
	{
		ScoreCalculator.RemoveGoldInformation();
	}
}

void ACaretakerGameState::AchievementSolved(EAchievementType AchievementType)
{
	if (bScoreSetupOkay == false)
	{
		return;
	}

	if (ClockInterface == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Could not count solved Trap, because clock was null ! This shouldn't happen !")
		return;
	}
	int32 ScoreAddition1 = 0;

	switch (AchievementType)
	{
	case AT_NONE:
		break;
	case AT_GARBAGE:
		ScoreAddition1 = ScoreCalculator.ReleaseScoreTypeInformation(EScoreType::ST_GARBAGE, ClockInterface->GetCurrentTime());
		CurrentScore += ScoreAddition1;
		CurrentScoreWidget->SetNewScore(CurrentScore, ScoreAddition1);		
		break;
	case AT_GOLD:
		ScoreAddition1 = ScoreCalculator.ReleaseScoreTypeInformation(EScoreType::ST_CHEST, ClockInterface->GetCurrentTime());
		CurrentScore += ScoreAddition1;
		CurrentScoreWidget->SetNewScore(CurrentScore, ScoreAddition1);
		break;
	case AT_MEAT:
		ScoreCalculator.IncrementMeatCount();
		break;
	case AT_TRAP:
		ScoreAddition1 = ScoreCalculator.ReleaseScoreTypeInformation(EScoreType::ST_TRAP, ClockInterface->GetCurrentTime());
		CurrentScore += ScoreAddition1;
		CurrentScoreWidget->SetNewScore(CurrentScore, ScoreAddition1);
		break;
	case AT_VICTORY:		
		break;
	case AT_DEATHBYSPIDER:
		break;
	case AT_DEATHBYMONSTER:
		break;
	case AT_DEATHBYTRAP:
		break;
	case AT_DEATHBYTIME:
		break;
	case AT_PROGRESS:
		break;
	case AT_DEATHBYPICKUP:
		break;
	default:
		break;
	}
}

void ACaretakerGameState::IncrementGarbageToCollect()
{
	GarbageCount++;
	GarbageMax++;
	Information->SetGarbageToCollect(FText::AsNumber(GarbageCount));
	Information->SetGarbageToCollectMax(FText::AsNumber(GarbageMax));
}

void ACaretakerGameState::IncrementTrapsToSolve()
{
	TrapCount++;
	TrapMax++;
	Information->SetTrapsToSolve(FText::AsNumber(TrapCount));
	Information->SetTrapsToSolveMax(FText::AsNumber(TrapMax));
}

void ACaretakerGameState::IncrementChestsToSolve()
{
	ChestCount++;
	ChestMax++;
	Information->SetChestsToSolve(FText::AsNumber(ChestCount));
	Information->SetChestsToSolveMax(FText::AsNumber(ChestMax));
}

void ACaretakerGameState::ContinueGamePlay()
{
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_ShowCredentials, this, &ACaretakerGameState::HideHighScore, .1f, false, .25f);
}
