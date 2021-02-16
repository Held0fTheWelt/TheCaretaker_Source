/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "Widgets/Start/StartMenuWidget.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Interfaces/GameInstance/GameInstanceAccessoryInterface.h"
#include "Interfaces/GameInstance/GameInstanceMenuInterface.h"
#include "Interfaces/GameInstance/GameInstanceUIInterface.h"
#include "GameInstance/GameInstanceManager.h"
#include "GameModes/Menu/GameMode_Menu.h"
#include "Log/GlobalLog.h"
#include "Components/Button.h"
#include "Structs/Achievement/Achievement.h"
#include "UObject/Class.h"
#include "UObject/UObjectGlobals.h"
#include "Misc/Char.h"
UStartMenuWidget::UStartMenuWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	CredentialsForPlaymodeButton = FString("fZn");

	PlayModes.Add(FText::FromString("Classic+"));
	PlayModes.Add(FText::FromString("Default+"));
}

void UStartMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (GameInstanceAccessor == nullptr)
	{
		LOG_WARNING(InitializationLog, "Creation of Start Menu failed, because Game Instance could not be cast! Does it implement IGameInstanceMenuInterface ?");
		return;
	}

	UGameInstanceManager* GameInstance = Cast<UGameInstanceManager>(GetGameInstance());

	FAchievementLoadIdentifier Achievements = GameInstance->GetLoadIdentifier();

	//if (Achievements.MaxLevelAchieved > 0 || Achievements.MaxDungeonAchieved > 0 || Achievements.MaxPartAchievedInDungeon > EPartInformation::EPI_LEVEL1)
	if (GameInstance->GetCurrentLevelPoints() > 0)
	{
		SetAlternateTextToNewGameButton();
	}

	bShowPlayModeButton = GameInstance->TestCredentials(CredentialsForPlaymodeButton);

	if (!NewGame->OnClicked.IsBound()) NewGame->OnClicked.AddDynamic(this, &UStartMenuWidget::CallNewGame);
	if (!Tutorial->OnClicked.IsBound()) Tutorial->OnClicked.AddDynamic(this, &UStartMenuWidget::CallTutorial);
	if (!LoadGame->OnClicked.IsBound()) LoadGame->OnClicked.AddDynamic(this, &UStartMenuWidget::CallLevelSelector);
	if (!Options->OnClicked.IsBound()) Options->OnClicked.AddDynamic(this, &UStartMenuWidget::CallOptionsDialog);
	if (!Quit->OnClicked.IsBound()) Quit->OnClicked.AddDynamic(this, &UStartMenuWidget::CallQuitGame);
	/*if (bShowPlayModeButton)
	{
		PlayMode->SetVisibility(ESlateVisibility::Visible);
		if (!PlayMode->OnClicked.IsBound()) PlayMode->OnClicked.AddDynamic(this, &UStartMenuWidget::CallSwitchGameMode);
		if (GameInstanceAccessor->GetPlayMode() == EPlayMode::PM_CLASSIC)
		{
			PlayModeText->SetText(PlayModes[0]);
			CurrentPlayModeIndex = 0;
		}
		else if (GameInstanceAccessor->GetPlayMode() == EPlayMode::PM_DEFAULT)
		{
			PlayModeText->SetText(PlayModes[1]);
			CurrentPlayModeIndex = 1;
		}
	}
	else
	{
		PlayMode->SetVisibility(ESlateVisibility::Collapsed);
		if (!PlayMode->OnClicked.IsBound()) PlayMode->OnClicked.RemoveAll(this);
	}

	if (GameInstance->GetCurrentLevelPoints() < 9)
	{
		Credentials->SetVisibility(ESlateVisibility::Collapsed);
		if (Credentials->OnClicked.IsBound()) Credentials->OnClicked.RemoveAll(this);
	}
	else
	{
		Credentials->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		if (!Credentials->OnClicked.IsBound()) Credentials->OnClicked.AddDynamic(this, &UStartMenuWidget::CallCredentialViewTable);

	}*/

	bShow = true;	
}

void UStartMenuWidget::CallTutorial()
{
	if (GameInstanceAccessor == nullptr || GameInstanceRouter == nullptr ||!bShow)
	{
		LOG_WARNING(RuntimeLog, "Call Tutorial failed, because Game Instance was null! This shouldn't happen !");
	}
	else
	{
		GameInstanceAccessor->SetCurrentLevelName(GameInstanceAccessor->GetTutorialLevelName());
		GameInstanceRouter->ShowLoadLevel();
	}
}

void UStartMenuWidget::CallLevelSelector()
{
	if (GameInstanceUI == nullptr || !bShow)
	{
		LOG_WARNING(RuntimeLog, "Could not open Level Selector, because Game Instance was null! This shouldn't happen !");
	}
	else
	{
		GameInstanceUI->OpenDialog(EMenuDialog::MS_LEVELSELECT, this);
	}
}

