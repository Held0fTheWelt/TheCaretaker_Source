/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LockedByLevelPointsActor.generated.h"

UCLASS()
class THECARETAKER_API ALockedByLevelPointsActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ALockedByLevelPointsActor();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Secret")
	int32 LevelPointsToUnlock;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Secret")
	TArray<AActor*> ActorsToHideUntilCompletion;
};
