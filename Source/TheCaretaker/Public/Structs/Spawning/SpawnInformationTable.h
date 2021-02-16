/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Actors/Garbage/GarbageActor.h"
#include "Actors/Chest/ChestActor.h"
#include "Actors/Trap/TrapActor.h"
#include "Characters/Spider/SpiderCharacter.h"
#include "SpawnInformationTable.generated.h"

#pragma region Garbage Spawn Information Struct
USTRUCT(BlueprintType)
struct THECARETAKER_API FGarbageSpawnInformation
{
	GENERATED_BODY()

public:
	FGarbageSpawnInformation();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blueprint")
	TSubclassOf<AGarbageActor> GarbageBlueprint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transform")
	FVector LocalRelocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transform")
	FVector LocalReScaling;
};
#pragma endregion

#pragma region Chest Spawn Information Struct
USTRUCT(BlueprintType)
struct THECARETAKER_API FChestSpawnInformation
{
	GENERATED_BODY()

public:
	FChestSpawnInformation();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blueprint")
	TSubclassOf<AChestActor> ChestBlueprint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transform")
	FVector LocalRelocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transform")
	FVector LocalReScaling;
};
#pragma endregion

#pragma region Trap Spawn Information Struct
USTRUCT(BlueprintType)
struct THECARETAKER_API FTrapSpawnInformation
{
	GENERATED_BODY()

public:
	FTrapSpawnInformation();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blueprint")
	TSubclassOf<ATrapActor> TrapBlueprint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transform")
	FVector LocalRelocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transform")
	FVector LocalReScaling;
};
#pragma endregion

#pragma region Spider Spawn Information
USTRUCT(BlueprintType)
struct THECARETAKER_API FSpiderSpawnInformation
{
	GENERATED_BODY()

public:
	FSpiderSpawnInformation();
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blueprint")
	TSubclassOf<ASpiderCharacter> SpiderBlueprint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transform")
	FVector LocalRelocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transform")
	FVector LocalReScaling;
};
#pragma endregion

#pragma region Spawn Information Table
USTRUCT(BlueprintType)
struct THECARETAKER_API FSpawnInformationTable : public FTableRowBase
{
	GENERATED_BODY()

public:
	FSpawnInformationTable();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Garbage Setup")
	TArray<FGarbageSpawnInformation> GarbageInformation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chest Setup")
	TArray<FChestSpawnInformation> ChestInformation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trap Setup")
	TArray<FTrapSpawnInformation> TrapInformation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spider Setup")
	TArray<FSpiderSpawnInformation> SpiderInformation;

public:
	TArray<FGarbageSpawnInformation> GetGarbageInformation() const;
	TArray<FChestSpawnInformation> GetChestInformation() const;
	TArray<FTrapSpawnInformation> GetTrapInformation() const;
	TArray<FSpiderSpawnInformation> GetSpiderInformation() const;

};
#pragma endregion