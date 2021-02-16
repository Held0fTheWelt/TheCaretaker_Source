/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "Interfaces/Game/GameFunctionsInterface.h"
#include "GameActor.generated.h"

UCLASS()
class THECARETAKER_API AGameActor : public ATargetPoint, public IGameFunctionsInterface
{
	GENERATED_BODY()
	
public:	
	AGameActor();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Monster")
	bool bGameIsStarted;

	// Geerbt über IGameFunctionsInterface
	virtual void StopGame() override;
	// Geerbt über IGameFunctionsInterface
	virtual void NewGame() override;
};
