/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "CustomButton.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API UCustomButton : public UButton
{
	GENERATED_BODY()
	
public:
	UCustomButton();

#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override;
#endif

	void SetButtonColors(bool IsActive);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Colors")
	FButtonStyle ButtonStyleActive;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Colors")
	FButtonStyle ButtonStyleInactive;

};
