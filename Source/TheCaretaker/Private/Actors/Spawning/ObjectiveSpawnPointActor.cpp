/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#include "Actors/Spawning/ObjectiveSpawnPointActor.h"

#include "Components/StaticMeshComponent.h"
#include "Components/BillboardComponent.h"

#pragma region Constructor
AObjectiveSpawnPointActor::AObjectiveSpawnPointActor() 
{ 	
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	if (PreviewMesh == nullptr)
		PreviewMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("PreviewMesh"));

	// This is a query only trigger volume
	PreviewMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	PreviewMesh->SetupAttachment(RootComponent);

	Part = EPartInformation::EPI_NONE;

	// Comment out to Build the Game !
	//GetSpriteComponent()->SetRelativeLocation(FVector(0.f, 0.f, 50.f));
}
#pragma endregion

#pragma region Get SpawnPoint Type
ESpawnPointType AObjectiveSpawnPointActor::GetSpawnPointType() const
{
	return SpawnPointType;
}
#pragma endregion

#pragma region Get Current Transform
FTransform AObjectiveSpawnPointActor::GetCurrentTransform() const
{
	return GetTransform();
}
EPartInformation AObjectiveSpawnPointActor::GetCurrentPart() const
{
	return Part;
}
#pragma endregion

void AObjectiveSpawnPointActor::SetSpawned(bool Spawned)
{
	bSpawned = Spawned;
}

bool AObjectiveSpawnPointActor::GetIsSpawned() const
{
	return bSpawned;
}