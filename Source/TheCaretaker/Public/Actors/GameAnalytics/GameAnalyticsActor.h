// /* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/GameAnalytics/GameAnalyticsInterface.h"
#include "GameAnalyticsActor.generated.h"

UCLASS()
class THECARETAKER_API AGameAnalyticsActor : public AActor, public IGameAnalyticsInterface
{
	GENERATED_BODY()
	
public:	
	AGameAnalyticsActor();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void StartAnalytics();
	UFUNCTION(BlueprintImplementableEvent)
	void StopAnalytics();

public:
	virtual void StartGameAnalyticsSession() override;

	virtual void StopGameAnalyicisSession() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bSessionRunning;

};
