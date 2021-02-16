/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuildHighScoresActor.generated.h"

UCLASS()
class THECARETAKER_EDITOR_API ABuildHighScoresActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ABuildHighScoresActor();

protected:
	UPROPERTY(EditAnywhere, SaveGame, BlueprintReadWrite, Category = "Game | Information")
	class UDataTable* PlayModeInformation;

	UPROPERTY(EditAnywhere, SaveGame, BlueprintReadWrite, Category = "Game | Information")
	class UDataTable* ExtraPlayModeInformation;

	UPROPERTY(EditAnywhere, SaveGame, BlueprintReadWrite, Category = "Game | Information")
	class UDataTable* LocalHighScore;

public:
	UFUNCTION(BlueprintCallable, CallInEditor)
	void BuildHighScore();
};
