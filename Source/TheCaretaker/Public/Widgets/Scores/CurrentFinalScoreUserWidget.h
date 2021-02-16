// /* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CurrentFinalScoreUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API UCurrentFinalScoreUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UCurrentFinalScoreUserWidget(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* ScoreInGameText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* MeatBonusText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* HungerBonusText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* FinishBonusText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* PickupBonusText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* FinalScoreText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class USoundBase* ScoreAdditionSound;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class USoundBase* PickupBonusSound;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class USoundBase* FinalScoreSound;

public:
	UFUNCTION(BlueprintImplementableEvent)
	void PlayFinalScoreAnimation();
	UFUNCTION(BlueprintImplementableEvent)
	void HideScore();

	void PlaySound();

	void SetScoreInGame(int32 ScoreInGame);
	void SetMeatBonus(int32 MeatBonus);
	void SetHungerBonus(int32 HungerBonus);
	void SetFinishBonus(int32 FinishBonus);
	void SetPickupBonus(int32 PickupBonus);
	void SetFinalScore(int32 FinalScore);

	void Reset();
private:
	int32 Count;

private:
	UFUNCTION()
	void TimerFunction();

	FTimerHandle TimerHandle_ScoreSound;
	void FireSound();
};
