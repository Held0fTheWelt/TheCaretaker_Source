/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "MapDefinition.generated.h"


/**
 * 
 */
USTRUCT(BlueprintType)
struct THECARETAKER_API FMapDefinition 
{
	GENERATED_BODY()

public:
	FMapDefinition();

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName LevelName_Menu;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName LevelName_Load;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName LevelName_Tutorial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName LevelName_Credits;
};
