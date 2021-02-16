/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#include "Structs/EventDate/EventDateRow.h"

FEventHighlight::FEventHighlight()
{
	Date = FDateTime::Now();
	DateName = "";
	ReturningEventDay = EDayEnum::DE_NONE;
	bReturning = false;
}

FEventDateRow::FEventDateRow()
{
	EventType = EEventType::ET_NONE;
	EventBegin = FDateTime::Now();
	EventEnding = FDateTime::Now();
	EventHightlight = TArray<FEventHighlight>();
	bIsStableDate = false;
	StartDay = EDayEnum::DE_NONE;
	EndDay = EDayEnum::DE_NONE;
	bStartByDay = false;
}
