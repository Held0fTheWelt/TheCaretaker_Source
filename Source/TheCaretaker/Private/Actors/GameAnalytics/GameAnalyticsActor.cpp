// /* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "GameAnalyticsActor.h"

AGameAnalyticsActor::AGameAnalyticsActor()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

}

void AGameAnalyticsActor::BeginPlay()
{
	Super::BeginPlay();
	
	StartAnalytics();
}

void AGameAnalyticsActor::StartGameAnalyticsSession()
{
}

void AGameAnalyticsActor::StopGameAnalyicisSession()
{
	StopAnalytics();
}
