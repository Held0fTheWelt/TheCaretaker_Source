/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#include "Pawns/Monster/MonsterPawn.h"

#include "Actors/Monsters/MonsterFeedingVolumeActor.h"
#include "Log/GlobalLog.h"


AMonsterPawn::AMonsterPawn()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AMonsterPawn::BeginPlay()
{
	Super::BeginPlay();	
}

void AMonsterPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMonsterPawn::LeftMouseButtonClicked(ICollectableInterface* &CollectableRef)
{
	if (ConnectedVolume != nullptr)
	{
		ConnectedVolume->LeftMouseButtonClicked(CollectableRef);
	}
	LOG_DISPLAY(RuntimeExecutionLog,"Clicked Monster")
}

void AMonsterPawn::SetConnectedVolume(AMonsterFeedingVolumeActor* MonsterVolume)
{
	ConnectedVolume = MonsterVolume;
}

