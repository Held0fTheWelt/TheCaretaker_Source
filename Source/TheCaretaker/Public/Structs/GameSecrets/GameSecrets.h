/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Enums/GameSecrets/GameSecretsEnum.h"
#include "GameSecrets.generated.h"

USTRUCT(BlueprintType)
struct THECARETAKER_API FGameSecret
{
	GENERATED_BODY()

public:
	FGameSecret();
	FGameSecret(EGameSecretsEnum Type);

public:
	UPROPERTY()
	EGameSecretsEnum GameSecret;
	UPROPERTY()
	bool bIsActive;
	UPROPERTY()
	FText AchievementTitle;
	UPROPERTY()
	FText AchievementMessage;
};

USTRUCT(BlueprintType)
struct THECARETAKER_API FGameSecrets
{
	GENERATED_BODY()

public:
	FGameSecrets();

public:
	TArray<FGameSecret> Secrets;
};

