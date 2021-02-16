/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

UENUM(BlueprintType)
enum EAchievementType
{
	AT_NONE UMETA(DisplayName = "None"),
	AT_GARBAGE UMETA(DisplayName = "Garbage"),
	AT_GOLD UMETA(DisplayName = "Gold"),
	AT_MEAT UMETA(DisplayName = "Meat"),
	AT_TRAP UMETA(DisplayName = "Trap"),
	AT_VICTORY UMETA(DisplayName = "Victory"),
	AT_DEATHBYSPIDER UMETA(DisplayName = "Death by Spider"),
	AT_DEATHBYMONSTER UMETA(DisplayName = "Death by Monster"),
	AT_DEATHBYTRAP UMETA(DisplayName = "Death by Trap"),
	AT_DEATHBYTIME UMETA(DisplayName = "Death by Time"),
	AT_PROGRESS UMETA(DisplayName = "Progress Achievement"),
	AT_DEATHBYPICKUP UMETA(DisplayName = "Death by Pickup"),
	AT_SECRETUNLOCKED UMETA(DisplayName = "Secret Unlocked"),
	AT_HIGHSCORE UMETA(DisplayName = "Highscore Achievement"),
	AT_WINCONDITIONMET UMETA(DisplayName = "WinCondition Met Achievement"),
	AT_PICKUP UMETA(DisplayName = "Pickup Achievement"),
	AT_SUPERBONUSPICKUP UMETA(DisplayName = "Super Bonus Pickup Achievement"),
	AT_BAD_PICKUP UMETA(DisplayName = "Bad Pickup Achievement"),
};