/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SecretCredentialUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API USecretCredentialUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Credential;

public:
	UFUNCTION(BlueprintCallable)
	void SetCredentialInformation(FString CredentialLetter, FLinearColor TextColor, FLinearColor OutlineColor);

private:
	void PerformCredentialInformation(FString CredentialLetter, FLinearColor TextColor, FLinearColor OutlineColor);
};
