// /* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "SpiderWebActor.h"

#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"
#include "Interfaces/GameInstance/GameInstanceAccessoryInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Log/GlobalLog.h"

ASpiderWebActor::ASpiderWebActor()
{

	if(!Root)
		Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	RootComponent = Root;

	if (!Mesh)
		Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
		
	Mesh->SetupAttachment(Root);

	DifficultyToUnlock = -1;
	LevelPointsToUnlock = -1;

}

void ASpiderWebActor::BeginPlay()
{
	Super::BeginPlay();

	IGameInstanceAccessoryInterface* GameInstanceInterface = Cast<IGameInstanceAccessoryInterface>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (GameInstanceInterface == nullptr)
	{
		LOG_WARNING(InitializationLog, "GameInstance not found ! This shouldn't happen !")
	}
	else
	{
		if (GameInstanceInterface->GetCurrentLevelPoints() < LevelPointsToUnlock && LevelPointsToUnlock != -1
		||  GameInstanceInterface->GetCurrentDifficulty() < DifficultyToUnlock && DifficultyToUnlock != -1)
		{
			//LOG_WARNING(InitializationLog, "Destroying !")
			Destroy();
		}
		else
		{
			//UE_LOG(LogTemp, Warning, TEXT("Showing Spiderweb. Has more than %d Levelpoints"), LevelPointsToUnlock);
		}
	}
}
