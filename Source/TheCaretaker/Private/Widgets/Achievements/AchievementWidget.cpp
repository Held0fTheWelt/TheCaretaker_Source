/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "Widgets\Achievements\AchievementWidget.h"

#include "TimerManager.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Engine/World.h"

UAchievementWidget::UAchievementWidget()
{
	TimeToFade = 3;
	TimeToLive = 3;
}

void UAchievementWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ShowWidget(false);
}

void UAchievementWidget::SetAchievementInformation(UTexture2D* Image, int16 Amount, FText Title, FText Description, FText Date)
{
	if (Image != nullptr)
	{
		AchievementImage->SetBrushFromTexture(Image, false);
	}
	FString AmountString = FString::FromInt(Amount);
	AchievementAmount->SetText(FText::FromString(AmountString));
	AchievementTitle->SetText(Title);
	AchievementDescription->SetText(Description);
	AchievementDate->SetText(Date);

	SetElementVisibility(true, Amount > 0);
	ShowWidget(true);

	GetWorld()->GetTimerManager().SetTimer(TimerHandle_AchievementWidget, 1, false, TimeToFade);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_AchievementWidget, this, &UAchievementWidget::FadeInFinished, 1.0f, false, TimeToFade);
}

void UAchievementWidget::SetElementVisibility(bool Visible, bool ShowAmount)
{
	if (Visible)
	{
		BackgroundImage->SetVisibility(ESlateVisibility::Visible);
		AchievementImage->SetVisibility(ESlateVisibility::Visible);
		if (ShowAmount)
		{
			AchievementAmount->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			AchievementAmount->SetVisibility(ESlateVisibility::Hidden);
		}
		AchievementTitle->SetVisibility(ESlateVisibility::Visible);
		AchievementDescription->SetVisibility(ESlateVisibility::Visible);
		DateText->SetVisibility(ESlateVisibility::Visible);
		AchievementDate->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		BackgroundImage->SetVisibility(ESlateVisibility::Hidden);
		AchievementImage->SetVisibility(ESlateVisibility::Hidden);
		AchievementAmount->SetVisibility(ESlateVisibility::Hidden);
		AchievementTitle->SetVisibility(ESlateVisibility::Hidden);
		AchievementDescription->SetVisibility(ESlateVisibility::Hidden);
		DateText->SetVisibility(ESlateVisibility::Hidden);
		AchievementDate->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UAchievementWidget::FadeInFinished()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle_AchievementWidget);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_AchievementWidget, this, &UAchievementWidget::TextShownEnough, 1.0f, false, TimeToLive);

}

void UAchievementWidget::TextShownEnough()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle_AchievementWidget);
	ShowWidget(false);
}
