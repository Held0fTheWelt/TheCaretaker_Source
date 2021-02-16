/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "SpiderSetup.generated.h"


USTRUCT(BlueprintType)
struct THECARETAKER_API FSpiderSetup
{
	GENERATED_BODY()

public:
	FSpiderSetup();

public:
	UPROPERTY(EditAnywhere)
	float WalkSpeed;
	UPROPERTY(EditAnywhere)
	float AnimRate;
	UPROPERTY(EditAnywhere)
	float AttackRadius;
	// AttackMode
	// WalkMode
};