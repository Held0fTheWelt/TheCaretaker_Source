/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "SpawnVolumeFloorActor.h"

#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"

ASpawnVolumeFloorActor::ASpawnVolumeFloorActor()
{
	PrimaryActorTick.bCanEverTick = false;

	if (Scene == nullptr)
		Scene = CreateDefaultSubobject<USceneComponent>(FName("RootSceneComponent"));

	RootComponent = Scene;

	if (Floor == nullptr)
		Floor = CreateDefaultSubobject<UStaticMeshComponent>(FName("FloorComponent"));

	Floor->SetupAttachment(RootComponent);

	PartInformation = EPartInformation::EPI_NONE;
}

EPartInformation ASpawnVolumeFloorActor::GetPartOfLevel() const
{
	return PartInformation;
}

FVector ASpawnVolumeFloorActor::GetLocation() const
{
	return GetActorLocation() + FVector(250,250,0);
}
