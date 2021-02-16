/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"


UENUM()
enum EPartInformation
{
	EPI_NONE   = 0		UMETA(DisplayName = "None"),
	EPI_LEVEL1 = 1		UMETA(DisplayName = "Part 1"),
	EPI_LEVEL2 = 2		UMETA(DisplayName = "Part 2"),
	EPI_LEVEL3 = 3		UMETA(DisplayName = "Part 3"),
	EPI_END    = 4		UMETA(DisplayName = "END_OF_PARTS"),
	EPI_SPECIAL= 5		UMETA(DisplayName = "Special Area"),
	EPI_MASTER = 6		UMETA(DisplayName = "Dungeon Master Area"),
};