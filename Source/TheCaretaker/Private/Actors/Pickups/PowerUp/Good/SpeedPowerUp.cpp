/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "Actors/Pickups/PowerUp/Good/SpeedPowerUp.h"

#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "Interfaces/Achievements/AchievementCountInterface.h"
#include "Interfaces/Characters/Character/CharacterInterface.h"
#include "Log/GlobalLog.h"

#pragma region Constructor
ASpeedPowerUp::ASpeedPowerUp()
{
	SpeedMultiplier = 5;
}
#pragma endregion

#pragma region Activated
void ASpeedPowerUp::Activated(AActor* OtherActor)
{
	Super::Activated(OtherActor);

	if (ActorToInvoke == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Other Actor was nullptr in SpeedUp Activated"));
		return;
	}

	ICharacterInterface* CharacterInterface = Cast<ICharacterInterface>(ActorToInvoke);
	
	if (CharacterInterface == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("CharacterInterface was nullptr in SpeedUp Activated"));
		return;
	}
		
	CharacterInterface->SetSpeedMultiplier(SpeedMultiplier);

	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), PowerUpSound,CharacterInterface->GetLocation());

	IAchievementCountInterface* AchievementInstance = Cast<IAchievementCountInterface>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (AchievementInstance == nullptr)
	{
		LOG_WARNING(RuntimeExecutionLog, "Could not cast GameInstance to AchievementCountInterface. This shouldn't happen!")
	}
	else
	{
		AchievementInstance->CountAchievement(EAchievementType::AT_PICKUP);
	}

}
#pragma endregion

#pragma region Expired
void ASpeedPowerUp::Expired()
{
	ICharacterInterface* CharacterInterface = Cast<ICharacterInterface>(ActorToInvoke);

	if (CharacterInterface == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("CharacterInterface was nullptr in SpeedUp Activated"));
		return;
	}

	CharacterInterface->SetSpeedMultiplier(1);

	Super::Expired();
}
#pragma endregion