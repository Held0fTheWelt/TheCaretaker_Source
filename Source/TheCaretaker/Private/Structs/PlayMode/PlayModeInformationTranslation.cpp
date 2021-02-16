/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#include "Structs/PlayMode/PlayModeInformationTranslation.h"
#include "Enums/PlayMode/PlayMode.h"


FPlayModeInformationTranslation::FPlayModeInformationTranslation()
{
	PlayMode = EPlayMode::PM_NONE;

	Level = 0;
	Dungeon = 0;
	Difficulty = 0;
	PartInformation = EPartInformation::EPI_NONE;
	PartOfLevel = EPartInformation::EPI_NONE;
	
	TitleMessage = FText::FromString(TEXT(""));
	SubtitleMessage = FText::FromString(TEXT(""));
	
	NumberOfGarbage = 0;
	NumberOfChests = 0;
	NumberOfTraps = 0;
	
	NumberOfSpiders = 0;
	PathNumberMax = 0;
	PathSpreadValues = TArray<float>();
	
	TimeToGetHungry = 0.f;
	bWaitForEndOfTime = false;
	
	PlayModeOfPart = EPlayMode::PM_NONE;
	
	Secret0Character = FString("");
	Secret0Color = FLinearColor::Black;
	Secret0SubColor = FLinearColor::Black;
	Secret0SloganIndex = 0;

	Secret1Character = FString("");
	Secret1Color = FLinearColor::Black;
	Secret1SubColor = FLinearColor::Black;
	Secret1SloganIndex = 0;
}
