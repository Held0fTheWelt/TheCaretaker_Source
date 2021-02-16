/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"


UENUM(BlueprintType)
enum class ECollectionDataType : uint8
{
	ECDT_NONE			UMETA(DisplayName = "None"),
	ECDT_FLOOR			UMETA(DisplayName = "Floor"),
	ECDT_GROUND			UMETA(DisplayName = "Ground"),
	ECDT_WALL			UMETA(DisplayName = "Wall"),
	ECDT_WALLHOLE		UMETA(DisplayName = "Wall with Hole"),
	ECDT_PILLAR			UMETA(DisplayName = "Pillar"),
	ECDT_PILLAR_SUPPORT	UMETA(DisplayName = "Pillar Support"),
	ECDT_PILLAR_CROSS1	UMETA(DisplayName = "Pillar Crossbar"),
	ECDT_PILLAR_CROSS2	UMETA(DisplayName = "Pillar Crossbar2"),
	ECDT_DOOR_1		UMETA(DisplayName = "Door1"),
	ECDT_DOOR_2		UMETA(DisplayName = "Door2"),
	ECDT_DOOR_3		UMETA(DisplayName = "Door3"),
	ECDT_CEILING	UMETA(DisplayName = "Ceiling"),	
	ECDT_TORCH		UMETA(DisplayName = "Torch"),	
	ECDT_CHEST_BOD	UMETA(DisplayName = "Chest Body"),	
	ECDT_CHEST_COV	UMETA(DisplayName = "Chest Cover"),	
	ECDT_TRAP_BOD	UMETA(DisplayName = "Trap Body"),	
	ECDT_TRAP_SPK	UMETA(DisplayName = "Trap Spikes"),	
	ECDT_GB_BOOKS	UMETA(DisplayName = "Garbage Books"),	
	ECDT_GB_DEADMAN UMETA(DisplayName = "Garbage DeadMan"),	
	ECDT_GB_SKULLS	UMETA(DisplayName = "Garbage Skulls"),	
	ECDT_GB_BONES	UMETA(DisplayName = "Garbage Bones"),	
	ECDT_GB_WOOD	UMETA(DisplayName = "Garbage Wood"),	
	ECDT_FIREPLACE	UMETA(DisplayName = "Fireplace"),	
	ECDT_GOLD		UMETA(DisplayName = "Gold"),	
	ECDT_MEAT		UMETA(DisplayName = "Meat")
};