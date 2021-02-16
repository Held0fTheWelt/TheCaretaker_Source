/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Types/SlateEnums.h"
#include "Interfaces/GameInstance/GameInstanceInterface.h"
#include "AchievementInputBoxUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API UAchievementInputBoxUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UAchievementInputBoxUserWidget(const FObjectInitializer& ObjectInitializer);
public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void PlayAnimationInput(bool Forward);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void PlayAnimationMessage(bool Forward);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void PlayWindowAnimation(int32 AnimationIndex, bool Forward);

	UFUNCTION()
	void TestTextCommited(const FText &Text, ETextCommit::Type CommitMethod);

	void SecretUnlockedMessage(FText SecretTitle, FText SecretSlogan, FText SecretMessage, bool Success);
	void HideSecretUnlockedAgain();

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UEditableTextBox* TextBox;
	
	UPROPERTY(meta = (BindWidget))
	class UImage* BackgroundTextBox;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* SecretTitle;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* SecretSlogan;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* SecretMessage;

	class IGameInstanceInterface* GameInstance;

	UPROPERTY(EditDefaultsOnly)
	float TimeToShowSecretUnlockedMessage;

	UPROPERTY(EditDefaultsOnly)
	class USoundBase* SecretUnlockedSound;

	UPROPERTY(EditDefaultsOnly)
	class USoundBase* SecretUnlockFailSound;
		
private:
	FTimerHandle TimerHandle_SecretUnlocked;
};
