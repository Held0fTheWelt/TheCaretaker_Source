/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "Structs/Secret/SecretSloganList.h"

FSecretSloganList::FSecretSloganList()
{
	Slogans.Add(FSecretSlogan("Shift the night", FText::FromString("New GameMode Achieved !"), 0, 0, EPlayMode::PM_CLASSIC));
	Slogans.Add(FSecretSlogan("Let me compete", FText::FromString("Highscores opened !"), 1, 0, EPlayMode::PM_CLASSIC));
	Slogans.Add(FSecretSlogan("Give me more", FText::FromString("Extra Levels added !"), 2, 33, EPlayMode::PM_CLASSIC));
	Slogans.Add(FSecretSlogan("Lightning Jack", FText::FromString("Speed Pickups Unlocked !"), 3, 15, EPlayMode::PM_DEFAULT));
	Slogans.Add(FSecretSlogan("The invisible cape", FText::FromString("Invisibility Unlocked !"), 4, 25, EPlayMode::PM_DEFAULT));
	Slogans.Add(FSecretSlogan("On light feet", FText::FromString("Noise Pickups Unlocked !"), 5, 27, EPlayMode::PM_DEFAULT));
	Slogans.Add(FSecretSlogan("Give me a second", FText::FromString("Time Pickups Unlocked !"), 6, 33, EPlayMode::PM_DEFAULT));
	Slogans.Add(FSecretSlogan("Give me a hand", FText::FromString("Inventory Pickups Unlocked !"), 7, 45, EPlayMode::PM_DEFAULT));
	Slogans.Add(FSecretSlogan("Master of time", FText::FromString("Time Pickups enlarged !"), 8, 81, EPlayMode::PM_DEFAULT));
	Slogans.Add(FSecretSlogan("Are you crazy?", FText::FromString("\"Are you crazy\" extra Modes!"), 9, 0, EPlayMode::PM_DEFAULT));
	Slogans.Add(FSecretSlogan("Unlock the spiders", FText::FromString("Spider Achievements Unlocked"), 10, 0, EPlayMode::PM_DEFAULT));
	Slogans.Add(FSecretSlogan("Hot-Rod-Runner", FText::FromString(""), 11, 50, EPlayMode::PM_CLASSIC));
	Slogans.Add(FSecretSlogan("Show me history", FText::FromString(""), 13, 0, EPlayMode::PM_DEFAULT));
	Slogans.Add(FSecretSlogan("Filter me my slogan", FText::FromString(""), 15, 0, EPlayMode::PM_DEFAULT));
 	Slogans.Add(FSecretSlogan("Beat the clock", FText::FromString(""), 12, 0, EPlayMode::PM_DEFAULT));
	Slogans.Add(FSecretSlogan("Yves", FText::FromString("Developer Setup. Run me again."), 16, 400, EPlayMode::PM_DEFAULT));
	Slogans.Add(FSecretSlogan("Azrael", FText::FromString(""), 17, 458, EPlayMode::PM_DEFAULT));
	Slogans.Add(FSecretSlogan("Kaos", FText::FromString(""), 18, 459, EPlayMode::PM_DEFAULT));

}

TArray<FString> FSecretSloganList::GetSecretSlogans(EPlayMode PlayMode) const
{
	TArray<FString> ReturnValue = TArray<FString>();

	for (auto Slogan : Slogans)
	{
		if (Slogan.Episode == PlayMode)
		{
			ReturnValue.Add(Slogan.Slogan);
		}
	}

	return ReturnValue;
}

int32 FSecretSloganList::GetLevelPointsForIndex(int32 Index) const
{
	if (Index <= Slogans.Num())
	{
		return Slogans[Index].LevelPointsToSolve;
	}
	return 9999999;
}
