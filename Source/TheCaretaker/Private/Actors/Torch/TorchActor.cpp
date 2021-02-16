// /* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "TorchActor.h"

#include "TimerManager.h"

#include "Actors/Pickups/PowerUp/PowerUp.h"
#include "Actors/Pickups/Pickup/SingleObjectPickup.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"
#include "Interfaces/GameInstance/GameInstanceAccessoryInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Log/GlobalLog.h"

ATorchActor::ATorchActor()
{
	BlockedSound = nullptr;
	MechanismSound = nullptr;
	ReloadedSound = nullptr;

	PowerUpsToSwitch = TArray<TSubclassOf<APowerUp>>();
	PickupToSwitch = nullptr;
	
	GameInstanceAccessory = nullptr;

	bUsingTorchAsSwitch = false;
	CurrentPowerUpInUse = 0;

	TimeToReload = 5.f;

	bReloaded = false;
}

void ATorchActor::BeginPlay()
{
	Super::BeginPlay();
	//
	//if (PowerUpInformationList == nullptr)
	//{
	//	PowerUpsToSwitch.Empty();
	//	PickupToSwitch = nullptr;
	//	return;
	//}

	GameInstanceAccessory = Cast<IGameInstanceAccessoryInterface>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (GameInstanceAccessory->IsPart2() && GameInstanceAccessory->GetPlayMode() == EPlayMode::PM_DEFAULT)
	{
		bUsingTorchAsSwitch = true;
		bReloaded = true;

		if (PowerUpsToSwitch.Num() > 0)
		{

			for (int32 i = PowerUpsToSwitch.Num() - 1; i >= 0; i--)
			{
				if (PowerUpsToSwitch[i] == nullptr)
				{
					PowerUpsToSwitch.RemoveAt(i);
				}

				if (!GameInstanceAccessory->IsPowerUpAvailable(PowerUpsToSwitch[i]))
				{
					PowerUpsToSwitch.RemoveAt(i);
				}
			}		
		}
	}
}

void ATorchActor::LeftMouseButtonClicked(ICollectableInterface*& CollectableRef)
{
	if (!bUsingTorchAsSwitch)
		return;

	if (bReloaded == false)
		return;


	if (PickupToSwitch == nullptr)
	{
		PlayBlockedSound();
		return;
	}

	if (PowerUpsToSwitch.Num() == 0)
	{
		PlayBlockedSound();
		return;
	}

	CountPowerUp();

	if (ChangePowerUp())
	{
		bReloaded = false;

		PlayMechanismSound();

		GetWorld()->GetTimerManager().SetTimer(TimerHandle_Reload, this, &ATorchActor::Reloaded, TimeToReload, false);
	}
}

void ATorchActor::PlayBlockedSound()
{
	if (BlockedSound == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "BlockedSound was null ! Set it up in the Blueprint")
	}
	else
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), BlockedSound, GetActorLocation());
	}
}

void ATorchActor::PlayMechanismSound()
{
	if (MechanismSound == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "MechanismSound was null ! Set it up in the Blueprint")
	}
	else
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), MechanismSound, GetActorLocation());
	}
}

void ATorchActor::PlayReloadedSound()
{
	if (ReloadedSound == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "ReloadedSound was null ! Set it up in the Blueprint")
	}
	else
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ReloadedSound, GetActorLocation());
	}
}

void ATorchActor::CountPowerUp()
{
	CurrentPowerUpInUse++;

	if (CurrentPowerUpInUse >= PowerUpsToSwitch.Num())
	{
		CurrentPowerUpInUse = 0;
	}

	if (PowerUpsToSwitch[CurrentPowerUpInUse] == nullptr)
	{
		if (CurrentPowerUpInUse == 0)
			return;

		CountPowerUp();
	}
}

bool ATorchActor::ChangePowerUp()
{
	if (PickupToSwitch == nullptr || PowerUpsToSwitch.Num() < CurrentPowerUpInUse - 1 || PowerUpsToSwitch.Num() == 0)
	{
		LOG_WARNING(RuntimeExecutionLog, "PickupToSwitch was null ! This shouldn't happen !")
		return false;
	}
	if (PowerUpsToSwitch.Num() == 0)
	{
		LOG_WARNING(RuntimeExecutionLog, "PickupToSwitch was null ! This shouldn't happen !")
		return false;
	}
	if (PowerUpsToSwitch.Num() < CurrentPowerUpInUse - 1)
	{
		LOG_WARNING(RuntimeExecutionLog, "PickupToSwitch was null ! This shouldn't happen !")
		return false;
	}

	PickupToSwitch->PowerUpClass = PowerUpsToSwitch[CurrentPowerUpInUse];

	return true;
}

void ATorchActor::Reloaded()
{
	bReloaded = true;
	PlayReloadedSound();
}
