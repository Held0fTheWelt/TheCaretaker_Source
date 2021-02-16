/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Actors/Pickups/PowerUp/BadLuckPowerUp.h"
#include "Interfaces/Characters/Spider/SpiderInterface.h"
#include "BadLuck_SpiderRun_PowerUp.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API ABadLuck_SpiderRun_PowerUp : public ABadLuckPowerUp
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Expired() override;

	virtual void Activated(class AActor* OtherActor) override;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Speed")
	float MaxWalkSpeed;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Speed")
	float AnimRate;

private:
	TArray<ISpiderInterface*> SpidersInScene;

	float PreviousWalkSpeed;
	float PreviousAnimRate;
};
