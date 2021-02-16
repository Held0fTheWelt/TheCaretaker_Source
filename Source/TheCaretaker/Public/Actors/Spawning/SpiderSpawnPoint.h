/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Actors/Spawning/ObjectiveSpawnPointActor.h"
#include "Interfaces/SpawnPoints/SpiderSpawnPointInterface.h"
#include "SpiderSpawnPoint.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API ASpiderSpawnPoint : public AObjectiveSpawnPointActor, public ISpiderSpawnPointInterface
{
	GENERATED_BODY()
	
public:
	ASpiderSpawnPoint();
protected:
	UPROPERTY(EditAnywhere, Category = "WayPoints")
	int32 PathIndex;

	UPROPERTY(EditAnywhere, Category = "WayPoints")
	TArray<class AConnectedTargetPoint*> TargetWayPoints;

	// Inherited via ISpiderSpawnPointInterface
	virtual TArray<AConnectedTargetPoint*, FDefaultAllocator> GetTargetPoints() const;
	virtual int32 GetPathIndex() const override;
	virtual FString GetName() const override;
};
