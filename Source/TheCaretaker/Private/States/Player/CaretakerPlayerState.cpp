/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "States/Player/CaretakerPlayerState.h"

#include "Actors/Resource/ResourceActor.h"
#include "Engine/World.h"
#include "Interfaces/Collectables/CollectableInterface.h"
#include "Interfaces/Garbage/GarbageInterface.h"
#include "Interfaces/GameMode/Game/GameModeInterface.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Log/GlobalLog.h"
#include "States/Game/CaretakerGameState.h"
#include "Widgets/Information/DebugInformationWidget.h"
#include "Widgets/Information/InformationWidget.h"
#include "Widgets/Inventory/DebugInventoryWidget.h"
#include "Widgets/Inventory/InventoryWidget.h"

ACaretakerPlayerState::ACaretakerPlayerState()
{
	CollectedFood = 0;
	CollectedGold = 0;

	MaxGold = 10;
	MaxGarbage = 10;

	Zero = 0;

	InventoryLimit = 2;
	CurrentlyCollected = 0;

	LeftHandStatus = EResourceType::RT_NONE;
	RightHandStatus = EResourceType::RT_NONE;
}

void ACaretakerPlayerState::BeginPlay()
{
	Super::BeginPlay();

	GameStateInterface = Cast<IGameStateInterface>(UGameplayStatics::GetGameState(GetWorld()));
	if (GameStateInterface == nullptr)
	{
		LOG_WARNING(InitializationLog, "Could not Cast GameStateInterface ! This shouldn't happen !")
	}
	IGameModeInterface* GameModeInterface = Cast<IGameModeInterface>(UGameplayStatics::GetGameMode(GetWorld()));

	if (GameModeInterface == nullptr)
	{
		LOG_WARNING(InitializationLog, "Could not Cast GameModeInterface ! This shouldn't happen !")
	}
	else
	{
		GarbageSpawnInformation = GameModeInterface->GetGarbageSpawnInformation();
	}
}

const bool ACaretakerPlayerState::GetCurrentLimitStatus() const
{
	return CurrentlyCollected < InventoryLimit;
}

void ACaretakerPlayerState::AddGold(int8 GoldToAdd, class AResourceActor* Actor)
{
	if (CurrentlyCollected < InventoryLimit)
	{
		if (GameStateInterface == nullptr)
		{
			LOG_WARNING(InitializationLog, "GameStateInterface was null ! This shouldn't happen !")
		}
		else
		{
			if (GameStateInterface->GetCurrentChestCount() - CollectedGold == 0)
			{
				return;
			}
		}
		CollectedGold += GoldToAdd;
		CollectedGold = ClampValues(CollectedGold, MaxGold);
		if (CollectedGold == 1)
		{
			LeftHandStatus = EResourceType::RT_GOLD;
		}
		else if(CollectedGold == 2)
		{
			RightHandStatus = EResourceType::RT_GOLD;
		}
		Inventory->AddResource(ESpawnPointType::SPT_CHEST, 1);
		DebugInventory->SetGoldAmount(FText::AsNumber(CollectedGold));
		Actor->AddResourceEvent();
		GameStateInterface->AddGoldObjective();
		CurrentlyCollected++;
	}
	else if (CollectedGold == MaxGold)
	{
		CurrentlyCollected--;
		Inventory->RemoveResource(ESpawnPointType::SPT_CHEST, 1);
		DebugInventory->SetGoldAmount(FText::AsNumber(CollectedGold));
		Actor->AddResourceEvent();
		GameStateInterface->RemoveGoldObjective();
		CollectedGold--;
	}
}


void ACaretakerPlayerState::RemoveGold(int8 GoldToRemove)
{
	CollectedGold -= GoldToRemove;
	CollectedGold = ClampValues(CollectedGold, MaxGold);
	DebugInventory->SetGoldAmount(FText::AsNumber(CollectedGold));
	Inventory->RemoveResource(ESpawnPointType::SPT_CHEST, CollectedFood);
	CurrentlyCollected--;
}

