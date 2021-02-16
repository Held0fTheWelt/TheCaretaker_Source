/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "GameMode_Game.h"

#include "Actors/Monsters/MonsterFeedingVolumeActor.h"
#include "Components/Clock/ClockComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameInstance/GameInstanceUIInterface.h"
#include "GameInstance/GameInstanceInterface.h"
#include "Interfaces/Chests/ChestInterface.h"
#include "Interfaces/GameInstance/GameInstanceMenuInterface.h"
#include "Interfaces/Game/GameFunctionsInterface.h"
#include "Interfaces/Garbage/GarbageInterface.h"
#include "Interfaces/Monsters/Feeding/MonsterFeedingInterface.h"
#include "Interfaces/Traps/TrapInterface.h"
#include "Interfaces/GameState/GameStateInterface.h"
#include "Log/GlobalLog.h"
#include "Kismet/GameplayStatics.h"
#include "States/Game/CaretakerGameState.h"
#include "Widgets/Main/MainUI.h"


#pragma region Setup UI
bool AGameMode_Game::SetupUI()
{
	if (GameInstanceUI != nullptr)
	{
		if (GameInstanceUI->TestSetup() == false)
		{
			LOG_WARNING(InitializationLog, "Setup of GameInstance incomplete ! Cannot run Game!");
			return false;
		}

		GameInstanceUI->CallUI(EUIEnum::UI_GAME);

		if (GameStateInterface == nullptr)
		{
			return false;
		}
		else
		{
			UMainUI* MainUI = GameInstance->GetGameUI();
			ClockComponent->SetTimeWidget(MainUI->Clock);
			return GameStateInterface->SetupGameState(MainUI);
		}
	}
	else
	{
		LOG_WARNING(InitializationLog, "GameMode could not cast GameInstance! This shouldn't happen ! Is it set in the project settings ??");
	}
	return false;
}
#pragma endregion

#pragma region Set UI Information
void AGameMode_Game::SetupUIInformation()
{
	TArray<AActor*>InterfacesFound;

	// Pick only Actors with Interface, instead of iterating whole World:
	UGameplayStatics::GetAllActorsWithInterface(this, UGarbageInterface::StaticClass(), InterfacesFound);
	GameStateInterface->SetGarbageToCollect(InterfacesFound.Num());

	InterfacesFound.Empty();

	UGameplayStatics::GetAllActorsWithInterface(this, UChestInterface::StaticClass(), InterfacesFound);
	GameStateInterface->SetChestsToSolve(InterfacesFound.Num());

	InterfacesFound.Empty();

	UGameplayStatics::GetAllActorsWithInterface(this, UTrapInterface::StaticClass(), InterfacesFound);
	GameStateInterface->SetTrapsToSolve(InterfacesFound.Num());
}
#pragma endregion


void AGameMode_Game::ShowMessagesOnScreen()
{
	GameInstanceUI->ShowUIEntryMessageInformation();
	LOG_DISPLAY(InitializationLog, "Showing Messages on Start")
}





