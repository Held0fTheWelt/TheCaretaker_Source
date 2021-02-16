/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "SecretConnection.generated.h"

// Is a Slogan to unlock a secret
USTRUCT(BlueprintType)
struct THECARETAKER_API FSecretConnection : public FTableRowBase
{
	GENERATED_BODY()

public:
	FSecretConnection();

public:
	UPROPERTY(EditAnywhere)
	int32 Index;
	
	UPROPERTY(EditAnywhere)
	TArray<FString> SecretCredentials;
};