void UStartMenuWidget::ShowWidget(bool Show)
{
	Super::ShowWidget(Show);

	if (bShow)
	{
		NewGame->SetVisibility(ESlateVisibility::Visible);
		if (!NewGame->OnClicked.IsBound()) NewGame->OnClicked.AddDynamic(this, &UStartMenuWidget::CallNewGame);
		Quit->SetVisibility(ESlateVisibility::Visible);
		if (!Quit->OnClicked.IsBound()) Quit->OnClicked.AddDynamic(this, &UStartMenuWidget::CallQuitGame);
		Options->SetVisibility(ESlateVisibility::Visible);
		if (!Options->OnClicked.IsBound()) Options->OnClicked.AddDynamic(this, &UStartMenuWidget::CallOptionsDialog);
		if (bShowPlayModeButton)
		{
			PlayMode->SetVisibility(ESlateVisibility::Visible);
			if (!PlayMode->OnClicked.IsBound()) PlayMode->OnClicked.AddDynamic(this, &UStartMenuWidget::CallSwitchGameMode);
			if (GameInstanceAccessor->GetPlayMode() == EPlayMode::PM_CLASSIC)
			{
				PlayModeText->SetText(PlayModes[0]);
				CurrentPlayModeIndex = 0;
			}
			else if (GameInstanceAccessor->GetPlayMode() == EPlayMode::PM_DEFAULT)
			{
				PlayModeText->SetText(PlayModes[1]);
				CurrentPlayModeIndex = 1;
			}
		}
	}
	else
	{
		NewGame->SetVisibility(ESlateVisibility::Hidden);
		if (NewGame->OnClicked.IsBound()) NewGame->OnClicked.RemoveAll(this);
		Quit->SetVisibility(ESlateVisibility::Hidden);
		if (Quit->OnClicked.IsBound()) Quit->OnClicked.RemoveAll(this);
		Options->SetVisibility(ESlateVisibility::Hidden);
		if (Options->OnClicked.IsBound()) Options->OnClicked.RemoveAll(this);
		PlayMode->SetVisibility(ESlateVisibility::Collapsed);
		if (!PlayMode->OnClicked.IsBound()) PlayMode->OnClicked.RemoveAll(this);
	}
}

void UStartMenuWidget::SetAlternateTextToNewGameButton()
{
	Txt_NewGame->SetText(ContinueText);
}

void UStartMenuWidget::CallNewGame()
{
	if (GameInstanceRouter == nullptr || !bShow)
	{
		LOG_WARNING(RuntimeLog, "Start Game failed, because Game Instance could not be cast! Does it implement IGameInstanceMenuInterface ?");
	}
	else
	{
		GameInstanceRouter->NewGame();
	}
}

void UStartMenuWidget::CallOptionsDialog()
{
	if (GameInstanceUI == nullptr || !bShow)
	{
		LOG_WARNING(RuntimeLog, "Options Dialog could not be shown, because Game Instance could not be cast! Does it implement IGameInstanceMenuInterface ?");
	}
	else
	{
		GameInstanceUI->OpenDialog(EMenuDialog::MD_OPTIONS, this);
	}
}

void UStartMenuWidget::CallQuitGame()
{
	if (GameInstanceRouter == nullptr || !bShow)
	{
		LOG_WARNING(ShutdownLog, "Quit Game failed, because Game Instance could not be cast! Does it implement IGameInstanceMenuInterface ?");
	}
	else
	{
		GameInstanceRouter->SaveGameData();
		
		AGameMode_Menu* GameMode = GameInstanceRouter->GetMenuGameMode();
		if (GameMode != nullptr)
		{
			GameMode->PlayQuitSequence();
		}
		else
		{
			LOG_WARNING(RuntimeExecutionLog,"Could not play Quit Sequence, because GameMode was null ! This shouldn't happen !")
			GameInstanceRouter->Quit();
		}
	}
}

void UStartMenuWidget::CallSwitchGameMode()
{

	CurrentPlayModeIndex++;

	if (CurrentPlayModeIndex >= PlayModes.Num())
	{
		CurrentPlayModeIndex = 0;	
	}

	PlayModeText->SetText(PlayModes[CurrentPlayModeIndex]);

	if (GameInstanceRouter == nullptr)
	{
		LOG_WARNING(ShutdownLog, "Cannot switch GameMode failed, because Game Instance could not be cast! Does it implement IGameInstanceMenuInterface ?");
	}
	else
	{
		switch (CurrentPlayModeIndex)
		{
		case 0:
			GameInstanceRouter->Classic();
			break;
		case 1:
			GameInstanceRouter->Default();
			break;
		default:
			break;
		}
	}
}

void UStartMenuWidget::CallCredentialViewTable()
{
	if (GameInstanceUI == nullptr || !bShow)
	{
		LOG_WARNING(RuntimeLog, "Could not open Credential View Table, because Game Instance was null! This shouldn't happen !");
	}
	else
	{
		GameInstanceUI->OpenDialog(EMenuDialog::MS_CREDENTIALS, this);
	}
}
