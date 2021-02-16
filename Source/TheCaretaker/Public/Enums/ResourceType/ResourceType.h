/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"


UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EResourceType : uint8
{
	RT_NONE 	UMETA(DisplayName = "None"),
	RT_GOLD 	UMETA(DisplayName = "Gold"),
	RT_MEAT 	UMETA(DisplayName = "Meat"),
	RT_GARBAGE 	UMETA(DisplayName = "Garbage"),
};