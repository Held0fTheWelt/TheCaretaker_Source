/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Part2;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UStartMenuWidget* StartMenu;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UAchievementInputBoxUserWidget* AchievementInputBox;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UMultiLineEditableTextBox* InfoBox;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UHighScoreUserWidget* HighScore;

public:
	UFUNCTION(BlueprintImplementableEvent)
	void PlayAchievementAnimation();

	UFUNCTION(BlueprintImplementableEvent)
	void PlayCompetitionAnimation();

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void PlayPart2Animation();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GamePart")
	bool bIsPart2;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GamePart")
	bool bPlayNewAchieved;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GamePart")
	bool bIsNewlyAchieved;


public:
	virtual void NativeConstruct() override;

	void SetPart2(bool IsPart2);

	void SetNewlyAchieved();

	void HideElementsForAchievementMessage();

	UFUNCTION(BlueprintImplementableEvent)
	void StopAnimationPlaying();

	void UpdateUI();
};
