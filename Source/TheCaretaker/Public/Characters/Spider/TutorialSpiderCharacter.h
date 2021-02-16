/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Characters/Spider/SpiderCharacter.h"
#include "Interfaces/Tutorial/TutorialInterface.h"
#include "Interfaces/Tutorial/TutorialActorInterface.h"
#include "Structs/Tutorial/TutorialInformation.h"
#include "TutorialSpiderCharacter.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API ATutorialSpiderCharacter : public ASpiderCharacter
{
	GENERATED_BODY()
	
public:
	ATutorialSpiderCharacter();

protected:
	virtual void BeginPlay() override;

	virtual void NotifyOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Tutorial")
	TArray<FTutorialInformation> TutorialInformation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Tutorial")
	int32 IndexInTutorial;

private:
	ITutorialInterface* TutorialGameMode;
};
