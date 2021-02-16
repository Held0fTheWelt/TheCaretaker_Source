/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "Structs/Secret/SecretSlogan.h"

FSecretSlogan::FSecretSlogan(FString NewSlogan, FText NewMessage, int32 NewIndex, int32 NewPoints, EPlayMode NewEpisode)
{
	Slogan = NewSlogan;
	Message = NewMessage;
	SloganIndex = NewIndex;
	LevelPointsToSolve = NewPoints;
	Episode = NewEpisode;
}
FSecretSlogan::FSecretSlogan()
{
	Slogan = FString();
	Message = FText::FromString("");
	SloganIndex = 0;
	LevelPointsToSolve = 0;
	Episode = EPlayMode::PM_NONE;
}