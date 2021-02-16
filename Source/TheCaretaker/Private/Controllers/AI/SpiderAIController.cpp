/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "Controllers/AI/SpiderAIController.h"

#include "Log/GlobalLog.h"


void ASpiderAIController::SetGamePaused(bool SetGamePaused)
{	
	bIsPaused = SetGamePaused;
}

bool ASpiderAIController::IsPaused() const
{
	return bIsPaused;
}
