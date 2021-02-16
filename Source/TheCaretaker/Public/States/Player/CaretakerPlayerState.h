/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Enums/ResourceType/ResourceType.h"
#include "Interfaces/GameState/GameStateInterface.h"
#include "Interfaces/PlayerState/PlayerStateInterface.h"
#include "Interfaces/Collectables/CollectableInterface.h"
#include "Structs/Spawning/SpawnInformationTable.h"
#include "CaretakerPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API ACaretakerPlayerState : public APlayerState, public IPlayerStateInterface
{
	GENERATED_BODY()
	
public:

	ACaretakerPlayerState();

	virtual void BeginPlay() override;
public:
	UPROPERTY(EditDefaultsOnly, Category = "Collectables")
	int8 CollectedFood;
	UPROPERTY(EditDefaultsOnly, Category = "Collectables")
	int8 CollectedGold;

	UPROPERTY(EditDefaultsOnly, Category = "Collectables")
	int8 MaxGold;

	UPROPERTY(EditDefaultsOnly, Category = "Collectables")
	int8 MaxFood;
	
	UPROPERTY(EditDefaultsOnly, Category = "Collectables")
	int8 InventoryLimit;
	

	UPROPERTY(EditDefaultsOnly, Category = "Collectables")
	int8 MaxGarbage;

	UPROPERTY(EditDefaultsOnly, Category = "Collectables")
	TArray<AActor*> CollectedGarbage;

	const bool GetCurrentLimitStatus() const;
public:
	const int8 GetFoodCount() { return CollectedFood; }
	const int8 GetGoldCount() { return CollectedGold; }
	UFUNCTION()
	void AddGold(int8 GoldToAdd, class AResourceActor* Actor);
	UFUNCTION()
	void RemoveGold(int8 GoldToRemove);
	UFUNCTION()
	void AddFood(int8 FoodToAdd, class AResourceActor* Actor);
	UFUNCTION()
	void RemoveFood(int8 FoodToRemove);
	UFUNCTION()
	void DropLeft();
	UFUNCTION()
	void DropRight();

	void AddCollectableGarbage(ICollectableInterface* Garbage, class AResourceActor* Actor);
	ICollectableInterface* RemoveGarbage();

private:
	int8 ClampValues(int8 ValueToClamp, int8 MaxValue);

public:
	class UDebugInventoryWidget* DebugInventory;
	
	class UInformationWidget* Information;
	class UDebugInformationWidget* DebugInformation;
	class UInventoryWidget* Inventory;

public:
	void SetupWidgets(class UInventoryWidget* InventoryWidget, class UDebugInventoryWidget* DebugInventoryWidget, class UInformationWidget* InformationWidget, class UDebugInformationWidget* DebugInformationWidget);

	const bool HasGarbage();
	void FreeGarbage();

private:
	UPROPERTY(VisibleAnywhere, Category = "Analysis | Spawning")
	TArray<FGarbageSpawnInformation> GarbageSpawnInformation;

	int8 Zero;
	UPROPERTY(VisibleAnywhere, Category = "Collectables")
	int8 CurrentlyCollected;
	UPROPERTY(VisibleAnywhere, Category = "Collectables")
	EResourceType LeftHandStatus;
	UPROPERTY(VisibleAnywhere, Category = "Collectables")
	EResourceType RightHandStatus;
	UPROPERTY(VisibleAnywhere, Category = "Collectables")
	TSubclassOf<class AGarbageActor> LeftHandGarbage;
	UPROPERTY(VisibleAnywhere, Category = "Collectables")
	TSubclassOf<class AGarbageActor> RightHandGarbage;

	IGameStateInterface* GameStateInterface;

	// Geerbt über IPlayerStateInterface
	virtual void RemoveItemSlot(bool IsGoodPickup) override;
	virtual void AddItemSlot();

	void UpdateItemSlots();
};
