// /* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/SpiderWeb/SpiderWebInterface.h"
#include "SpiderWebActor.generated.h"

UCLASS()
class THECARETAKER_API ASpiderWebActor : public AActor, public ISpiderWebInterface
{
	GENERATED_BODY()
	
public:	
	ASpiderWebActor();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class USceneComponent* Root;

	UPROPERTY(EditAnywhere, Category = "Lock")
	int32 DifficultyToUnlock;

	UPROPERTY(EditAnywhere, Category = "Lock")
	int32 LevelPointsToUnlock;

protected:
	virtual void BeginPlay() override;

};
