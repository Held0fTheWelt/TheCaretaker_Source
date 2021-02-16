/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "Structs/Difficulty/DifficultyMultiplier.h"


FDifficultyMultiplier::FDifficultyMultiplier()
{
	// Mode 1
	Modifier.Add(1.f);
	// Mode 2
	Modifier.Add(1.5f);
	// Mode 3
	Modifier.Add(1.75f);
	// Mode 4
	Modifier.Add(2.f);
	// Mode 5
	Modifier.Add(2.15f);
	// Mode 6
	Modifier.Add(2.25f);
	// Mode 7
	Modifier.Add(2.3f);
	// Mode 8
	Modifier.Add(2.325f);
	// Mode 9
	Modifier.Add(2.375f);
}
