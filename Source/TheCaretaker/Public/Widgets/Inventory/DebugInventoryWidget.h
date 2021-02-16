/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/Widgets/Inventory/DebugInventoryWidgetInterface.h"
#include "DebugInventoryWidget.generated.h"

/** Class to Debug Happpenings on GameField */
UCLASS()
class THECARETAKER_API UDebugInventoryWidget : public UUserWidget, public IDebugInventoryWidgetInterface
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TxtCollectedGold;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TxtCollectedMeat;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TxtCollectedGarbage;

	// Sets a new Text Notification
	UFUNCTION(BlueprintCallable, Category = "Text")
	void SetGoldAmount(FText GoldAmount);
	void SetMeatAmount(FText MeatAmount);
	void SetGarbageAmount(FText GarbageAmount);


	UFUNCTION(BlueprintCallable, Category = "Text")
	void ClearGold();

	UFUNCTION(BlueprintCallable, Category = "Text")
	void ClearMeat();

	UFUNCTION(BlueprintCallable, Category = "Text")
	void ClearGarbage();
};
