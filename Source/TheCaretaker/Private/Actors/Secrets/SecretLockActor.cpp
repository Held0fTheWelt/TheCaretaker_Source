/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "SecretLockActor.h"

#include "Engine/World.h"
#include "Interfaces/GameInstance/GameInstanceAccessoryInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Log/GlobalLog.h"

FSecretInformation::FSecretInformation()
{
	bIsLevelSecret = false;
	GameSecretCode = FString();
}

// Sets default values
ASecretLockActor::ASecretLockActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASecretLockActor::BeginPlay()
{
	Super::BeginPlay();


	
}

void ASecretLockActor::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	if (SecretSettings.bIsLevelSecret)
	{
		IGameInstanceAccessoryInterface* GameInstance = Cast<IGameInstanceAccessoryInterface>(UGameplayStatics::GetGameInstance(GetWorld()));

		if (GameInstance == nullptr)
		{
			LOG_WARNING(InitializationLog, "GameInstance was null ! This shouldn't happen !")
		}
		else
		{
			if (!GameInstance->IsSecretAccessible(SecretSettings.GameSecretCode))
			{
				LOG_WARNING(InitializationLog, "Secret is not accessible. Destroying!")
				if (SecretSettings.ActorsBoundToSecret.Num() == 0)
					return;

				for (auto Actor : SecretSettings.ActorsBoundToSecret)
				{
					if (Actor == nullptr)
					{
						continue;
					}
					Actor->Destroy();
				}
			}
		}
	}
}


