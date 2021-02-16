/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SecretCredentialsItemUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API USecretCredentialsItemUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialUserWidget* Credential1;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialUserWidget* Credential2;

public:
	void SetCredentialInfos(int32 CredentialIndex, FString Character = TEXT(""), FLinearColor TextColorCode = FLinearColor::Black, FLinearColor OutlineColorCode = FLinearColor::Black, int32 ConnectedSloganIndex = -1, TArray<int32> SolvedSloganIndices = TArray<int32>());

	void CheckForSolvedSloganIndex(int32 SolvedSloganIndex);

private:
	UPROPERTY()
	int32 ConnectedSloganIndex1;
	UPROPERTY()
	int32 ConnectedSloganIndex2;
};
