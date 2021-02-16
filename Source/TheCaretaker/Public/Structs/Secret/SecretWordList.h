/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Structs/Secret/SecretWord.h"
#include "SecretWordList.generated.h"


// Is used to identify a Secret Credential Ownage
USTRUCT(BlueprintType)
struct THECARETAKER_API FSecretWordList
{
	GENERATED_BODY()

public:
	FSecretWordList();

public:
	TArray<FSecretWord> SecretWords;


};