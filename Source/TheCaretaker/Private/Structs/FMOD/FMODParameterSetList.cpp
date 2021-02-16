/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "Structs/FMOD/FMODParameterSetList.h"

// Add default functionality here for any IFMODParameterSet functions that are not pure virtual.
FMODParameterSet::FMODParameterSet()
{
	ParameterName = EName::NAME_None;
	ParameterType = EFMODParameterType::FMOD_PT_NONE;
	SoundChangeValue = 0;
}

FMODParameterSet::FMODParameterSet(FName Name, EFMODParameterType Type, float ChangeValue)
{
	ParameterName = Name;
	ParameterType = Type;
	SoundChangeValue = ChangeValue;
}

FName FMODParameterSetList::GetParameterName(EFMODParameterType ParameterType)
{
	for (auto Set : ParameterSet)
	{
		if (Set.ParameterType == ParameterType)
		{
			return Set.ParameterName;
		}
	}

	return EName::NAME_None;
}
