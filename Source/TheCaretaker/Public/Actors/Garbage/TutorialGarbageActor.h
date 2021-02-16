/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Actors/Garbage/GarbageActor.h"
#include "Interfaces/Tutorial/TutorialInterface.h"
#include "Interfaces/Tutorial/TutorialActorInterface.h"
#include "Structs/Tutorial/TutorialInformation.h"
#include "TutorialGarbageActor.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API ATutorialGarbageActor : public AGarbageActor, public ITutorialActorInterface
{
	GENERATED_BODY()

public:
	ATutorialGarbageActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void LeftMouseClicked() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Tutorial")
	TArray<FTutorialInformation> TutorialInformation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Tutorial")
	int32 IndexInTutorial;

private:
	ITutorialInterface* TutorialGameMode;

	class ACaretakerPlayerState* PlayerState;
	
};
