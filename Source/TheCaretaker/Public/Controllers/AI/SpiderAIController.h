/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Interfaces/Pause/PauseGameInterface.h"
#include "SpiderAIController.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API ASpiderAIController : public AAIController, public IPauseGameInterface
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Pause")
	bool bIsPaused;
		
public:
	virtual void SetGamePaused(bool SetGamePaused) override;

	virtual bool IsPaused() const;

};
