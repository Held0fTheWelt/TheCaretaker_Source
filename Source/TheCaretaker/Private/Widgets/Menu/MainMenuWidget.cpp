/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "Widgets/Menu/MainMenuWidget.h"
#include "Components/MultiLineEditableTextBox.h"

void UMainMenuWidget::NativeConstruct()
{


	Super::NativeConstruct();
}

void UMainMenuWidget::SetPart2(bool IsPart2)
{
	bIsPart2 = IsPart2;
}

void UMainMenuWidget::SetNewlyAchieved()
{
	if (!bIsNewlyAchieved)
	{
		bIsPart2 = true;
		bPlayNewAchieved = true;
		bIsNewlyAchieved = true;
	}
}

void UMainMenuWidget::HideElementsForAchievementMessage()
{
	StopAnimationPlaying();
}

void UMainMenuWidget::UpdateUI()
{
}
