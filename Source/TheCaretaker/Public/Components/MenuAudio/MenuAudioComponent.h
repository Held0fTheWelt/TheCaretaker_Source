/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Components/AudioComponent.h"
#include "Interfaces/GameInstance/GameInstanceAccessoryInterface.h"
#include "MenuAudioComponent.generated.h"

USTRUCT(BlueprintType)
struct THECARETAKER_API FMenuAudioClip
{
	GENERATED_BODY()

public:
	FMenuAudioClip();

public:

	UPROPERTY(EditAnywhere)
	int32 LevelPointsNeeded;
	
	UPROPERTY(EditAnywhere)
	bool bIsPart2;

	UPROPERTY(EditAnywhere)
	class USoundBase* AudioClip;
};

/**
 * 
 */
UCLASS()
class THECARETAKER_API UMenuAudioComponent : public UAudioComponent
{
	GENERATED_BODY()

		UMenuAudioComponent();
protected:
	virtual void BeginPlay() override;
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Clips")
	TArray<FMenuAudioClip> AudioClipSettings;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Clips")
	TArray<class USoundBase*> CompetitionSoundtrack;

	void ContinueCompetition();

private:
	IGameInstanceAccessoryInterface* GameInstance;
};
