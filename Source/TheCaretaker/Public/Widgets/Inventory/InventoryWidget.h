/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structs/Icons/Inventory/InventoryIconDefinition.h"
#include "Interfaces/Widgets/Inventory/InventoryWidgetInterface.h"
#include "Enums/SpawnPointType/SpawnPointType.h"
#include "InventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UInventoryWidget(const FObjectInitializer& ObjectInitializer);

public:	
	UPROPERTY(meta = (BindWidget))
	class UImage* LeftHand;
	UPROPERTY(meta = (BindWidget))
	class UImage* BackgroundLeft;
	UPROPERTY(meta = (BindWidget))
	class UImage* FrameLeft;

	UPROPERTY(meta = (BindWidget))
	class UImage* RightHand;
	UPROPERTY(meta = (BindWidget))
	class UImage* BackgroundRight;
	UPROPERTY(meta = (BindWidget))
	class UImage* FrameRight;
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* AmountLeft;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* AmountRight;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Icon Definition Table")
	class UDataTable* IconDefinition;

private:
	bool bFirst;

	TEnumAsByte<ESpawnPointType> ResourceLeft;
	TEnumAsByte<ESpawnPointType> ResourceRight;

	TArray<FInventoryIconDefinition*> Icons;
private:
	
	void ShowInventory(bool Show);
	void ShowResourceLeft(bool Show);
	void ShowResourceRight(bool Show);

protected:
	virtual void NativeOnInitialized() override;
	void InitializeIconDefinitions();

public:
	void AddResource(TEnumAsByte<ESpawnPointType> ResourceType, int8 Amount);
	void RemoveResource(TEnumAsByte<ESpawnPointType> ResourceType, int8 Amount);
	void UpdateFood(int8 Amount);
};
