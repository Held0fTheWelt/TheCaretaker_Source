/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "SecretWord.generated.h"


// Is used to identify a Secret Credential Ownage
USTRUCT(BlueprintType)
struct THECARETAKER_API FSecretWord
{
	GENERATED_BODY()

public:
	FSecretWord();

public:
	FString SecretWord;
};