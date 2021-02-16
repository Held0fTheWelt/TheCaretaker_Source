/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "CharacterSetup.generated.h"

USTRUCT(BlueprintType)
struct THECARETAKER_API FCharacterSetup
{
	GENERATED_BODY()

public:
	FCharacterSetup();

public:
	UPROPERTY(EditAnywhere)
	float WalkSpeed;
	UPROPERTY(EditAnywhere)
	float RunModifier;
	UPROPERTY(EditAnywhere)
	float RayLength;
	UPROPERTY(EditAnywhere)
	int32 MaxItems;
};