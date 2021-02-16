/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/Widgets/IngameMenu/IngameMenuWidgetInterface.h"
#include "Widgets/BackButton/BackButtonUserWidget.h"
#include "Widgets/Generic/ScreenNotification/ScreenNotification.h"
#include "IngameMenuUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API UIngameMenuUserWidget : public UBackButtonUserWidget, public IIngameMenuWidgetInterface
{
	GENERATED_BODY()
public:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Title;

	UPROPERTY(meta = (BindWidget))
	class UScreenNotification* Subtitle;

	UPROPERTY(meta = (BindWidget))
	class UButton* Continue;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ContinueText;

	UPROPERTY(meta = (BindWidget))
	class UButton* Restart;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* RestartText;

	UPROPERTY(meta = (BindWidget))
	class UButton* Options;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* OptionsText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* BackText;

public:
	void VictoryButton(bool IsVictory);

	void IngameMenuCall();

	UFUNCTION(BlueprintImplementableEvent)
	void HideInformationCallBlueprint();
	virtual void HideInformationCall() override;

protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Messages")
	FText VictoryMessage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Messages")
	FText ContinueMessage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Messages")
	FText RestartMessage;

private:
	UFUNCTION()
	void BackToMenu();
	UFUNCTION()
	void BackToMenuAfterVictory();
	UFUNCTION()
	void ReturnToGame();
	UFUNCTION()
	void ShowOptionsDialog();
	UFUNCTION()
	void RestartLevel();
	UFUNCTION()
	void ContinueToNextPart();
	UFUNCTION()
	void ContinueToNextDifficulty();

	void CloseIngameMenu();
};
