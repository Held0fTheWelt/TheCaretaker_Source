/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Generic/ProgressBar/GenericProgressBarWidget.h"
#include "Interfaces/Pause/PauseGameInterface.h"
#include "Interfaces/Widgets/NoiseBar/NoiseBarWidgetInterface.h"
#include "NoiseBarUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API UNoiseBarUserWidget : public UGenericProgressBarWidget, public IPauseGameInterface, public INoiseBarWidgetInterface
{
	GENERATED_BODY()
	
public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "Content")
	class UImage* Background;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "Content")
	class UImage* Bar;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "Content")
	class UTextBlock* Text;

public:
	UNoiseBarUserWidget();

	virtual void NativeOnInitialized() override;
	
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	UFUNCTION(BlueprintCallable, Category = "NoiseBar")
	void CharacterRunning(bool Running);

	void SetNoiseBarMultiplier(float Value);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Components)
	class UFMODAudioComponent* FMODAudio;

	TSubclassOf<class AFirstPersonCharacter> CharacterClass;

	void SetBarVisibility();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Noise Level")
	float NoiseAdditionAtMonsterAngry;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Noise Level")
	bool bMonsterIsAngry;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Noise Level")
	float CurrentNoiseLevel;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Noise Level")
	float SoundChangeValue;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Noise Level")
	float NoiseMultiplier;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Noise Level")
	float DefaultRegainMultiplier;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Noise Level")
	bool IsRunning;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Noise Level")
	float HeartBeatPercent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Noise Sound")
	FName FMODParameterName;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Noise Sound")
	FName FMODAngryParameterName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Noise Level")
	float AngryParameterHeartbeat;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Noise Level")
	float AngryParameterMonster;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character")
	class AFirstPersonCharacter* Character;


private:
	void CalculateCurrentNoise(float InDeltaTime);
	void SetupAudioEvents();
	void SetPercentProgress();
	void SetBarColor();
	void CheckDungeonMasterSleep();

	bool bDungeonMasterAwake;

	UFUNCTION()
	void AddMonsterAngryValue(float Value);
	
private:
	float AngryValue;
	bool bPaused;
	bool bNoiseBarBlock;
	float NoiseModifier;
	float HeartBeatModifierRange;
	float HeartBeatModifier;

private:
	virtual void SetGamePaused(bool SetGamePaused) override;
	virtual bool IsPaused() const;
	virtual void NoisePickupBlockingNoise(bool IsBlockingNoise);
	virtual void NoisyPickup(float NoiseModifier = 1.f) override;
};
