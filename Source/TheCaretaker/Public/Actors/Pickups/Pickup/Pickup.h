/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Pickup/PickupInterface.h"
#include "Pickup.generated.h"

UCLASS(Abstract)
class THECARETAKER_API APickup : public AActor, public IPickupInterface
{
	GENERATED_BODY()
	
public:	
	APickup();

public:
	UPROPERTY(EditAnywhere, Category = "Pickup")
	TSubclassOf<class APowerUp> CurrentPowerUpClass;

protected:

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USphereComponent* TriggerVolume;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UDecalComponent* Decals;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UParticleSystemComponent* ParticleSystemComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Network")
	bool bUsesMultiplayer;

	UPROPERTY(EditAnywhere, Category = "Pickup")
	bool bSpawnOnBeginPlay;

	UPROPERTY(EditDefaultsOnly, Category = "Pickup")
	float CoolDownDuration;

	UPROPERTY(EditAnywhere, Category = "Pickup")
	bool ReactsOnAllPlayers;

	UPROPERTY(EditAnywhere, Category = "Pickup")
	float ParticleDelayDuration;

	class APowerUp* CurrentPowerUpActor;

public:	
	virtual void NotifyActorBeginOverlap(class AActor* OtherActor) override;

private:	
	void PlayParticleEffect();

public:
	virtual void Respawn();

private:
	FTimerHandle TimerHandle_RespawnPickup;
	FTimerHandle TimerHandle_ParticleEffect;

	bool bOnStart;
};
