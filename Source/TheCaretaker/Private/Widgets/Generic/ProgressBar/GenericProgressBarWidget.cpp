// @Yves Tanas 2020


#include "Widgets/Generic/ProgressBar/GenericProgressBarWidget.h"

#include "Components/ProgressBar.h"

void UGenericProgressBarWidget::SetProgressBarVisibility(bool Show)
{
	if (Show)
		SetVisibility(ESlateVisibility::Visible);
	else
		SetVisibility(ESlateVisibility::Hidden);
}

void UGenericProgressBarWidget::ResetProgressBar()
{
	ProgressBar->SetPercent(0);
	SetProgressBarVisibility(false);
}

void UGenericProgressBarWidget::SetProgressBarPercentage(float Percentage)
{
	SetProgressBarVisibility(true);
	ProgressBar->SetPercent(Percentage);
}
