/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/MouseInteraction/MouseInteractionInterface.h"
#include "MonsterPawn.generated.h"

UCLASS()
class THECARETAKER_API AMonsterPawn : public ACharacter, public IMouseInteractionInterface
{
	GENERATED_BODY()

public:
	AMonsterPawn();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Outlining")
	class AMonsterFeedingVolumeActor* ConnectedVolume;

public:			
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void LeftMouseButtonClicked(ICollectableInterface* &CollectableRef);

	void SetConnectedVolume(class AMonsterFeedingVolumeActor* MonsterVolume);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Hungry"))
	void PlayHungryAnimation(bool Play);
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Angry"))
	void PlayAngerAnimation(bool Play);
	UPROPERTY(BlueprintReadWrite)
	bool bIsAngry;

};
