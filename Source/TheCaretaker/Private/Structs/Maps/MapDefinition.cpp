/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "MapDefinition.h"

// Add default functionality here for any IMapDefinition functions that are not pure virtual.
FMapDefinition::FMapDefinition()
{
	LevelName_Menu = FName("Map_Menu");
	LevelName_Load = FName("Map_Load");
	LevelName_Tutorial = FName("Map_Tutorial");
	LevelName_Credits = FName("Map_Credits");
}