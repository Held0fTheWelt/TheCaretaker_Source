/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Enums/FMOD/FMODParameterType.h"
#include "FMODParameterSetList.generated.h"

USTRUCT(BlueprintType)
struct THECARETAKER_API FMODParameterSet
{
	GENERATED_BODY()

public:
	FMODParameterSet(FName Name, EFMODParameterType ParameterType, float SoundChangeValue = 1.0f);

	FMODParameterSet();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ParameterName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EFMODParameterType ParameterType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SoundChangeValue;
};

USTRUCT(BlueprintType)
struct THECARETAKER_API FMODParameterSetList 
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameter List")
	TArray<FMODParameterSet> ParameterSet;

	FName GetParameterName(EFMODParameterType ParameterType);
};

