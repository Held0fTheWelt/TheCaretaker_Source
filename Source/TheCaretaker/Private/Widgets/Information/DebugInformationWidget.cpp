/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "Widgets/Information/DebugInformationWidget.h"
#include "Components/TextBlock.h"

void UDebugInformationWidget::SetMostAngryMonster(FText Notification)
{
	TxtMonsters->SetText(Notification);
}

void UDebugInformationWidget::ClearTextMonstersNotification()
{
	TxtMonsters->SetText(FText::FromString(""));
}