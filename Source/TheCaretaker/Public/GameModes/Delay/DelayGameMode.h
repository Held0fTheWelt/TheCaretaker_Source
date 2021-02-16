/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DelayGameMode.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API ADelayGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ADelayGameMode();
	
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Finish")
	void Executed();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Finish")
	float TimeToFinish;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Finish")
	FName MapToLoad;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Finish")
	TArray<FName> MapToLoadSecond;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Finish")
	bool bUseSecondList;
private:
	void Finish();

	FTimerHandle DelayTimer;
};
