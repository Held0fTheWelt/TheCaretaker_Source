/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Actors/Trap/TrapActor.h"
#include "Interfaces/Tutorial/TutorialInterface.h"
#include "Interfaces/Tutorial/TutorialActorInterface.h"
#include "Structs/Tutorial/TutorialInformation.h"
#include "TutorialTrapActor.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API ATutorialTrapActor : public ATrapActor
{
	GENERATED_BODY()

public:
	ATutorialTrapActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void LeftMouseButtonClicked(ICollectableInterface*& CollectableRef) override;

	virtual void TrapSolved() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Tutorial")
		TArray<FTutorialInformation> TutorialInformation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Tutorial")
		int32 IndexInTutorial;

private:
	ITutorialInterface* TutorialGameMode;
};
