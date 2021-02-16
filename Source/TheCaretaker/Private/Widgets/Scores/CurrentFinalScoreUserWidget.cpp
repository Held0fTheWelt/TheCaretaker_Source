// /* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "CurrentFinalScoreUserWidget.h"

#include "TimerManager.h"

#include "Components/TextBlock.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Log/GlobalLog.h"
#include "Sound/SoundBase.h"

UCurrentFinalScoreUserWidget::UCurrentFinalScoreUserWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	Count = 5;
}

void UCurrentFinalScoreUserWidget::PlaySound()
{
	TimerFunction();
}

void UCurrentFinalScoreUserWidget::Reset()
{
	Count = 5;
}

void UCurrentFinalScoreUserWidget::TimerFunction()
{
	FireSound();
	if (Count >= 0)
	{
		GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
		TimerHandle_ScoreSound.Invalidate();
		if (TimerHandle_ScoreSound.IsValid())
		{
			TimerHandle_ScoreSound = FTimerHandle();
		}

		GetWorld()->GetTimerManager().SetTimer(TimerHandle_ScoreSound, this, &UCurrentFinalScoreUserWidget::TimerFunction, 1.f, false);
	}
}

void UCurrentFinalScoreUserWidget::FireSound()
{
	if (Count == 0)
	{
		if (FinalScoreSound == nullptr)
		{
			LOG_WARNING(RuntimeExecutionLog, "FinalScoreSound was null ! Is it set up in the blueprint ?")
				return;
		}

		UGameplayStatics::PlaySound2D(GetWorld(), FinalScoreSound);
	}
	if (Count == 1)
	{
		if (PickupBonusSound == nullptr)
		{
			LOG_WARNING(RuntimeExecutionLog, "FinalScoreSound was null ! Is it set up in the blueprint ?")
				return;
		}

		UGameplayStatics::PlaySound2D(GetWorld(), PickupBonusSound);
	}
	if (Count > 1)
	{
		if (ScoreAdditionSound == nullptr)
		{
			LOG_WARNING(RuntimeExecutionLog, "ScoreAdditionSound was null ! Is it set up in the blueprint ?")
				return;
		}

		UGameplayStatics::PlaySound2D(GetWorld(), ScoreAdditionSound);
	}

	Count--;
}

void UCurrentFinalScoreUserWidget::SetScoreInGame(int32 ScoreInGame)
{
	ScoreInGameText->SetText(FText::FromString(FString::FromInt(ScoreInGame)));
}

void UCurrentFinalScoreUserWidget::SetMeatBonus(int32 MeatBonus)
{
	MeatBonusText->SetText(FText::FromString(FString::FromInt(MeatBonus)));
}

void UCurrentFinalScoreUserWidget::SetHungerBonus(int32 HungerBonus)
{
	HungerBonusText->SetText(FText::FromString(FString::FromInt(HungerBonus)));
}

void UCurrentFinalScoreUserWidget::SetFinishBonus(int32 FinishBonus)
{
	FinishBonusText->SetText(FText::FromString(FString::FromInt(FinishBonus)));
}

void UCurrentFinalScoreUserWidget::SetPickupBonus(int32 PickupBonus)
{
	PickupBonusText->SetText(FText::FromString(FString::FromInt(PickupBonus)));
}

void UCurrentFinalScoreUserWidget::SetFinalScore(int32 FinalScore)
{
	FinalScoreText->SetText(FText::FromString(FString::FromInt(FinalScore)));
}
