/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "Widgets/TrapTimer/TrapTimerUserWidget.h"

#include "Components/ProgressBar.h"

UTrapTimerUserWidget::UTrapTimerUserWidget()
{
}

void UTrapTimerUserWidget::SetTrapTimerValue(float Value)
{
	ProgressBar->SetPercent(Value);
	SetTrapTimerColor(Value);
}

void UTrapTimerUserWidget::SetTrapTimerColor(float Value)
{
	// 0 - 1R 0G
	// 0,5 = 1R 1G
	// 1 = 0R 1G

	float temp = Value / 2;

	FLinearColor NewColor = FLinearColor::White;
	if (Value < .5f)
	{
		NewColor = FLinearColor(1, Value * 2, 0, 1);
	}
	else
	{
		NewColor = FLinearColor(1 - (Value - .5f) * 2,1, 0, 1);
	}

	ProgressBar->SetFillColorAndOpacity(NewColor);
}

void UTrapTimerUserWidget::SetGamePaused(bool SetGamePaused)
{
}

bool UTrapTimerUserWidget::IsPaused() const
{
	return false;
}

