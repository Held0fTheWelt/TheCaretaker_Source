/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MonsterInformationWidget.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API UMonsterInformationWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* MonsterName;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UMonsterHungerBarWidget* MonsterHunger;

	void SetMonsterImage(class UTexture2D* Image);

public:
	void SetProgressBarPercentage(float Value);
	void SetMonsterName(FText Name);


};
