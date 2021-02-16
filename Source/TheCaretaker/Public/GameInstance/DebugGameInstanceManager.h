// /* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "GameInstance/GameInstanceManager.h"
#include "DebugGameInstanceManager.generated.h"


USTRUCT(BlueprintType)
struct THECARETAKER_API FTestDungeonSetup
{
	GENERATED_BODY()

public:
	FTestDungeonSetup();
public:
	UPROPERTY(EditDefaultsOnly)
	bool bSolvedPart1;
	UPROPERTY(EditDefaultsOnly)
	bool bSolvedPart2;
	UPROPERTY(EditDefaultsOnly)
	bool bSolvedPart3;
};

USTRUCT(BlueprintType)
struct THECARETAKER_API FTestDifficultySetup
{
	GENERATED_BODY()

public:
	FTestDifficultySetup();

public:
	UPROPERTY(EditDefaultsOnly)
	TArray<FTestDungeonSetup> Dungeons;
	UPROPERTY(EditDefaultsOnly)
	bool bSolvedComplete;
};

USTRUCT(BlueprintType)
struct THECARETAKER_API FTestLevelSetup
{
	GENERATED_BODY()

public:
	FTestLevelSetup();

public:
	UPROPERTY(EditDefaultsOnly)
	TArray<FTestDifficultySetup> Difficulties;
	UPROPERTY(EditDefaultsOnly)
	bool bSolvedComplete;
};

USTRUCT(BlueprintType)
struct THECARETAKER_API FTestSetup
{
	GENERATED_BODY()

public:
	FTestSetup();
public:
	UPROPERTY(VisibleAnywhere)
	EPlayMode PlayMode;

	UPROPERTY(EditDefaultsOnly)
	TArray<FTestLevelSetup> Levels;
};

/**
 * 
 */
UCLASS()
class THECARETAKER_API UDebugGameInstanceManager : public UGameInstanceManager
{
	GENERATED_BODY()

public:
	UDebugGameInstanceManager(const FObjectInitializer& ObjectInitializer);

	/** virtual function to allow custom GameInstances an opportunity to set up what it needs */
	virtual void Init() override;

protected:
	UPROPERTY(EditDefaultsOnly)
	bool bUseDebugSetup;
	UPROPERTY(EditDefaultsOnly)
	bool bPart2;
	UPROPERTY(EditDefaultsOnly)
	bool bCompetition;
	UPROPERTY(EditDefaultsOnly)
	bool bExtraLevels;
	UPROPERTY(EditDefaultsOnly)
	bool bSpeedPickups;
	UPROPERTY(EditDefaultsOnly)
	bool bInvisibilityPickups;
	UPROPERTY(EditDefaultsOnly)
	bool bNoisePickups;
	UPROPERTY(EditDefaultsOnly)
	bool bInventoryPickups;
	UPROPERTY(EditDefaultsOnly)
	bool bTimePickups1;
	UPROPERTY(EditDefaultsOnly)
	bool bTimePickups2;

	UPROPERTY(EditDefaultsOnly)
	TArray<FTestSetup> TestSetup;

private:
	void CalculateNewProgress();
	void AddOnAddOns();
};
