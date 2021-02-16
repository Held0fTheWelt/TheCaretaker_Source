/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "MonsterAnger.generated.h"

USTRUCT(BlueprintType)
struct THECARETAKER_API FMonsterAnger
{
	GENERATED_BODY()

public:
	FMonsterAnger();

	const FString GetName();
	

	void SetAnger(float NewAnger);

public:
	UPROPERTY()
	FName MonsterName;
	UPROPERTY()
	float Anger;
};
