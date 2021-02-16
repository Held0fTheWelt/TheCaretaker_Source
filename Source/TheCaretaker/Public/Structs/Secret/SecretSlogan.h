/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Secret/SecretWord.h"
#include "Enums/PlayMode/PlayMode.h"
#include "SecretSlogan.generated.h"

// Is a Slogan to unlock a secret
USTRUCT(BlueprintType)
struct THECARETAKER_API FSecretSlogan
{
	GENERATED_BODY()

public:
	FSecretSlogan(); 
	FSecretSlogan(FString NewSlogan, FText NewMessage, int32 NewIndex, int32 NewPoints, EPlayMode NewEpisode);

public:
	UPROPERTY(VisibleAnywhere)
	FString Slogan;
	UPROPERTY(EditAnywhere)
	FText Message;
	UPROPERTY(VisibleAnywhere)
	TArray<FSecretWord> ConnectedSecretWords;
	UPROPERTY(VisibleAnywhere)
	int32 SloganIndex;
	UPROPERTY(VisibleAnywhere)
	int32 LevelPointsToSolve;
	UPROPERTY(VisibleAnywhere)
	EPlayMode Episode;
};