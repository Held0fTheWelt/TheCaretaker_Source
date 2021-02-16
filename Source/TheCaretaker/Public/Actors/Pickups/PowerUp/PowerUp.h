/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Pickups/PickupActorInterface.h"
#include "PowerUp.generated.h"

UCLASS()
class THECARETAKER_API APowerUp : public AActor, public IPickupActorInterface
{
	GENERATED_BODY()
	
public:	
	APowerUp();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UPointLightComponent* Light;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class URotatingMovementComponent* RotatingComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Network")
	bool bUsesMultiplayer;

	/* Time between PowerUp Ticks*/
	UPROPERTY(EditDefaultsOnly, Category = "PowerUps")
	float PowerUpInterval;

	/* Total Times we apply the PowerUp Effect */
	UPROPERTY(EditDefaultsOnly, Category = "PowerUps")
	int32 TotalNumberOfTicks;

	UPROPERTY(EditDefaultsOnly, Category = "PowerUps | Sound")
	class USoundBase* PowerUpSound;

	UPROPERTY(EditDefaultsOnly, Category = "PowerUps | Sound")
	class USoundBase* PowerPulseSound;
	
	UPROPERTY(EditDefaultsOnly, Category = "PowerUps | Sound")
	class USoundBase* PowerDownSound;
	
	UPROPERTY(VisibleAnywhere, Category = "PowerUps")
	int32 TicksLeft;

	UPROPERTY(Replicated)
	AActor* ActorToInvoke;

public:		
	UFUNCTION(BlueprintImplementableEvent, Category="PowerUps")
	void OnExpired() ;

	UFUNCTION(BlueprintImplementableEvent, Category = "PowerUps")
	void OnActivated(class AActor* OverlapActor);

	UFUNCTION(BlueprintImplementableEvent, Category = "PowerUps")
	void OnTick();

	UFUNCTION(BlueprintImplementableEvent, Category = "PowerUps")
	void OnPowerUpStateChanged(bool bNewIsActive);

	virtual void Expired() override;

	virtual void Activated(class AActor* OtherActor) override;

	virtual void OnTickPowerUp() override;
private:
	FTimerHandle TimerHandle_PowerUpTick;	

	UPROPERTY(ReplicatedUsing = OnRep_PowerUpActive)
	bool bIsPowerUpActive;

	UFUNCTION()
	void OnRep_PowerUpActive();


	virtual void GetLifetimeReplicatedProps(class TArray<class FLifetimeProperty> &OutLifetimeProps)const override;


};
