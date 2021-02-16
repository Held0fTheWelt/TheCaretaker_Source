/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Actors/Click/ClickActor.h"
#include "Interfaces/Fireplace/FireplaceInterface.h"
#include "FireplaceActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFirePlaceAction, AFireplaceActor*, Actor);

UCLASS()
class THECARETAKER_API AFireplaceActor : public AClickActor , public IFireplaceInterface
{
	GENERATED_BODY()
	
public:
	AFireplaceActor();

public:
	virtual void LeftMouseButtonClicked(ICollectableInterface*& CollectableRef) override;

	virtual void AddFireplaceListener() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Resource")
	void AddResourceEvent();
protected:
	virtual void BeginPlay() override;

protected:
	class USceneComponent* BurnSoundSpawnLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = Components)
	class UParticleSystemComponent* ParticleSystemComponent;
private:
	FFirePlaceAction FirePlaceAction;

	UPROPERTY(EditDefaultsOnly, Category = "Burn Sound")
	class USoundBase* BurnSound;

	FTimerHandle TimerHandle_FireParticle_Deactivate;

	void DeActivateParticleSystem();
};
