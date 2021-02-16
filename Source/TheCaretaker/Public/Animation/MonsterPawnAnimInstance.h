/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MonsterPawnAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API UMonsterPawnAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsAngry;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsHungry;

public:
	virtual void NativeUpdateAnimation(float DeltaSeconds);
};
