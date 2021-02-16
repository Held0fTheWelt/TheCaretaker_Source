/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Structs/PlayMode/PlayModeInformation.h"
#include "Structs/PlayMode/PlayModeInformationTranslation.h"
#include "DataBaseTranslator.generated.h"

UCLASS()
class THECARETAKER_EDITOR_API ADataBaseTranslator : public AActor
{
	GENERATED_BODY()
	
public:	
	ADataBaseTranslator();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UDataTable* PlayModeInformationTranslation;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UDataTable* PlayModeInformation;

protected:
	UFUNCTION(BlueprintCallable, CallInEditor)
	void TranslateData();
	
	UFUNCTION(BlueprintCallable, CallInEditor)
	void RetranslateData();

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateTranslation(const TArray<FPlayModeInformationTranslation>& PlayModeTranslation);
	
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateReTranslation(const TArray<FName>& Names, const TArray<FPlayModeInformation>& PlayModeInfo);
};
