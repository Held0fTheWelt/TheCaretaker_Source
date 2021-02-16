/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#include "Widgets/Inventory/InventoryWidget.h"

#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Log/GlobalLog.h"

UInventoryWidget::UInventoryWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bFirst = true;
	
	ResourceLeft = ESpawnPointType::SPT_NONE;
	ResourceRight = ESpawnPointType::SPT_NONE;
}

void UInventoryWidget::ShowInventory(bool Show)
{
	ShowResourceLeft(Show);
	ShowResourceRight(Show);
}
void UInventoryWidget::ShowResourceLeft(bool Show)
{
	if (Show)
	{
		if (ResourceLeft != ESpawnPointType::SPT_NONE)
		{
			LeftHand->SetVisibility(ESlateVisibility::Visible);
			BackgroundLeft->SetVisibility(ESlateVisibility::Visible);
			FrameLeft->SetVisibility(ESlateVisibility::Visible);

			if (ResourceLeft == ESpawnPointType::SPT_VOLUME)
			{
				AmountLeft->SetVisibility(ESlateVisibility::Visible);
			}
		}
	}
	else
	{
		LeftHand->SetVisibility(ESlateVisibility::Hidden);
		BackgroundLeft->SetVisibility(ESlateVisibility::Hidden);
		FrameLeft->SetVisibility(ESlateVisibility::Hidden);

		AmountLeft->SetVisibility(ESlateVisibility::Hidden);
	}
}
void UInventoryWidget::ShowResourceRight(bool Show)
{
	if (Show)
	{
		if (ResourceRight != ESpawnPointType::SPT_NONE)
		{
			RightHand->SetVisibility(ESlateVisibility::Visible);
			BackgroundRight->SetVisibility(ESlateVisibility::Visible);
			FrameRight->SetVisibility(ESlateVisibility::Visible);
		
			if (ResourceRight == ESpawnPointType::SPT_VOLUME)
			{
				AmountRight->SetVisibility(ESlateVisibility::Visible);
			}
		}
	}
	else
	{
		RightHand->SetVisibility(ESlateVisibility::Hidden);
		BackgroundRight->SetVisibility(ESlateVisibility::Hidden);
		FrameRight->SetVisibility(ESlateVisibility::Hidden);
		
		AmountRight->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UInventoryWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	InitializeIconDefinitions();

	AmountLeft->SetText(FText::FromString(FString::FromInt(0)));
	AmountRight->SetText(FText::FromString(FString::FromInt(0)));

	ShowInventory(false);
}

void UInventoryWidget::InitializeIconDefinitions()
{
	TArray<FName> RowNames = IconDefinition->GetRowNames();
	for (auto Name : RowNames)
	{
		static const FString ContextString(Name.ToString());
		FInventoryIconDefinition* InventoryIconDefinition = IconDefinition->FindRow<FInventoryIconDefinition>(Name, ContextString, true);
		Icons.Add(InventoryIconDefinition);
	}
}

void UInventoryWidget::AddResource(TEnumAsByte<ESpawnPointType> ResourceType, int8 Amount)
{
	uint8 AmountValue = Amount;
	if (bFirst == true)
	{
		if (ResourceType != ESpawnPointType::SPT_VOLUME)
		{
			AmountValue = 0;
		}
		for (auto IconDef : Icons)
		{
			if (IconDef->TypeOfImage == ResourceType)
			{
				LeftHand->SetBrushFromTexture(IconDef->InventoryImages[0], false);
			}
		}
		ResourceLeft = ResourceType;
		AmountLeft->SetText(FText::FromString(FString::FromInt(AmountValue)));
		bFirst = false;
	}
	else
	{
		if (ResourceType != ESpawnPointType::SPT_VOLUME)
		{
			AmountValue = 0;
		}
		for (auto IconDef : Icons)
		{
			if (IconDef->TypeOfImage == ResourceType)
			{
				RightHand->SetBrushFromTexture(IconDef->InventoryImages[0], false);
			}
		}
		ResourceRight = ResourceType;
		AmountRight->SetText(FText::FromString(FString::FromInt(AmountValue)));
	}

	ShowInventory(true);
}

void UInventoryWidget::RemoveResource(TEnumAsByte<ESpawnPointType> ResourceType, int8 Amount)
{
	LOG_DISPLAY(RuntimeExecutionLog,"Start removing ")
	if (ResourceRight == ResourceType)
	{
		LOG_DISPLAY(RuntimeExecutionLog,"Start removing right hand")
		ShowResourceRight(false);
		if (ResourceType == ESpawnPointType::SPT_VOLUME)
		{
			if (ResourceLeft == ResourceType && Amount > 5)
			{
				AmountRight->SetText(FText::FromString(FString::FromInt(Amount - 5)));
				ShowResourceLeft(true);
				ShowResourceRight(true);
				return;
			}
			if (Amount > 0 && ResourceLeft != ESpawnPointType::SPT_VOLUME)
			{
				AmountRight->SetText(FText::FromString(FString::FromInt(Amount)));
				ShowResourceLeft(true);
				ShowResourceRight(true);
				return;
			/*	ResourceLeft = ResourceRight;
				for (auto IconDef : Icons)
				{
					if (IconDef->TypeOfImage == ResourceRight)
					{
						LeftHand->SetBrushFromTexture(IconDef->InventoryImages[0], false);
					}
				}
				ResourceRight = ESpawnPointType::SPT_NONE;

				AmountLeft->SetText(FText::FromString(FString::FromInt(Amount)));*/
			}
		}
		ResourceRight = ESpawnPointType::SPT_NONE;
	}
	else if (ResourceLeft == ResourceType)
	{
		LOG_DISPLAY(RuntimeExecutionLog,"Start removing right hand")
					
		ShowResourceLeft(false);
		if (ResourceType == ESpawnPointType::SPT_VOLUME)
		{
			if (Amount > 0)
			{
				AmountLeft->SetText(FText::FromString(FString::FromInt(Amount)));
				ShowResourceLeft(true);
				return;
			}
		}
		if (ResourceRight != ESpawnPointType::SPT_NONE)
		{
			ResourceLeft = ResourceRight;
			for (auto IconDef : Icons)
			{
				if (IconDef->TypeOfImage == ResourceRight)
				{
					LeftHand->SetBrushFromTexture(IconDef->InventoryImages[0], false);
				}
			}
			ResourceRight = ESpawnPointType::SPT_NONE;

			AmountLeft->SetText(FText::FromString(FString::FromInt(Amount)));			

			ShowResourceLeft(true);
			ShowResourceRight(false);
			return;
		}
		ResourceLeft = ESpawnPointType::SPT_NONE;			
		bFirst = true;
		//LOG_DISPLAY(RuntimeExecutionLog,"Stated end of line")
	}
	else
	{
		LOG_DISPLAY(RuntimeExecutionLog, "Resource to drop is not known in the inventory. This shouldn't happen !")
	}

}

void UInventoryWidget::UpdateFood(int8 Amount)
{
	if (ResourceRight == ESpawnPointType::SPT_VOLUME)
	{
		if (Amount > 0)
		{
			AmountRight->SetText(FText::FromString(FString::FromInt(Amount)));
			ShowResourceRight(true);
			return;
		}
	}
	else
	{
		if (Amount > 0)
		{
			AmountLeft->SetText(FText::FromString(FString::FromInt(Amount)));
			ShowResourceLeft(true);
			return;
		}
	}
}
