/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EBlueprintDataType : uint8
{
	EBDT_NONE					UMETA(DisplayName = "None"),
	EBDT_ACTOR_CHEST			UMETA(DisplayName = "Chest"),
	EBDT_ACTOR_MONSTER_VOLUME	UMETA(DisplayName = "Monster Feeding Volume"),
	EBDT_ACTOR_MONSTER_WOLF		UMETA(DisplayName = "Wolf"),
	EBDT_ACTOR_MONSTER_SNAKE	UMETA(DisplayName = "Snake"),
	EBDT_ACTOR_MONSTER_MUMMY	UMETA(DisplayName = "Mummy"),
	EBDT_ACTOR_DOOR				UMETA(DisplayName = "Door"),
	EBDT_ACTOR_FIREPLACE		UMETA(DisplayName = "Fireplace"),
	EBDT_ACTOR_MINICAM			UMETA(DisplayName = "Minicam"),
	EBDT_ACTOR_PICKUP			UMETA(DisplayName = "Pickup"),
	EBDT_ACTOR_POWERUP_SPEED	UMETA(DisplayName = "Power Speedup"),
	EBDT_ACTOR_RESOURCE_GOLD	UMETA(DisplayName = "Gold Resource"),
	EBDT_ACTOR_RESOURCE_MEAT	UMETA(DisplayName = "Meat Resource"),
	EBDT_ACTOR_SOUND_SCARE		UMETA(DisplayName = "Scare Sound"),
	EBDT_ACTOR_SPAWNPOINT_GBG	UMETA(DisplayName = "Spawnpoint Garbage"),
	EBDT_ACTOR_SPAWNPOINT_CHS	UMETA(DisplayName = "Spawnpoint Chest"),
	EBDT_ACTOR_SPAWNPOINT_TRP	UMETA(DisplayName = "Spawnpoint Trap"),
	EBDT_ACTOR_SPAWNPOINT_SPD	UMETA(DisplayName = "Spawnpoint Spider"),
	EBDT_ACTOR_TARGETPOINT		UMETA(DisplayName = "Target Point"),
	EBDT_ACTOR_TRAP				UMETA(DisplayName = "Trap"),
	EBDT_ACTOR_TRASH_1			UMETA(DisplayName = "Trash Books"),
	EBDT_ACTOR_TRASH_2			UMETA(DisplayName = "Trash Deadman"),
	EBDT_ACTOR_TRASH_3			UMETA(DisplayName = "Trash Bones"),
	EBDT_ACTOR_TRASH_4			UMETA(DisplayName = "Trash Skulls"),
	EBDT_ACTOR_TRASH_5			UMETA(DisplayName = "Trash Wood"),
	EBDT_ACTOR_WINCONDITION		UMETA(DisplayName = "Win Condition Volume"),
};