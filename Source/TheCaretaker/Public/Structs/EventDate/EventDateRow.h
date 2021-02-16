/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Enums/Event/EventType.h"
#include "Enums/Time/DayEnum.h"
#include "EventDateRow.generated.h"

USTRUCT(BlueprintType)
struct THECARETAKER_API FEventHighlight
{
	GENERATED_BODY()

public:
	FEventHighlight();

public:
	UPROPERTY(EditAnywhere)
	FDateTime Date;

	UPROPERTY(EditAnywhere)
	FString DateName;

	UPROPERTY(EditAnywhere)
	EDayEnum ReturningEventDay;

	UPROPERTY(EditAnywhere)
	bool bReturning;
};

USTRUCT(BlueprintType)
struct THECARETAKER_API FEventDateRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	FEventDateRow();

public:
	UPROPERTY(EditAnywhere)
	EEventType EventType;

	UPROPERTY(EditAnywhere)
	FDateTime EventBegin;

	UPROPERTY(EditAnywhere)
	TArray<FEventHighlight> EventHightlight;
	
	UPROPERTY(EditAnywhere)
	FDateTime EventEnding;
	
	UPROPERTY(EditAnywhere)
	bool bIsStableDate;

	UPROPERTY(EditAnywhere)
	EDayEnum StartDay;

	UPROPERTY(EditAnywhere)
	EDayEnum EndDay;
	UPROPERTY(EditAnywhere)
	bool bStartByDay;
};

