/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class ECompare : uint8
{
	CO_EQUAL	UMETA(DisplayName = "Equal"),
	CO_GREATER	UMETA(DisplayName = "Greater"),
	CO_SMALLER	UMETA(DisplayName = "Smaller")
};
