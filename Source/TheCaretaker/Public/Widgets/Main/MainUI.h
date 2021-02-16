/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structs/Icons/Inventory/InventoryIconDefinition.h"
#include "MainUI.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API UMainUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UMainUI(const FObjectInitializer& ObjectInitializer);

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UScreenNotification* ScreenNotifications;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UMiniMapWidget* MiniMap;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UMonsterHungerViewWidget* Monsters;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UDebugInventoryWidget* DebugInventory;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UInformationWidget* Information;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UDebugInformationWidget* DebugInformation;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTimeInformationWidget* Clock;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UInventoryWidget* Inventory;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* LevelTitle;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UNoiseBarUserWidget* Noisebar;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UAchievementWidget* AchievementUnlocked;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class USecretCredentialsUserWidget* SecretCredentials;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UCurrentFinalScoreUserWidget* FinalScore;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UPickupUserWidget* PickupWidget;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UCurrentHighScoreUserWidget* HighScore;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTrapTimerUserWidget* TrapTimer;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Tutorial")
	bool bTutorialPlaying;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	FInventoryIconDefinition InventoryImages;

public:
	void ShowPartInformation(FText Title, FText ScreenNotification, int32 index);
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void StartAnimation(int32 index);

	void ShowPickupWidget(bool Show);
};
