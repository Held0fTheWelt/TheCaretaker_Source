/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "GameMode_Menu.h"

#include "Components/MenuAudio/MenuAudioComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Interfaces/GameInstance/GameInstanceUIInterface.h"
#include "GameInstance/GameInstanceInterface.h"
#include "Log/GlobalLog.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameState.h"
#include "Interfaces/GameInstance/GameInstanceAccessoryInterface.h"
#include "Interfaces/GameInstance/GameInstanceMenuInterface.h"
#include "Interfaces/GameInstance/GameInstanceUIInterface.h"
#include "Interfaces/GameInstance/GameInstanceInterface.h"
#include "Structs/CurrentProgress/CurrentProgress.h"
AGameMode_Menu::AGameMode_Menu()
{
	if (MenuAudioComponent == nullptr)
		MenuAudioComponent = CreateDefaultSubobject<UMenuAudioComponent>(FName("MenuAudioComponent"));

	MenuAudioComponent->SetupAttachment(RootComponent);
}
#pragma endregion

#pragma region Begin Play
void AGameMode_Menu::BeginPlay()
{
	Super::BeginPlay();

	if (GetInstanceInterfaces() == false) return;

	if (GameInstance != nullptr)
	{
		GameInstance->ResetTestModes();
		GameInstance->RecalculateCurrentProgress();
		LOG_DISPLAY(InitializationLog, "Print Current Progress Values")
		GameInstance->ResetPlayModes();
		GameInstance->UpdateGameStateValues();
		GameInstance->TestExtraLevelsSetup();

	}
	else
	{
		LOG_WARNING(InitializationLog, "Could not find GameInstance ! This shouldn't happen !")
	}

	if (SetupUI() == false) return;

	GameInstance->TestCompetitionMode();

	SetupContinueButton();	
}
#pragma endregion

#pragma region Setup UI
bool AGameMode_Menu::SetupUI()
{
	if (GameInstanceUI != nullptr)
	{
		if (GameInstanceUI->TestSetup() == false)
		{
			LOG_WARNING(InitializationLog, "Setup of GameInstance incomplete ! Cannot run Game!");
			return false;
		}

		GameInstanceUI->CallUI(EUIEnum::UI_MENU);

		return true;
	}
	else
	{
		LOG_ERROR(InitializationLog, "GameMode could not cast GameInstance! This shouldn't happen ! Is it set in the project settings ??");
	}
	return false;
}
void AGameMode_Menu::SetupContinueButton()
{
	FCurrentProgress CurrentProgress = GameInstanceAccessory->GetCurrentProgress();
	GameInstanceAccessory->SetCurrentLevelName(GameInstanceAccessory->GetLevelName(CurrentProgress.CurrentLevel, CurrentProgress.CurrentDungeon));
}
bool AGameMode_Menu::GetInstanceInterfaces()
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

	return Okay;
}
#pragma endregion
