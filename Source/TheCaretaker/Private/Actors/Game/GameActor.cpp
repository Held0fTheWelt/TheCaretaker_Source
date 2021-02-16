/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "Actors/Game/GameActor.h"


AGameActor::AGameActor()
{
	PrimaryActorTick.bCanEverTick = true;
}


void AGameActor::StopGame()
{
	bGameIsStarted = false;
}

void AGameActor::NewGame()
{
	bGameIsStarted = true;
}

