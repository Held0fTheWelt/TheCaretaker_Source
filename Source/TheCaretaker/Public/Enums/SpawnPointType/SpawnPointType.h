/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "SpawnPointType.generated.h"

UENUM()
enum ESpawnPointType
{
    SPT_NONE        UMETA(DisplayName = "None"),
    SPT_GARBAGE     UMETA(DisplayName = "Garbage"),
    SPT_CHEST       UMETA(DisplayName = "Chest"),
    SPT_TRAP        UMETA(DisplayName = "Trap"),
    SPT_VOLUME      UMETA(DisplayName = "Feeding Volume"),
    SPT_SPIDER      UMETA(DisplayName = "Spider"),
    SPT_SPIDERPATH  UMETA(DisplayName = "SpiderPathNumber"),
};