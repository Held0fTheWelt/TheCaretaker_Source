/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/WinCondition/WinConditionVolumeInterface.h"
#include "WinConditionActor.generated.h"

DECLARE_DELEGATE(FWinConditionUpdate);

UCLASS()
class THECARETAKER_API AWinConditionActor : public AActor, public IWinConditionVolumeInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWinConditionActor();

	FWinConditionUpdate WinConditionUpdate;

	virtual bool ShouldWaitForEndOfTime() const override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	/** TriggerVolume to activate and deactivate ChestBehaviour */
	UPROPERTY(VisibleAnywhere, Category = "TriggerBox")
	class UBoxComponent* TriggerVolume;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "Win Condition")
	bool bShouldWaitUntilEndOfTime;

private:
	bool bIsInSafeZone;

private:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	// Inherited via IWinConditionVolumeInterface
	virtual bool IsInSafeZone() const;
	virtual void CallWinConditionUpdate();
};
