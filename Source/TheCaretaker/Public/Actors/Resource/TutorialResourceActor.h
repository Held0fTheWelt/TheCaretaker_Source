/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Actors/Resource/ResourceActor.h"
#include "Interfaces/Tutorial/TutorialInterface.h"
#include "Interfaces/Tutorial/TutorialActorInterface.h"
#include "Structs/Tutorial/TutorialInformation.h"
#include "TutorialResourceActor.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API ATutorialResourceActor : public AResourceActor, public ITutorialActorInterface
{
	GENERATED_BODY()

public:
	ATutorialResourceActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void LeftMouseButtonClicked(ICollectableInterface*& CollectableRef) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Tutorial")
	TArray<FTutorialInformation> TutorialInformation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Tutorial")
	int32 IndexInTutorial;

private:
	ITutorialInterface* TutorialGameMode;
};
