/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Enums/PartInformation/PartInformationEnum.h"
#include "Interfaces/DungeonMaster/DungeonMasterInterface.h"
#include "GameInstance/GameInstanceManager.h"
#include "PlayerStateInterface.generated.h"

UINTERFACE(MinimalAPI)
class UPlayerStateInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class THECARETAKER_API IPlayerStateInterface
{
	GENERATED_BODY()

public:
	virtual void AddItemSlot() = 0;
	virtual void RemoveItemSlot(bool IsGoodPickup) = 0;
};
