/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "Structs/Heat/PlayerTypeDefinition.h"

// Add default functionality here for any IGameInformation functions that are not pure virtual.
FPlayerTypeDefinition::FPlayerTypeDefinition()
{
	PlayMode = EPlayMode::PM_NONE;
	PlayerDescription = "";
}
