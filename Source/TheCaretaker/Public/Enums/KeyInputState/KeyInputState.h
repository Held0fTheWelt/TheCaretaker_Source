/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EKeyInputState : uint8
{
	KES_NONE			UMETA(DisplayName = "None"),
	KES_BUTTON_DOWN		UMETA(DisplayName = "Button Down"),
	KES_JUST_RELESAED	UMETA(DisplayName = "Released"),
	KES_JUST_PRESSED	UMETA(DisplayName = "Pressed")
};