void ACaretakerPlayerState::AddFood(int8 FoodToAdd, AResourceActor* Actor)
{
	if (CollectedFood > 0)
	{
		float Reminder;
		int32 Whole = UKismetMathLibrary::FMod(CollectedFood, FoodToAdd, Reminder);
		if (Reminder != 0)
		{	
			CollectedFood = (Whole + 1) * FoodToAdd;

			DebugInventory->SetMeatAmount(FText::AsNumber(CollectedFood));
			Inventory->UpdateFood(FoodToAdd);			
			return;
		}
	}

	if (CurrentlyCollected < InventoryLimit)
	{
		CollectedFood += FoodToAdd;
		if (CollectedFood == FoodToAdd)
		{
			LeftHandStatus = EResourceType::RT_MEAT;
		}
		else
		{
			RightHandStatus = EResourceType::RT_MEAT;
		}
		CollectedFood = ClampValues(CollectedFood, MaxFood);
		DebugInventory->SetMeatAmount(FText::AsNumber(CollectedFood));
		Inventory->AddResource(ESpawnPointType::SPT_VOLUME, FoodToAdd);
		Actor->AddResourceEvent();
		CurrentlyCollected++;
	}
	else if (CollectedFood == MaxFood)
	{
		CollectedFood -= FoodToAdd;
		CollectedFood = ClampValues(CollectedFood, MaxFood);
		Inventory->RemoveResource(ESpawnPointType::SPT_VOLUME, FoodToAdd);		
		DebugInventory->SetMeatAmount(FText::AsNumber(CollectedFood));
		Actor->AddResourceEvent();		
		CurrentlyCollected--;
	}
}

void ACaretakerPlayerState::RemoveFood(int8 FoodToRemove)
{
	CollectedFood -= FoodToRemove;
	CollectedFood = ClampValues(CollectedFood, MaxFood);
	DebugInventory->SetMeatAmount(FText::AsNumber(CollectedFood));
	Inventory->RemoveResource(ESpawnPointType::SPT_VOLUME, CollectedFood);
	CurrentlyCollected = UKismetMathLibrary::FCeil(float(CollectedFood) / 5.f);
	CurrentlyCollected += CollectedGarbage.Num();
	CurrentlyCollected += CollectedGold;
}

void ACaretakerPlayerState::DropLeft()
{
	LOG_WARNING(RuntimeExecutionLog, "Dropping Left Hand")

	if (LeftHandStatus != EResourceType::RT_NONE)
	{

		LeftHandStatus = RightHandStatus;
		LeftHandGarbage = RightHandGarbage;
		RightHandStatus = EResourceType::RT_NONE;
		RightHandGarbage = nullptr;
	}
}

void ACaretakerPlayerState::DropRight()
{
	LOG_WARNING(RuntimeExecutionLog, "Dropping Right Hand")

	if (RightHandStatus == EResourceType::RT_NONE)
	{
		DropLeft();
	}
	else
	{
		RightHandStatus = EResourceType::RT_NONE;
		RightHandGarbage = nullptr;
	}

}

void ACaretakerPlayerState::AddCollectableGarbage(ICollectableInterface* Garbage, class AResourceActor* Actor)
{
	if (CurrentlyCollected < InventoryLimit)
	{
		if (Garbage != nullptr)
		{
			CollectedGarbage.Add(Garbage->GetActor());
			DebugInventory->SetGarbageAmount(FText::AsNumber(CollectedGarbage.Num()));
			if (Actor != nullptr)
				Actor->AddResourceEvent();
			CurrentlyCollected++;


			IGarbageInterface* GarbageInterface = Cast<IGarbageInterface>(Garbage);
			if (GarbageInterface != nullptr)
			{
				if (CurrentlyCollected == 1)
				{
					LeftHandGarbage = GarbageSpawnInformation[GarbageInterface->GetSpawnInformationIndex()].GarbageBlueprint;
					LeftHandStatus = EResourceType::RT_GARBAGE;
				}
				else if (CurrentlyCollected == 2)
				{
					RightHandStatus = EResourceType::RT_GARBAGE;
					RightHandGarbage = GarbageSpawnInformation[GarbageInterface->GetSpawnInformationIndex()].GarbageBlueprint;
				}
			}
			else
			{
				LOG_WARNING(RuntimeExecutionLog, "Could not cast CollectableInterface to GarbageInterface.")
			}
		}
		else
		{
			LOG_WARNING(RuntimeExecutionLog, "Could not add Garbage to PlayerState, because pointer was null!");
		}
		Inventory->AddResource(ESpawnPointType::SPT_GARBAGE, 1);
	}
}

