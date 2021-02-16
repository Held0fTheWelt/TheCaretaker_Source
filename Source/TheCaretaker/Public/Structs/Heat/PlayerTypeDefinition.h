/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Enums/PlayMode/PlayMode.h"
#include "PlayerTypeDefinition.generated.h"

USTRUCT(BlueprintType)
struct THECARETAKER_API FPlayerTypeDefinition : public FTableRowBase
{
	GENERATED_BODY()

public:
	FPlayerTypeDefinition();

public:
	UPROPERTY(EditAnywhere)
	EPlayMode PlayMode;

	UPROPERTY(EditAnywhere)
	FString PlayerDescription;	
};
