/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InformationWidget.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API UInformationWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TxtGarbage;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TxtGarbageMax;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TxtChests;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TxtChestsMax;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TxtTraps;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TxtTrapsMax;

//	UPROPERTY(meta = (BindWidget))
//	class UTextBlock* TxtMonsters;

public:
	// Sets a new Text Notification
	UFUNCTION(BlueprintCallable, Category = "Text")
	void SetGarbageToCollect(FText Notification);
	void SetGarbageToCollectMax(FText Notification);

	// Clears current Text Notification
	UFUNCTION(BlueprintCallable, Category = "Text")
	void ClearTextGarbageNotification();

	// Sets a new Text Notification
	UFUNCTION(BlueprintCallable, Category = "Text")
	void SetChestsToSolve(FText Notification);
	void SetChestsToSolveMax(FText Notification);

	// Clears current Text Notification
	UFUNCTION(BlueprintCallable, Category = "Text")
	void ClearTextChestsNotification();

	// Sets a new Text Notification
	UFUNCTION(BlueprintCallable, Category = "Text")
	void SetTrapsToSolve(FText Notification);
	void SetTrapsToSolveMax(FText Notification);

	// Clears current Text Notification
	UFUNCTION(BlueprintCallable, Category = "Text")
	void ClearTextTrapsNotification();

	// Sets a new Text Notification
	UFUNCTION(BlueprintCallable, Category = "Text")
	virtual void SetMostAngryMonster(FText Notification);

	// Clears current Text Notification
	UFUNCTION(BlueprintCallable, Category = "Text")
	virtual void ClearTextMonstersNotification();

	UFUNCTION(BlueprintImplementableEvent, Category = "Init")
	void PlayTutorialAnimation(int32 index);
};
