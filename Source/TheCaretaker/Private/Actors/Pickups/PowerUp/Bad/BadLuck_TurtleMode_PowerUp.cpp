/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "BadLuck_TurtleMode_PowerUp.h"

#include "Interfaces/Achievements/AchievementCountInterface.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "Interfaces/Characters/Character/CharacterInterface.h"

#pragma region Constructor
ABadLuck_TurtleMode_PowerUp::ABadLuck_TurtleMode_PowerUp()
{
	SpeedMultiplier = .2f;
}
#pragma endregion

#pragma region Activated
void ABadLuck_TurtleMode_PowerUp::Activated(AActor* OtherActor)
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

	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), PowerUpSound, CharacterInterface->GetLocation());

}
#pragma endregion

#pragma region Expired
void ABadLuck_TurtleMode_PowerUp::Expired()
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