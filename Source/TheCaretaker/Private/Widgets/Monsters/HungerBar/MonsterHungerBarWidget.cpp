/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "Widgets/Monsters/HungerBar/MonsterHungerBarWidget.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "Components/PanelSlot.h"
#include "Components/ProgressBar.h"
#include "Components/OverlaySlot.h"
#include "Log/GlobalLog.h"
#include "Styling/SlateBrush.h"

UMonsterHungerBarWidget::UMonsterHungerBarWidget()
{
	MarginTop = 10.f;
	ProgressBarMultiplier = .0001f;
	MarginMultiplier = 500.f;
}

void UMonsterHungerBarWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	//UCanvasPanelSlot* CanvasSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(this);
	///*UPanelSlot* Slot = ProgressBar->Slot;

	//if (Slot == nullptr)
	//{
	//	LOG_WARNING(InitializationLog,"Could not get ProgressBar Panel Slot")
	//}
	//else
	//{
	//	UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(Slot);
	//*/	if (CanvasSlot == nullptr)
	//	{
	//		LOG_WARNING(InitializationLog,"Could not cast Panel Slot to Canvas Panel Slot")
	//	}
	//	else
	//	{
	//		MarginMultiplier = CanvasSlot->GetSize().X;
	//	}
	////}	
}

void UMonsterHungerBarWidget::SetMonsterImage(UTexture2D* Image)
{
	MonsterTexture = Image;
	MonsterImage->SetBrushFromTexture(Image);
}

void UMonsterHungerBarWidget::SetProgressBarVisibility(bool Show)
{
	Super::SetProgressBarVisibility(Show);

}

void UMonsterHungerBarWidget::ResetProgressBar()
{
	Super::ResetProgressBar();

	FMargin Margin;
	
	UOverlaySlot* OverlaySlot = Cast<UOverlaySlot>(MonsterImage->Slot);

	if (OverlaySlot == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Could not cast Image Slot to OverlaySlot! This shouldn't happen !")
			return;
	}
	OverlaySlot->SetPadding(Margin);	

	CurrentPosition = 0;
}

void UMonsterHungerBarWidget::SetProgressBarPercentage(float Percentage)
{
	Super::SetProgressBarPercentage(Percentage);

	CurrentPosition = Percentage;
}

void UMonsterHungerBarWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (bPaused)
	{
		return;
	}

	CurrentPosition += (ProgressBar->Percent * ProgressBarMultiplier * InDeltaTime);
	CurrentPosition = FMath::Clamp(CurrentPosition, 0.f, 1.f);

	FMargin Margin;
	Margin.Top = MarginTop;
	Margin.Left = MarginMultiplier * CurrentPosition;

	
	UOverlaySlot* OverlaySlot = Cast<UOverlaySlot>(MonsterImage->Slot);

	if (OverlaySlot == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Could not cast Image Slot to OverlaySlot! This shouldn't happen !")
		return;
	}
	OverlaySlot->SetPadding(Margin);
}

void UMonsterHungerBarWidget::SetGamePaused(bool SetGamePaused)
{
	bPaused = SetGamePaused;
}

bool UMonsterHungerBarWidget::IsPaused() const
{
	return bPaused;
}
