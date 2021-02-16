/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "SecretCredentialsUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API USecretCredentialsUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Title;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UHorizontalBox* NewlyAchievedCredentials;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UHorizontalBox* AchievedCredentials;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class USecretCredentialUserWidget* FirstNewCredential;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class USecretCredentialUserWidget* SecondNewCredential;

public:
	UFUNCTION(BlueprintImplementableEvent)
	void PlayWidgetAnimation(int32 Index, bool Forward);

	void SetCredentials(FString C1, FLinearColor C1TextColor, FLinearColor C1OutlineColor, FString C2, FLinearColor C2TextColor, FLinearColor C2OutlineColor);

	virtual void NativeOnInitialized();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Credentials")
	TSubclassOf<class USecretCredentialUserWidget> SecretCredentialTemplate;
	
};
