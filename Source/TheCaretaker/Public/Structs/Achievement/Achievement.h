/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Enums/Achievement/AchievementType.h"
#include "Structs/Part/PartInformation.h"
#include "Engine/DataTable.h"
#include "Achievement.generated.h"


USTRUCT(BlueprintType)
struct THECARETAKER_API FLevelAchievementInformation
{
	GENERATED_BODY()

public:
	FLevelAchievementInformation();
	FLevelAchievementInformation(int32 Level, int32 Dungeon, EPartInformation Part);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level")
	int32 Level;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level")
	int32 Dungeon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level")
	TEnumAsByte<EPartInformation> Part;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Difficulty")
	int32 AchievedDifficulty;
};

USTRUCT(BlueprintType)
struct THECARETAKER_API FAchieved
{
	GENERATED_BODY()

public:
	FAchieved();

public:
	UPROPERTY(VisibleAnywhere, SaveGame, BlueprintReadWrite, Category = "Achieved Date")
	int32 Index;

	UPROPERTY(VisibleAnywhere, SaveGame, BlueprintReadWrite, Category = "Achieved Date")
	bool bAchieved;

	UPROPERTY(EditAnywhere, SaveGame, BlueprintReadWrite, Category = "Achieved Date")
	FDateTime TimeAchieved;
};

USTRUCT(BlueprintType)
struct THECARETAKER_API FAchievementLoadIdentifier
{
	GENERATED_BODY()

public:
	FAchievementLoadIdentifier();

public:
	UPROPERTY(VisibleAnywhere, SaveGame, BlueprintReadWrite, Category = "Game Progress")
	int32 MaxLevelAchieved;

	UPROPERTY(VisibleAnywhere, SaveGame, BlueprintReadWrite, Category = "Game Progress")
	int32 MaxDifficultyAchieved;

	UPROPERTY(VisibleAnywhere, SaveGame, BlueprintReadWrite, Category = "Game Progress")
	int32 MaxDungeonAchieved;

	UPROPERTY(VisibleAnywhere, SaveGame, BlueprintReadWrite, Category = "Game Progress")
	TEnumAsByte<EPartInformation> MaxPartAchievedInDungeon;

	UPROPERTY(VisibleAnywhere, SaveGame, BlueprintReadWrite, Category = "Game Progress")
	FName LatesMapNameAchieved;
};

USTRUCT(BlueprintType)
struct THECARETAKER_API FAchievement
{
	GENERATED_BODY()

public:
	FAchievement(EAchievementType NewAchievementType);

	FAchievement();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Type")
	TEnumAsByte<EAchievementType> AchievementType;
	UPROPERTY(EditAnywhere, SaveGame, BlueprintReadWrite, Category = "Count")
	int32 CurrentCount;
};
