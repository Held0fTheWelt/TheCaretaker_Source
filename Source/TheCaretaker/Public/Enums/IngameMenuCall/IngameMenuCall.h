/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "IngameMenuCall.generated.h"

UENUM()
enum EIngameMenuCall
{
    IMC_NONE            UMETA(DisplayName = "None"),
    IMC_DEFAULT         UMETA(DisplayName = "Garbage"),
    IMC_DEATHBYSPIDER   UMETA(DisplayName = "Death Menu Call by Spider"),
    IMC_DEATHBYMONSTER  UMETA(DisplayName = "Death Menu Call by hungry Monster"),
    IMC_DEATHBYTRAP     UMETA(DisplayName = "Death Menu Call by Trap execution"),
    IMC_VICTORY         UMETA(DisplayName = "Victory Menu Call"),
    IMC_TIME            UMETA(DisplayName = "Time is Up Call"),
    IMC_DEATHBYPICKUP   UMETA(DisplayName = "Death Menu Call by Pickup execution"),
};