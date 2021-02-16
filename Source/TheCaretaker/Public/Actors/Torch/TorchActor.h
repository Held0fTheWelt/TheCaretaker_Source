// /* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/MouseInteraction/MouseInteractionInterface.h"
#include "Interfaces/GameInstance/GameInstanceAccessoryInterface.h"
#include "TorchActor.generated.h"

UCLASS()
class THECARETAKER_API ATorchActor : public AActor, public IMouseInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATorchActor();

protected:
	UPROPERTY(EditDefaultsOnly)
	class USoundBase* BlockedSound;

	UPROPERTY(EditDefaultsOnly)
	class USoundBase* MechanismSound;

	UPROPERTY(EditDefaultsOnly)
	class USoundBase* ReloadedSound;
	
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<class APowerUp>> PowerUpsToSwitch;

	UPROPERTY(EditAnywhere)
	class ASingleObjectPickup* PickupToSwitch;

	UPROPERTY(VisibleAnywhere)
	int32 CurrentPowerUpInUse;

	UPROPERTY(EditAnywhere)
	float TimeToReload;

protected:
	virtual void BeginPlay() override;

public:
	virtual void LeftMouseButtonClicked(ICollectableInterface*& CollectableRef);

private:
	void PlayBlockedSound();
	void PlayMechanismSound();
	void PlayReloadedSound();
	void CountPowerUp();
	bool ChangePowerUp();

private:
	IGameInstanceAccessoryInterface* GameInstanceAccessory;

	UPROPERTY()
	bool bReloaded;

	UPROPERTY()
	bool bUsingTorchAsSwitch;

	FTimerHandle TimerHandle_Reload;

	void Reloaded();
};
