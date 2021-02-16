/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#include "Structs/PowerUp/PowerUpList.h"

FPowerUpList::FPowerUpList()
{
	PowerUpType = EPowerUpType::PUT_NONE;
	PowerUp = nullptr;
	SecretSloganIndexBounding = 0;
	SelectionType = EPowerUpSelection::PUS_NONE;
}
