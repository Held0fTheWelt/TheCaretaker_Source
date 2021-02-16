/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "Interfaces/TargetPoints/TargetPointInterface.h"
#include "ConnectedTargetPoint.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API AConnectedTargetPoint : public ATargetPoint, public ITargetPointInterface
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Connected Target Points")
	TArray<AConnectedTargetPoint*> ConnectedTargetPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Connected Target Points")
	bool bCountsDirection;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Connected Target Points")
	bool bSkipToZero;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	bool bIsSpawnPoint;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	int32 PathNumber;
};
