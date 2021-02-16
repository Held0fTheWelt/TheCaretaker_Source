// /* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LockedByLevelPointsAndDiffActor.generated.h"

UCLASS()
class THECARETAKER_API ALockedByLevelPointsAndDiffActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALockedByLevelPointsAndDiffActor();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Secret")
	int32 DifficultyToUnlock;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Secret")
	int32 LevelPointsToUnlock;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Secret")
	TArray<AActor*> ActorsToHideUntilCompletion;

};
