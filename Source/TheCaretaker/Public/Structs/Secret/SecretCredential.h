/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "SecretCredential.generated.h"

// Is part of a Secret Slogan
USTRUCT(BlueprintType)
struct THECARETAKER_API FSecretCredential
{
	GENERATED_BODY()

public:
	FSecretCredential();

public:
	// The character to receive
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Character;
	// The color to show the Character for connection to Unique Slogan
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor TextColorCode;

	// The color to show the characters outlining for connection to Unique Slogan
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor OutlineColorCode;

	// The index of the connected slogan
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ConnectedSloganIndex;

};