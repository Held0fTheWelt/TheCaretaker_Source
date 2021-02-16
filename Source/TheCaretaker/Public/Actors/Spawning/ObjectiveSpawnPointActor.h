/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "Interfaces/SpawnPoints/ObjectiveSpawnPointInterface.h"
#include "Enums/PartInformation/PartInformationEnum.h"
#include "ObjectiveSpawnPointActor.generated.h"

UCLASS()
class THECARETAKER_API AObjectiveSpawnPointActor : public ATargetPoint, public IObjectiveSpawnPointInterface
{
	GENERATED_BODY()
	
public:	
	AObjectiveSpawnPointActor();
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning Type")
	TEnumAsByte<ESpawnPointType> SpawnPointType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* PreviewMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Part")
	TEnumAsByte<EPartInformation> Part;
public:	
	virtual ESpawnPointType GetSpawnPointType() const override;
	virtual FTransform GetCurrentTransform() const override;

	// Inherited via IObjectiveSpawnPointInterface
	virtual EPartInformation GetCurrentPart() const override;

public:
	UPROPERTY()
	bool bSpawned;

	// Geerbt über IObjectiveSpawnPointInterface
	virtual void SetSpawned(bool Spawned) override;
	virtual bool GetIsSpawned() const override;
};
