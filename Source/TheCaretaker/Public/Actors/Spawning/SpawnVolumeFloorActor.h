/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/SpawnPoints/SpawnOnFloorInterface.h"
#include "GameFramework/Actor.h"

#include "SpawnVolumeFloorActor.generated.h"

UCLASS()
class THECARETAKER_API ASpawnVolumeFloorActor : public AActor, public ISpawnOnFloorInterface
{
	GENERATED_BODY()
	
public:	
	ASpawnVolumeFloorActor();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
	class USceneComponent* Scene;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
	class UStaticMeshComponent* Floor;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	TEnumAsByte<EPartInformation> PartInformation;

	// Inherited via ISpawnOnFloorInterface
	virtual EPartInformation GetPartOfLevel() const;

	// Inherited via ISpawnOnFloorInterface
	virtual FVector GetLocation() const override;
};
