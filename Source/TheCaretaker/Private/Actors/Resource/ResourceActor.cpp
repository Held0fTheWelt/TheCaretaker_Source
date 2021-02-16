/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "Actors/Resource/ResourceActor.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Log/GlobalLog.h"
#include "States/Player/CaretakerPlayerState.h"

#pragma region Begin Play
void AResourceActor::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<AActor*>GameStateActors;
	// Pick only Actors with Interface, instead of iterating whole World:
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACaretakerPlayerState::StaticClass(), GameStateActors);
	for (const auto& Actor : GameStateActors) {

		ACaretakerPlayerState* PlayerStateActor = Cast<ACaretakerPlayerState>(Actor);
		if (PlayerStateActor != nullptr)
		{
			if (ResourceType == EResourceType::RT_GOLD)
			{
				ResourceCollected.AddDynamic(PlayerStateActor, &ACaretakerPlayerState::AddGold);
			}
			else if (ResourceType == EResourceType::RT_MEAT)
			{
				ResourceCollected.AddDynamic(PlayerStateActor, &ACaretakerPlayerState::AddFood);
			}

		}
	}


}
#pragma endregion

#pragma region Left MouseButton Clicked
void AResourceActor::LeftMouseButtonClicked(ICollectableInterface*& CollectableRef)
{
	if (ResourceCollected.IsBound())
	{
		ResourceCollected.Broadcast(AmountToAdd, this);
		LOG_DISPLAY(RuntimeExecutionLog, "Resource added!");
	}
	else
	{
		LOG_WARNING(RuntimeExecutionLog, "Could not add Resource, because Event is not bound!");
	}
}
#pragma endregion