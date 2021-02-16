/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "Widgets/Ingame/IngameMenuUserWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Engine/World.h"
#include "Engine/GameInstance.h"
#include "GameInstance/GameInstanceManager.h"
#include "Kismet/GameplayStatics.h"
#include "Log/GlobalLog.h"
#include "Widgets/BackButton/BackButtonUserWidget.h"


void UIngameMenuUserWidget::VictoryButton(bool IsVictory)
{
	if (IsVictory)
	{
		Continue->SetVisibility(ESlateVisibility::Hidden);
		ContinueText->SetVisibility(ESlateVisibility::Hidden);
		RestartText->Text = VictoryMessage;
		if (Restart->OnClicked.IsBound())
		{
			Restart->OnClicked.Clear();
		}
		Restart->OnClicked.AddDynamic(this, &UIngameMenuUserWidget::ContinueToNextPart);
		Options->SetVisibility(ESlateVisibility::Hidden);
		OptionsText->SetVisibility(ESlateVisibility::Hidden);
		if (Back->OnClicked.IsBound())
		{
			Back->OnClicked.RemoveDynamic(this, &UIngameMenuUserWidget::BackToMenu);
			Back->OnClicked.AddDynamic(this, &UIngameMenuUserWidget::BackToMenuAfterVictory);
		}
	}
	else
	{
		Continue->SetVisibility(ESlateVisibility::Hidden);
		ContinueText->SetVisibility(ESlateVisibility::Hidden);
		RestartText->Text = RestartMessage;
		if (Restart->OnClicked.IsBound())
		{
			Restart->OnClicked.Clear();
		}
		Restart->OnClicked.AddDynamic(this, &UIngameMenuUserWidget::RestartLevel);
	}
}

void UIngameMenuUserWidget::IngameMenuCall()
{
	Continue->SetVisibility(ESlateVisibility::Visible);
	ContinueText->Text = ContinueMessage;
}

void UIngameMenuUserWidget::HideInformationCall()
{
	HideInformationCallBlueprint();
}

void UIngameMenuUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!Restart->OnClicked.IsBound())
	{
		Restart->OnClicked.AddDynamic(this, &UIngameMenuUserWidget::RestartLevel);
	}
	if (!Options->OnClicked.IsBound())
	{
		Options->OnClicked.AddDynamic(this, &UIngameMenuUserWidget::ShowOptionsDialog);
	}
	if (!Continue->OnClicked.IsBound())
	{
		Continue->OnClicked.AddDynamic(this, &UIngameMenuUserWidget::ReturnToGame);
		Continue->OnClicked.AddDynamic(this, &UUserWidgetBase::ReturnToParent);
	}
	if (Back->OnClicked.IsBound())
	{
		Back->OnClicked.RemoveDynamic(this, &UUserWidgetBase::ReturnToParent);
		Back->OnClicked.AddDynamic(this, &UIngameMenuUserWidget::BackToMenu);
	}
	else
	{
		Back->OnClicked.AddDynamic(this, &UIngameMenuUserWidget::BackToMenu);
	}
}

void UIngameMenuUserWidget::BackToMenu()
{
	if (GameInstanceAccessor == nullptr || GameInstanceRouter == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Could not Load Level, because GameInstance was null! This shouldn't happen !")
	}
	else
	{
		GameInstanceAccessor->SetCurrentLevelName(GameInstanceAccessor->GetMenuLevelName());
		
		GameInstanceRouter->ShowLoadLevel();
	}	

	CloseIngameMenu();
}

void UIngameMenuUserWidget::BackToMenuAfterVictory()
{
	if (GameInstanceAccessor == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Could not Show Options Dialog. Game Instance was null. This shouldn't happen !")
	}
	else
	{
		GameInstanceAccessor->CountBeforeBackToMenu();
	}
	BackToMenu();
}

void UIngameMenuUserWidget::ReturnToGame()
{
	CloseIngameMenu();
}

void UIngameMenuUserWidget::ShowOptionsDialog()
{
	if (GameInstanceUI == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog,"Could not Show Options Dialog. Game Instance was null. This shouldn't happen !")
	}
	else
	{
		GameInstanceUI->OpenDialog(EMenuDialog::MD_OPTIONS, this);
	}
}

void UIngameMenuUserWidget::RestartLevel()
{
	if (GameInstanceRouter == nullptr)
	{
		CloseIngameMenu();
		LOG_WARNING(RuntimeExecutionLog, "Could not Restart Level. Game Instance was null. This shouldn't happen !")
	}
	else
	{
		GameInstanceRouter->RestartLevel();
		CloseIngameMenu();
	}
}

void UIngameMenuUserWidget::ContinueToNextPart()
{
	LOG_WARNING(RuntimeExecutionLog, "Here insert New Progress Types")

	///*if (GameInstanceRouter == nullptr)
	//{
	//	CloseIngameMenu();
	//	LOG_WARNING(RuntimeExecutionLog, "Could not Restart Level. Game Instance was null. This shouldn't happen !")
	//}
	//else
	//{
	//	GameInstanceRouter->ContinueForced();
	//	CloseIngameMenu();*/
	//}
}

void UIngameMenuUserWidget::ContinueToNextDifficulty()
{
}

void UIngameMenuUserWidget::CloseIngameMenu()
{		
	if (GameInstanceRouter == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Could not cast Instance to GameInstance! This shouldn't happen !")
	}
	else
	{
		GameInstanceRouter->CloseIngameMenu();
	}
	
	Destruct();
}
