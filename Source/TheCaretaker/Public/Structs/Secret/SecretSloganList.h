/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Enums/PlayMode/PlayMode.h"
#include "Structs/Secret/SecretSlogan.h"
#include "SecretSloganList.generated.h"

// Is a Slogan to unlock a secret
USTRUCT(BlueprintType)
struct THECARETAKER_API FSecretSloganList
{
	GENERATED_BODY()

public:
	FSecretSloganList();

public:
	UPROPERTY(EditAnywhere)
	TArray<FSecretSlogan> Slogans;

	TArray<FString> GetSecretSlogans(EPlayMode PlayMode) const;

	int32 GetLevelPointsForIndex(int32 Index) const;
};