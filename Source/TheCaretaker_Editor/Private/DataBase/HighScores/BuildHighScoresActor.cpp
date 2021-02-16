/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "BuildHighScoresActor.h"

#include "Log/GlobalLog.h"

ABuildHighScoresActor::ABuildHighScoresActor()
{	
	PrimaryActorTick.bCanEverTick = false;

}

void ABuildHighScoresActor::BuildHighScore()
{
	if (PlayModeInformation == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "PlayModeInformation were null. Please")
			return;
	}

	/*if (ExtraPlayModeInformation == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "ExtraPlayModeInformation were null. Please")
			return;
	}*/

	if (LocalHighScore == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "LocalHighScore were null. Please")
			return;
	}
}
