/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FinishedTimedGameMode.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API AFinishedTimedGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Finish")
	FName MapToLoad;

	UFUNCTION(BlueprintCallable, Category = "Credits")
	void Finish();

private:
	bool bPlaySecrets;
};