ICollectableInterface* ACaretakerPlayerState::RemoveGarbage()
{
	if (CollectedGarbage.Num() > 0)
	{
		ICollectableInterface* Garbage = Cast<ICollectableInterface>(CollectedGarbage.Pop(true));
		DebugInventory->SetGarbageAmount(FText::AsNumber(CollectedGarbage.Num()));
		Inventory->RemoveResource(ESpawnPointType::SPT_GARBAGE, CollectedFood);
		CurrentlyCollected--;
		return Garbage;
	}
	else
	{
		LOG_DISPLAY(RuntimeExecutionLog, "No more garbage in PlayerState. Nothing to remove.");

		return nullptr;
	}
}

int8 ACaretakerPlayerState::ClampValues(int8 ValueToClamp, int8 MaxValue)
{
	return FMath::Clamp(ValueToClamp, Zero, MaxValue);
}

#pragma region SetupWidgets
void ACaretakerPlayerState::SetupWidgets(UInventoryWidget* InventoryWidget, UDebugInventoryWidget* DebugInventoryWidget, UInformationWidget* InformationWidget, UDebugInformationWidget* DebugInformationWidget)
{
	if (InventoryWidget == nullptr)
	{
		LOG_WARNING(InitializationLog, "Could not set InventoryWidget in PlayerState, because pointer was null!");

	}
	else
	{
		Inventory = InventoryWidget;
		LOG_DISPLAY(InitializationLog, "InventoryWidget is ready to use!");
	}

	if (DebugInventoryWidget == nullptr)
	{
		LOG_WARNING(InitializationLog, "Could not set DebugInventoryWidget in PlayerState, because pointer was null!");

	}
	else
	{
		DebugInventory = DebugInventoryWidget;
		LOG_DISPLAY(InitializationLog, "DebugInventoryWidget is ready to use!");
	}

	if (InformationWidget == nullptr)
	{
		LOG_WARNING(InitializationLog, "Could not set InventoryWidget in PlayerState, because pointer was null!");

	}
	else
	{
		Information = InformationWidget;
		LOG_DISPLAY(InitializationLog, "InventoryWidget is ready to use!");
	}
	if (DebugInformationWidget == nullptr)
	{

	}
	else
	{
		DebugInformation = DebugInformationWidget;
	}
}
#pragma endregion

const bool ACaretakerPlayerState::HasGarbage()
{
	return CollectedGarbage.Num() > 0;
}

void ACaretakerPlayerState::FreeGarbage()
{
	CollectedGarbage.Pop();
}

void ACaretakerPlayerState::RemoveItemSlot(bool IsGoodPickup)
{
	InventoryLimit--;
	int8 Lower = 0;
	int8 Upper = 10;
	if (IsGoodPickup)
	{
		Lower = 2;
	}
	else
	{
		Lower = 1;
	}
	InventoryLimit = FMath::Clamp(InventoryLimit, Lower, Upper);
	
	UpdateItemSlots();
}

void ACaretakerPlayerState::AddItemSlot()
{
	InventoryLimit++;
	int8 Lower = 0;
	int8 Upper = 10;
	InventoryLimit = FMath::Clamp(InventoryLimit, Lower, Upper);

	UpdateItemSlots();
}

void ACaretakerPlayerState::UpdateItemSlots()
{
}
