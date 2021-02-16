/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "States/Game/CaretakerGameState.h"

#include "TimerManager.h"

#include "Actors/Fireplace/FireplaceActor.h"
#include "Actors/WinCondition/WinConditionActor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerState.h"
#include "Engine/GameInstance.h"
#include "Characters/DungeonMaster/DungeonMasterCharacter.h"
#include "GameInstance/GameInstanceManager.h"
#include "Interfaces/WinCondition/WinConditionVolumeInterface.h"
#include "Log/GlobalLog.h"
#include "Kismet/GameplayStatics.h"
#include "States/Player/CaretakerPlayerState.h"
#include "Widgets/Generic/ProgressBar/GenericProgressBarWidget.h"
#include "Widgets/Information/InformationWidget.h"
#include "Widgets/Inventory/InventoryWidget.h"
#include "Widgets/Main/MainUI.h"

void ACaretakerGameState::CalculateScoreAddition(EScoreType  ScoreToAdd)
{

}

#pragma region Set Garbage To Collect
void ACaretakerGameState::SetGarbageToCollect(int8 NewGarbageCount)
{
	if (Information == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Inventory was null in GameState! Cannot set new NewGarbageCount!");
		return;
	}

	if (NewGarbageCount < 0)
	{
		LOG_WARNING(RuntimeExecutionLog, "NewGarbageCount mustn't be less 0!");
		return;
	}

	GarbageCount = NewGarbageCount;
	GarbageMax = GarbageCount;

	Information->SetGarbageToCollect(FText::AsNumber(GarbageCount));
	Information->SetGarbageToCollectMax(FText::AsNumber(GarbageMax));
}
#pragma endregion

#pragma region Set Traps to Solve
void ACaretakerGameState::SetTrapsToSolve(int8 NewTrapCount)
{
	if (Information == nullptr)
	{
		LOG_WARNING(InitializationLog, "Inventory was null in GameState! Cannot set new NewTrapCount!");
		return;
	}

	if (NewTrapCount < 0)
	{
		LOG_WARNING(InitializationLog, "NewTrapCount mustn't be less 0!");
		return;
	}

	TrapCount = NewTrapCount;
	TrapMax = TrapCount;

	Information->SetTrapsToSolve(FText::AsNumber(TrapCount));
	Information->SetTrapsToSolveMax(FText::AsNumber(TrapMax));
}
#pragma endregion

#pragma region Set Chests to Solve
void ACaretakerGameState::SetChestsToSolve(int8 NewChestCount)
{
	if (Information == nullptr)
	{
		LOG_WARNING(InitializationLog, "Inventory was null in GameState! Cannot set new NewChestCount!");
		return;
	}

	if (NewChestCount < 0)
	{
		LOG_WARNING(InitializationLog, "NewChestCount mustn't be less 0!");
		return;
	}

	ChestCount = NewChestCount;
	ChestMax = ChestCount;

	Information->SetChestsToSolve(FText::AsNumber(ChestCount));
	Information->SetChestsToSolveMax(FText::AsNumber(ChestMax));
}
#pragma endregion

void ACaretakerGameState::GoldCollected()
{
	if (ClockInterface == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Could not count garbage, because ClockInterface was null ! This shouldn't happen !")
	}
	else
	{
		ScoreCalculator.AddScoreTypeInformation(EScoreType::ST_CHEST, ClockInterface->GetCurrentTime(), EPartInformation::EPI_NONE);
	}
}

void ACaretakerGameState::GarbageCollected(TEnumAsByte<EPartInformation> Part)
{
	if (ClockInterface == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog,"Could not count garbage, because ClockInterface was null ! This shouldn't happen !")
	}
	else
	{
		ScoreCalculator.AddScoreTypeInformation(EScoreType::ST_GARBAGE, ClockInterface->GetCurrentTime(), Part);
	}
}

#pragma region Count Down Traps
void ACaretakerGameState::CountDownTraps()
{
	
	if (TrapCount > 0)
	{
		TrapCount--;
		Information->SetTrapsToSolve(FText::AsNumber(TrapCount));
		if (bScoreSetupOkay)
		{
			AchievementSolved(EAchievementType::AT_TRAP);
		}
	}
	else {
		LOG_WARNING(RuntimeExecutionLog, "There couldn't be any trap left to count down! This call should not happen!");
	}
}
#pragma endregion

#pragma region Count Down Garbage
void ACaretakerGameState::CountDownGarbage(AFireplaceActor* Fireplace)
{
	if (PlayerState != nullptr)
	{
		if (!PlayerState->HasGarbage())
			return;

		PlayerState->RemoveGarbage();

		Fireplace->AddResourceEvent_Implementation();
	}
	else
	{
		for (auto State : PlayerArray)
		{
			if (State->IsPrimaryPlayer())
			{
				ACaretakerPlayerState* PS = Cast<ACaretakerPlayerState>(State);
				if (PS != nullptr)
				{
					PlayerState = PS;
				}
			}
		}
		LOG_WARNING(RuntimeExecutionLog, "Could not access PlayerState while counting down garbage!");
		return;
	}


	if (GarbageCount > 0)
	{
		GarbageCount--;
		Information->SetGarbageToCollect(FText::AsNumber(GarbageCount));
		if (bScoreSetupOkay)
		{
			AchievementSolved(EAchievementType::AT_GARBAGE);
		}
		if (GarbageCount == 0)
		{
			FTimerHandle TimerHandle;
			FTimerDelegate Delegate;
			Delegate.BindLambda([=] {
				WinConditionEntered();;
				});
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, Delegate, .75f, false);			
		}
	}
	else {
		LOG_WARNING(RuntimeExecutionLog, "There couldn't be any garbage left to count down! This call should not happen!");
	}
}
#pragma endregion

#pragma region Monster Is Angry
void ACaretakerGameState::MonsterIsAngry()
{
}
#pragma endregion

#pragma region Monster Not Angry Anymore
void ACaretakerGameState::MonsterNotAngryAnymore()
{
}
#pragma endregion

#pragma region Count Down Chests
void ACaretakerGameState::CountDownChests(TEnumAsByte<EPartInformation> Part)
{
	if (ChestCount > 0)
	{
		ChestCount--;
		Information->SetChestsToSolve(FText::AsNumber(ChestCount));
		if (bScoreSetupOkay)
		{
			ScoreCalculator.SetPartOfChest(Part);
			AchievementSolved(EAchievementType::AT_GOLD);
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("There couldn't be any trap left to count down! This call should not happen!"));
	}
}
#pragma endregion
