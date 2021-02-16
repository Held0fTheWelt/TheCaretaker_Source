/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/DungeonMaster/DungeonMasterInterface.h"
#include "DungeonMasterCharacter.generated.h"

DECLARE_DELEGATE(FCharacterDead);

UCLASS()
class THECARETAKER_API ADungeonMasterCharacter : public ACharacter, public IDungeonMasterInterface
{
	GENERATED_BODY()

public:
	ADungeonMasterCharacter();

	FCharacterDead CharacterDead;

protected:
	UPROPERTY(VisibleAnywhere, Category = Components)
	class UAudioComponent* SoundComponent;

	UPROPERTY(VisibleAnywhere, Category = Components)
	class USphereComponent* SphereComponent;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	class USoundBase* RoarSound;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	class USoundBase* GrollSound;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	float GrollDelay;
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	void DelayedGroll();

	FTimerHandle TimerHandle_DelayGroll;

	// Geerbt über IDungeonMasterInterface
	virtual void SetCapsuleRadius(float Radius);

	UFUNCTION()
	void CanChangeAgain();

	bool bCanChange;
	FTimerHandle TimerHandle_DelayCapsuleChange;
};
