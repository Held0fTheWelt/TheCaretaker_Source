/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Base/UserWidgetBase.h"
#include "Interfaces/Widgets/Achievement/AchievementWidgetInterface.h"
#include "AchievementWidget.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API UAchievementWidget : public UUserWidgetBase, public IAchievementWidgetInterface
{
	GENERATED_BODY()

public:
	UAchievementWidget();

protected:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* BackgroundImage;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* AchievementImage;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* AchievementUnlocked;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* AchievementAmount;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* AchievementTitle;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* AchievementDescription;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* DateText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* AchievementDate;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fading")
	float TimeToFade;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fading")
	float TimeToLive;

public:
	virtual void SetAchievementInformation(class UTexture2D* Image,int16 Amount, FText Title, FText Description, FText Date) override;

	void SetElementVisibility(bool Visible, bool ShowAmount = false);
private:
	FTimerHandle TimerHandle_AchievementWidget;

private:
	void FadeInFinished();

	void TextShownEnough();

};
