/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "Structs/Heat/HeatHistory.h"



FHeatHistoryPerPlayMode::FHeatHistoryPerPlayMode(EPlayMode PM)
{
	PlayMode = PM;
	PointsThisHeat = 0;
}

int32 FHeatHistoryPerPlayMode::GetHeatPoints() const
{
	return PointsThisHeat;
}

void FHeatHistoryPerPlayMode::AddHeatPoints(int32 HeatPoints)
{
	//UE_LOG(LogTemp, Warning, TEXT("Adding %d heat points to value"), HeatPoints);
	PointsThisHeat = PointsThisHeat + HeatPoints;
	//UE_LOG(LogTemp, Warning, TEXT("Points this heat %d"), PointsThisHeat);
}

FHeatHistoryPerPlayMode::FHeatHistoryPerPlayMode()
{
	PlayMode = EPlayMode::PM_NONE;
	PointsThisHeat = 0;
}

FHeatHistoryElement::FHeatHistoryElement()
{
	HeatValues = TArray<FHeatHistoryPerPlayMode>();
	HeatValues.Add(FHeatHistoryPerPlayMode(EPlayMode::PM_CLASSIC));
	HeatValues.Add(FHeatHistoryPerPlayMode(EPlayMode::PM_DEFAULT));

	DateOfHeatEntry = FDateTime::Now();
}

FHeatHistory::FHeatHistory()
{
	HistoryList = TArray<FHeatHistoryElement>();
	
}

int32 FHeatHistoryElement::GetHeatPoints() const
{
	int32 ReturnValue = 0;
	for (auto Heat : HeatValues)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Found %d heat points. Returning "), Heat.GetHeatPoints());
		ReturnValue += Heat.GetHeatPoints();
	}
	return ReturnValue;
}

int32 FHeatHistoryElement::GetHeatPointsPerPlayMode(EPlayMode PlayMode) const
{
	for (auto Heat : HeatValues)
	{
		if (Heat.PlayMode == PlayMode)
			return Heat.PointsThisHeat;
	}

	return -500;
}

void FHeatHistoryElement::AddHeatPoints(EPlayMode PlayMode, int32 HeatPoints)
{
	//UE_LOG(LogTemp, Warning, TEXT("HeatValues Num =  %d"), HeatValues.Num());

	for (int32 i = 0; i < HeatValues.Num(); i++)
	{	
		if (HeatValues[i].PlayMode == PlayMode)
		{
			HeatValues[i].AddHeatPoints(HeatPoints);
		}
	}
}

int32 FHeatHistory::GetHeatPoints() const
{
	int32 ReturnValue = 0;
	UE_LOG(LogTemp, Warning, TEXT("HistoryList Num =  %d"), HistoryList.Num());

	if (HistoryList.Num() > 0)
	{
		for (auto History : HistoryList)
		{
			//UE_LOG(LogTemp, Warning, TEXT("Found %d heat points. Adding"), History.GetHeatPoints());
			ReturnValue += History.GetHeatPoints();
		}
	}
	return ReturnValue;
}

EPlayMode FHeatHistory::HasMostPlayedThisPlayMode() const
{
	if(HistoryList.Num() == 0)
		return EPlayMode::PM_TUTORIAL;


	int32 ClassicHeat = 0;
	int32 DefaultHeat = 0;

	for (auto History : HistoryList)
	{
		ClassicHeat += History.GetHeatPointsPerPlayMode(EPlayMode::PM_CLASSIC);
		DefaultHeat += History.GetHeatPointsPerPlayMode(EPlayMode::PM_DEFAULT);
	}

	if (ClassicHeat > DefaultHeat)
		return EPlayMode::PM_CLASSIC;

	if (DefaultHeat > ClassicHeat)
		return EPlayMode::PM_DEFAULT;

	return EPlayMode::PM_NONE;
}

void FHeatHistory::AddHeatPoints(EPlayMode PlayMode, int32 HeatPoints)
{
	// We do this, as we do have only third of difficulties, giving 1 point for difficulty 0
	// 4 points for difficulty 1 and 9 points for difficulty 3
	// default ranges from 1 - 9
	if (PlayMode == EPlayMode::PM_CLASSIC)
	{
		HeatPoints = HeatPoints * HeatPoints;
	}

	//if (HistoryList.Num() == 0)
	//{
		AddNewHeatPoints(PlayMode, HeatPoints);
	//}
}

void FHeatHistory::AddNewHeatPoints(EPlayMode PlayMode, int32 HeatPoints)
{
	FHeatHistoryElement Element = FHeatHistoryElement();
	Element.AddHeatPoints(PlayMode, HeatPoints);
	HistoryList.Add(Element);
	
}
