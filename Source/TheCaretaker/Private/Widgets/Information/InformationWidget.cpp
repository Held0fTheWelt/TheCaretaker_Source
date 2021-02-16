/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "Widgets/Information/InformationWidget.h"

#include "Components/TextBlock.h"
void UInformationWidget::SetGarbageToCollect(FText Notification)
{
	TxtGarbage->SetText(Notification);
}

void UInformationWidget::SetGarbageToCollectMax(FText Notification)
{
	TxtGarbageMax->SetText(Notification);
}

void UInformationWidget::ClearTextGarbageNotification()
{
	TxtGarbage->SetText(FText::FromString(""));
}

void UInformationWidget::SetChestsToSolve(FText Notification)
{
	TxtChests->SetText(Notification);
}

void UInformationWidget::SetChestsToSolveMax(FText Notification)
{
	TxtChestsMax->SetText(Notification);
}

void UInformationWidget::ClearTextChestsNotification()
{
	TxtChests->SetText(FText::FromString(""));
}

void UInformationWidget::SetTrapsToSolve(FText Notification)
{
	TxtTraps->SetText(Notification);
}

void UInformationWidget::SetTrapsToSolveMax(FText Notification)
{
	TxtTrapsMax->SetText(Notification);
}

void UInformationWidget::ClearTextTrapsNotification()
{
	TxtTraps->SetText(FText::FromString(""));
}

void UInformationWidget::SetMostAngryMonster(FText Notification)
{
}

void UInformationWidget::ClearTextMonstersNotification()
{
}


