// /* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "RandomBadPickup.h"

#include "Engine/World.h"
#include "Engine/GameInstance.h"
#include "Interfaces/GameInstance/GameInstanceAccessoryInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Log/GlobalLog.h"
#include "Actors/Pickups/PowerUp/PowerUp.h"

ARandomBadPickup::ARandomBadPickup()
{
	PowerUpSelection = TArray<TSubclassOf<APowerUp>>();
	DeathPowerDownProbability = .5f;
}

void ARandomBadPickup::Respawn()
{
	ChooseRandomPowerUp();

	Super::Respawn();
}

void ARandomBadPickup::BeginPlay()
{
	TArray<FPowerUpList> PowerUpSelectionList = ReadPowerUpInformation();

	PullPowerUpInformation(PowerUpSelectionList);

	ChooseRandomPowerUp();

	Super::BeginPlay();
}

TArray<FPowerUpList> ARandomBadPickup::ReadPowerUpInformation()
{
	TArray<FPowerUpList> PowerUpSelectionList = TArray<FPowerUpList>();
	
	if (PickupInformation == nullptr)
	{
		LOG_WARNING(InitializationLog, "Random Bad Pickup Information needs setup Datatable, before ordinary usage")
	}
	else
	{
		static const FString ContextString(TEXT("PickupInformation"));

		TArray<FName> RowNames = PickupInformation->GetRowNames();
		for (int32 i = 0; i < RowNames.Num(); i++)
		{
			FPowerUpList* PowerUp = PickupInformation->FindRow<FPowerUpList>(RowNames[i], ContextString, true);
			if (PowerUp == nullptr)
			{
				LOG_WARNING(InitializationLog, "Power Up was null. Please check DataTable")
			}
			else
			{
				if (PowerUp->PowerUpType == EPowerUpType::PUT_BAD)
				{
					PowerUpSelectionList.Add(*PowerUp);
				}
			}
		}
	}
	return PowerUpSelectionList;
}

void ARandomBadPickup::ChooseRandomPowerUp()
{
	if (PowerUpSelection.Num() == 0)
	{
		LOG_WARNING(RuntimeExecutionLog, "Could not spawn, because PowerUpSelection was null !Retrying.")
		TArray<FPowerUpList> PowerUpSelectionList = ReadPowerUpInformation();

		PullPowerUpInformation(PowerUpSelectionList);
		if (PowerUpSelection.Num() == 0)
		{
			LOG_WARNING(RuntimeExecutionLog, "Could not spawn, because PowerUpSelection was null !")
			return;
		}
	}

	float Probability = FMath::RandRange(0.f, 1.f);
	UE_LOG(LogTemp, Display, TEXT("Probability for Death Pickup: %f with perception of %f%"), Probability, DeathPowerDownProbability);
	if ( Probability >= DeathPowerDownProbability)
	{
		CurrentPowerUpClass = PowerUpSelection[FMath::RandRange(0, PowerUpSelection.Num() - 1)];
	}
	else
	{
		CurrentPowerUpClass = DeathPowerDown;
	}

}

void ARandomBadPickup::PullPowerUpInformation(const TArray<FPowerUpList> &PowerUpSelectionList)
{
	if (PowerUpSelectionList.Num() == 0)
	{
		LOG_WARNING(InitializationLog,"Could not Pull information, because PowerUpSelection Array was count 0!")
	}
	else
	{
		IGameInstanceAccessoryInterface* GameInstanceInterface = Cast<IGameInstanceAccessoryInterface>(UGameplayStatics::GetGameInstance(GetWorld()));

		if (GameInstanceInterface == nullptr)
		{
			LOG_WARNING(InitializationLog, "Could not cast GameInstance ! This shouldn't happen !")
		}
		else
		{
			TArray<int32> LevelPointsPerSlogan = GameInstanceInterface->GetSlogansIndicesLevelpoints();
			int32 CurrentLevelPoints = GameInstanceInterface->GetCurrentLevelPoints();

			for (int32 i = 0; i < PowerUpSelectionList.Num(); i++)
			{
				if (PowerUpSelectionList[i].SecretSloganIndexBounding <= LevelPointsPerSlogan.Num() - 1)
				{
					if (LevelPointsPerSlogan[PowerUpSelectionList[i].SecretSloganIndexBounding] <= CurrentLevelPoints)
					{
						if (PowerUpSelectionList[i].SelectionType != EPowerUpSelection::PUS_BAD_DEATH)
						{
							PowerUpSelection.Add(PowerUpSelectionList[i].PowerUp);
						}
					}					
				}
				else
				{
					LOG_WARNING(InitializationLog, "SecretSloganIndex Bounding in PowerUpSelection too high")
				}
			}
		}
	}
}

