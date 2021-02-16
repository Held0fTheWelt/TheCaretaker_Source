/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "Interfaces/SpawnPoints/MonsterSpawnPointInterface.h"
#include "MonsterSpawnPoint.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API AMonsterSpawnPoint : public ATargetPoint, public IMonsterSpawnPointInterface
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	class AActor* MonsterPawn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	class ATutorialFeedingVolumeActor* FeedingVolume;

public:
	virtual void ShowMonster() override;
};
