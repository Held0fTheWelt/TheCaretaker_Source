/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/GameMode/Game/GameModeInterface.h"
#include "CurrentScoreUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API UCurrentScoreUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UCurrentScoreUserWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeOnInitialized();

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UHorizontalBox* ScoreAddition1;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UHorizontalBox* ScoreAddition2;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UHorizontalBox* ScoreAddition3;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UHorizontalBox* ScoreAddition4;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 CurrentScore;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 VisualScore;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 ScoreAddition1Value;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 ScoreAddition2Value;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 ScoreAddition3Value;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 ScoreAddition4Value;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float ShowDelay;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float CurrentShowDelay;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bAddition1IsLocked;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bAddition2IsLocked;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bAddition3IsLocked;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bAddition4IsLocked;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bFinishSoundPlayed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float ShowScoreMultiplier;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float TimeToShowScoreAddition;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float TimeToWaitForScoreAddedSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class USoundBase* NewScoreSound;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class USoundBase* SoundAddingScore;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class USoundBase* SoundAddedScore;

public:
	void SetNewScore(int32 NewScore, int32 ScoreAddition1);

	UFUNCTION(BlueprintImplementableEvent)
	void ShowAddedScoreImplementation(int32 index);

private:
	IGameModeInterface* GameModeInterface;
};
