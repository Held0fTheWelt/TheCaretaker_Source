/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "Structs/Anger/MonsterAnger.h"

// Add default functionality here for any IMonsterAnger functions that are not pure virtual.

FMonsterAnger::FMonsterAnger()
{
	MonsterName = EName::NAME_None;
	Anger = 0;
}

const FString FMonsterAnger::GetName()
{
	return MonsterName.ToString();
}

void FMonsterAnger::SetAnger(float NewAnger)
{
	Anger = NewAnger;
}
