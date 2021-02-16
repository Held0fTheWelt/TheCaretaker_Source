/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "Actors/Pickups/PowerUp/Good/HealthPowerUp.h"

#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

AHealthPowerUp::AHealthPowerUp()
{
	HealAmount = 20.f;
}

void AHealthPowerUp::OnTickPowerUp()
{
	Super::OnTickPowerUp();
	   	 
	//if (HealthComponent == nullptr)
	//{
	//	if (ActorToInvoke == nullptr)
	//	{
	//		UE_LOG(LogTemp, Warning, TEXT("Other Actor was nullptr in HealthPowerUp Tick"));
	//		return;
	//	}

	//	HealthComponent = Cast<UHealthComponent>(ActorToInvoke->GetComponentByClass(UHealthComponent::StaticClass()));
	//	if (HealthComponent == nullptr)
	//	{
	//		UE_LOG(LogTemp, Warning, TEXT("HealthComponent was nullptr in HealthPowerUp Tick"));
	//		return;
	//	}
	//}
	//HealthComponent->Heal(HealAmount);
}
