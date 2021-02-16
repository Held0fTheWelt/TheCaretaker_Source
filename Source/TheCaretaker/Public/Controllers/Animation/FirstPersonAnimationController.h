/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "FirstPersonAnimationController.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API UFirstPersonAnimationController : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;

	UFUNCTION(BlueprintCallable, Category = "Footsteps")
	void PlayFootStepSounds();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
	bool bIsMoving;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
	bool bIsInAir;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "Movement")
	TArray<class USoundBase*> LeftFootSteps;
	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "Movement")
	TArray<class USoundBase*> RightFootSteps;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	float PlayRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
	bool bIsRunning;
private:
	class ACharacter* PlayerCharacter;

	bool GetPlayerCharacter();
	FVector GetLocationForLinetrace(bool First);
};
