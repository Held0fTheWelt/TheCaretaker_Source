/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Enums/GameMessages/GameMessageType.h"
#include "CaretakerMessages.generated.h"

USTRUCT(BlueprintType)
struct THECARETAKER_API FGameMessage
{
	GENERATED_BODY()

public:
	FGameMessage();

	FGameMessage(EGameMessageType Type);
	
	FGameMessage(EGameMessageType Type, FText Msg);

public:
	UPROPERTY(EditAnywhere)
	FText Message;

	UPROPERTY(EditAnywhere)
	EGameMessageType MessageType;
};

/**
 *
 */
USTRUCT(BlueprintType)
struct THECARETAKER_API FCaretakerMessages 
{
	GENERATED_BODY()

public:
	FCaretakerMessages();

public:
	FText GetTextForMessageType(EGameMessageType MessageType);

public:
	UPROPERTY(EditDefaultsOnly, Category = "Game | Messages")
	TArray<FGameMessage> GameMessages;
};
