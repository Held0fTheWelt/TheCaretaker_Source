/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Enums/FMOD/FMODParameterType.h"
#include "MonsterHungerViewWidget.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API UMonsterHungerViewWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UMonsterHungerViewWidget(const FObjectInitializer& ObjectInitializer);

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UVerticalBox* MonsterList;
	
	UFUNCTION(BlueprintCallable, Category = "Monsters")
	TArray<class UMonsterInformationWidget*> GetMonsters() const;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class UFMODAudioComponent* MusicComponent;
		
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "FMOD")
	FName FMODParameterName;	

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "FMOD")
	EFMODParameterType FMODParameterType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "FMOD")
	float FMODVolume;
	
	TArray<class UMonsterInformationWidget*> Monsters;

protected:
	virtual void NativeConstruct() override;

public:
	void AddMonster(class UMonsterInformationWidget* Monster);
	void AddScoreWidget(class UCurrentScoreUserWidget* ScoreWidget);

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	float CalculateCurrentValues();
	void SetFMODParameters(float Value);
};
