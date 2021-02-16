/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Actors/Monsters/MonsterFeedingVolumeActor.h"
#include "Interfaces/Tutorial/TutorialInterface.h"
#include "Interfaces/Tutorial/TutorialActorInterface.h"
#include "Structs/Tutorial/TutorialInformation.h"
#include "TutorialFeedingVolumeActor.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API ATutorialFeedingVolumeActor : public AMonsterFeedingVolumeActor
{
	GENERATED_BODY()
	
public:
	ATutorialFeedingVolumeActor();

public:
	void InitMarkerWidget();

protected:
	virtual void BeginPlay() override;

	virtual void MonsterFed() override;

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
