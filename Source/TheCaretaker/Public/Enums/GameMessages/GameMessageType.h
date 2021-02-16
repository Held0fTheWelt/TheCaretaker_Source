/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EGameMessageType : uint8
{
	GMT_None			UMETA(DisplayName = "None"),
	GMT_TITLE_PAUSE		UMETA(DisplayName = "Pause Title Message"),
	GMT_TITLE_DEATH		UMETA(DisplayName = "Death Title Message"),
	GMT_TITLE_VICTORY	UMETA(DisplayName = "Victory Title Message"),
	GMT_SUB_PAUSE		UMETA(DisplayName = "Pause Subitle Message"),
	GMT_SUB_DEATH_SPD	UMETA(DisplayName = "Death by Spider Subitle Message"),
	GMT_SUB_DEATH_TRP	UMETA(DisplayName = "Death by Trap Subitle Message"),
	GMT_SUB_DEATH_TME	UMETA(DisplayName = "Death by Time Subitle Message"),
	GMT_SUB_DEATH_NSE	UMETA(DisplayName = "Death by Noise Subitle Message"),
	GMT_SUB_DEATH_PWR	UMETA(DisplayName = "Death by Power Up Subitle Message"),
	GMT_SUB_VICTORY		UMETA(DisplayName = "Victory Subitle Message"),
	
};
