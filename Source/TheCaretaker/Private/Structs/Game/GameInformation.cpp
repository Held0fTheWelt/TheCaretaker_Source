/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "Structs/Game/GameInformation.h"

// Add default functionality here for any IGameInformation functions that are not pure virtual.
FGameInformation::FGameInformation()
{

}

TArray<FLevelInformation> FGameInformation::GetLevelsInGame() const
{
	return LevelsInGame;
}
