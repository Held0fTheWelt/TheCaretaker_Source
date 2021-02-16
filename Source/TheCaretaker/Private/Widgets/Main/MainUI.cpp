/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "Widgets/Main/MainUI.h"

#include "TimerManager.h"

#include "Widgets/Pickup/PickupUserWidget.h"
#include "Components/TextBlock.h"
#include "Components/PanelSlot.h"
#include "Components/CanvasPanelSlot.h"
#include "Engine/World.h"
#include "Log/GlobalLog.h"
#include "Widgets/Generic/ScreenNotification/ScreenNotification.h"

UMainUI::UMainUI(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}


void UMainUI::ShowPartInformation(FText Title, FText ScreenNotification, int32 index)
{
	ScreenNotifications->SetTextNotification(ScreenNotification);
	ScreenNotifications->SetVisibility(ESlateVisibility::Visible);
	LevelTitle->SetText(Title);
	LevelTitle->SetVisibility(ESlateVisibility::Visible);

	StartAnimation(index);
}

void UMainUI::ShowPickupWidget(bool Show)
{
	if (Show)
	{
		PickupWidget->SetRenderOpacity(1.f);
	}
	else
	{
		PickupWidget->SetRenderOpacity(0.f);
	}
}
