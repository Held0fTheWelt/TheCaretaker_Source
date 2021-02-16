/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#include "Widgets/Inventory/DebugInventoryWidget.h"

#include "Components/TextBlock.h"
void UDebugInventoryWidget::SetGoldAmount(FText GoldAmount)
{
	TxtCollectedGold->SetText(GoldAmount);
}

void UDebugInventoryWidget::SetMeatAmount(FText MeatAmount)
{
	TxtCollectedMeat->SetText(MeatAmount);
}

void UDebugInventoryWidget::SetGarbageAmount(FText GarbageAmount)
{
	TxtCollectedGarbage->SetText(GarbageAmount);
}

void UDebugInventoryWidget::ClearGold()
{
	TxtCollectedGold->SetText(FText::FromString(""));
}

void UDebugInventoryWidget::ClearMeat()
{
	TxtCollectedMeat->SetText(FText::FromString(""));
}

void UDebugInventoryWidget::ClearGarbage()
{
	TxtCollectedGarbage->SetText(FText::FromString(""));
}
