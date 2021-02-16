/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "DataBaseTranslator.h"

//#include "JsonCsvToDataTableToStructBPLibrary.h"
#include "Engine/DataTable.h"
#include "Log/GlobalLog.h"


ADataBaseTranslator::ADataBaseTranslator()
{

}

void ADataBaseTranslator::TranslateData()
{
	//TArray<FPlayModeInformationTranslation> PlayModeTranslation = TArray<FPlayModeInformationTranslation>();

	//static const FString ContextString(TEXT("PlayModeInformation"));
	//if (PlayModeInformation == nullptr)
	//{
	//	LOG_WARNING(InitializationLog, "Could not find PlayModeInformation Table ! This shouldn't happen !")
	//	return;
	//}

	//TArray<FName> RowNames = PlayModeInformation->GetRowNames();
	//for (int32 i = 0; i < RowNames.Num(); i++)
	//{

	//	int32 CurrentPlayModeIndex = i;
	//	FPlayModeInformation* PlayModeInfo = PlayModeInformation->FindRow<FPlayModeInformation>(RowNames[i], ContextString, true);

	//	EPlayMode CurrentPlayMode = PlayModeInfo->PlayMode;

	//	for (int32 j = 0; j < PlayModeInfo->Levels.Num(); j++)
	//	{
	//		int32 CurrentLevelIndex = j;
	//		for (int32 k = 0; k < PlayModeInfo->Levels[j].DungeonsInLevel.Num(); k++)
	//		{
	//			int32 CurrentDungeonIndex = k;

	//			for (int32 l = 0; l < PlayModeInfo->Levels[j].DungeonsInLevel[k].Difficulties.Num(); l++)
	//			{
	//				int32 CurrentDifficultyIndex = l;
	//				for (int32 m = 0; m < PlayModeInfo->Levels[j].DungeonsInLevel[k].Difficulties[l].DungeonParts.Num(); m++)
	//				{
	//					int32 CurrentDungeonPart = m;
	//					UE_LOG(LogTemp, Warning, TEXT("%d parts"), PlayModeInfo->Levels[j].DungeonsInLevel[k].Difficulties[l].DungeonParts[m].PartsWithDifficulty.Num());
	//					
	//					for (int32 n = 0; n < PlayModeInfo->Levels[j].DungeonsInLevel[k].Difficulties[l].DungeonParts[m].PartsWithDifficulty.Num(); n++)
	//					{
	//						int32 PartInLevel = n;
	//						FPartDifficultyInformation DungeonPart = PlayModeInfo->Levels[j].DungeonsInLevel[k].Difficulties[l].DungeonParts[m].PartsWithDifficulty[n];

	//						FPlayModeInformationTranslation TranslationInformation = FPlayModeInformationTranslation();

	//						TranslationInformation.PlayMode = CurrentPlayMode;

	//						TranslationInformation.Level = CurrentLevelIndex;
	//						TranslationInformation.Dungeon = CurrentDungeonIndex;
	//						TranslationInformation.Difficulty= CurrentDifficultyIndex;
	//						TranslationInformation.PartInformation = EPartInformation(CurrentDungeonPart + 1);
	//						TranslationInformation.PartOfLevel= EPartInformation(PartInLevel + 1);

	//						TranslationInformation.TitleMessage = DungeonPart.PartTitleMessage;
	//						TranslationInformation.SubtitleMessage = DungeonPart.PartEntryMessage;

	//						TranslationInformation.NumberOfGarbage = DungeonPart.NumberOfGarbage;
	//						TranslationInformation.NumberOfChests = DungeonPart.NumberOfChests;
	//						TranslationInformation.NumberOfTraps= DungeonPart.NumberOfTraps;
	//						
	//						TranslationInformation.NumberOfSpiders = DungeonPart.NumberOfSpiders;
	//						TranslationInformation.PathNumberMax = DungeonPart.PathNumberMax;
	//						TranslationInformation.PathSpreadValues = DungeonPart.PathSpreadValue;
	//						
	//						if (TranslationInformation.PathSpreadValues.Num() == 0)
	//							TranslationInformation.PathSpreadValues.Add(1.f);

	//						TranslationInformation.TimeToGetHungry = DungeonPart.TimeToGetHungry;
	//						TranslationInformation.bWaitForEndOfTime = DungeonPart.bWaitForEndOfTime;
	//						TranslationInformation.PlayModeOfPart = DungeonPart.PlayMode;
	//						
	//						if (DungeonPart.SecretCredentials.Num() > 0)
	//						{
	//							TranslationInformation.Secret0Character = DungeonPart.SecretCredentials[0].Character;
	//							TranslationInformation.Secret0Color = DungeonPart.SecretCredentials[0].TextColorCode;
	//							TranslationInformation.Secret0SubColor = DungeonPart.SecretCredentials[0].OutlineColorCode;
	//							TranslationInformation.Secret0SloganIndex = DungeonPart.SecretCredentials[0].ConnectedSloganIndex;
	//						}
	//						//else
	//						//{
	//						//	TranslationInformation.Secret0Character = "";
	//						//	TranslationInformation.Secret0Color = FLinearColor::Black;
	//						//	TranslationInformation.Secret0SubColor = FLinearColor::Black;
	//						//	TranslationInformation.Secret0SloganIndex = 0;
	//						//}

	//						if (DungeonPart.SecretCredentials.Num() > 1)
	//						{
	//							TranslationInformation.Secret1Character = DungeonPart.SecretCredentials[1].Character;
	//							TranslationInformation.Secret1Color = DungeonPart.SecretCredentials[1].TextColorCode;
	//							TranslationInformation.Secret1SubColor = DungeonPart.SecretCredentials[1].OutlineColorCode;
	//							TranslationInformation.Secret1SloganIndex = DungeonPart.SecretCredentials[1].ConnectedSloganIndex;
	//						}
	//						//else
	//						//{
	//						//	TranslationInformation.Secret1Character = "";
	//						//	TranslationInformation.Secret1Color = FLinearColor::Black;
	//						//	TranslationInformation.Secret1SubColor = FLinearColor::Black;
	//						//	TranslationInformation.Secret1SloganIndex = 0;
	//						//}

	//						PlayModeTranslation.Add(TranslationInformation);
	//					}
	//				}
	//			}
	//		}
	//	}
	//}

	//UE_LOG(LogTemp, Warning, TEXT("Translation makes up %d rows"), PlayModeTranslation.Num());

	//UpdateTranslation(PlayModeTranslation);
}

void ADataBaseTranslator::RetranslateData()
{	
	//UE_LOG(LogTemp, Warning, TEXT("Starting"));
	//TArray<FPlayModeInformation> PlayModeInfo = TArray<FPlayModeInformation>();

	//static const FString ContextString(TEXT("PlayModeInformationTranslation"));
	//if (PlayModeInformationTranslation == nullptr)
	//{
	//	LOG_WARNING(InitializationLog, "Could not find PlayModeInformationTranslation Table ! This shouldn't happen !")
	//	return;
	//}
	//
	//TArray<FName> RowNames = PlayModeInformationTranslation->GetRowNames();
	//for (int32 i = 0; i < RowNames.Num(); i++)
	//{
	//	FPlayModeInformationTranslation* InformationTranslation = PlayModeInformationTranslation->FindRow<FPlayModeInformationTranslation>(RowNames[i], ContextString, true);

	//	if (InformationTranslation == nullptr)
	//	{

	//		LOG_WARNING(InitializationLog, "Could not get Row Name.")
	//		return;
	//	}
	//	else
	//	{
	//		bool HasPlayMode = false;
	//		int32 PlayModeIndex = 0;
	//		for (int32 j = 0; j < PlayModeInfo.Num(); j++)
	//		{
	//			if (PlayModeInfo[j].PlayMode == InformationTranslation->PlayMode)
	//			{
	//				HasPlayMode = true;
	//				PlayModeIndex = j;
	//				break;
	//			}
	//		}
	//		if (!HasPlayMode)
	//		{
	//			PlayModeInfo.Add(FPlayModeInformation());
	//			PlayModeIndex = PlayModeInfo.Num() - 1;
	//			PlayModeInfo[PlayModeIndex].PlayMode = InformationTranslation->PlayMode;
	//		}

	//		bool HasLevel = false;
	//		int32 LevelIndex = 0;
	//		for (int32 j = 0; j < PlayModeInfo[PlayModeIndex].Levels.Num(); j++)
	//		{
	//			if (j == InformationTranslation->Level)
	//			{
	//				HasLevel = true;
	//				LevelIndex = j;
	//				break;
	//			}
	//		}
	//		if (!HasLevel)
	//		{
	//			PlayModeInfo[PlayModeIndex].Levels.Add(FLevelSetup());
	//			LevelIndex = PlayModeInfo[PlayModeIndex].Levels.Num() - 1;
	//		}


	//		bool HasDungeon = false;
	//		int32 DungeonIndex = 0;
	//		for (int32 j = 0; j < PlayModeInfo[PlayModeIndex].Levels[LevelIndex].DungeonsInLevel.Num(); j++)
	//		{
	//			if (j == InformationTranslation->Dungeon)
	//			{
	//				HasDungeon = true;
	//				DungeonIndex = j;
	//				break;
	//			}
	//		}
	//		if (!HasDungeon)
	//		{
	//			PlayModeInfo[PlayModeIndex].Levels[LevelIndex].DungeonsInLevel.Add(FLevelDungeonInformation());
	//			DungeonIndex = PlayModeInfo[PlayModeIndex].Levels[LevelIndex].DungeonsInLevel.Num() - 1;
	//		}

	//		bool HasDifficulty = false;
	//		int32 DifficultyIndex = 0;
	//		for (int32 j = 0; j < PlayModeInfo[PlayModeIndex].Levels[LevelIndex].DungeonsInLevel[DungeonIndex].Difficulties.Num(); j++)
	//		{
	//			if (j == InformationTranslation->Difficulty)
	//			{
	//				HasDifficulty = true;
	//				DifficultyIndex = j;
	//				break;
	//			}
	//		}
	//		if (!HasDifficulty)
	//		{
	//		
	//			PlayModeInfo[PlayModeIndex].Levels[LevelIndex].DungeonsInLevel[DungeonIndex].Difficulties.Add(FDungeonDifficultyInformation());
	//			DifficultyIndex = PlayModeInfo[PlayModeIndex].Levels[LevelIndex].DungeonsInLevel[DungeonIndex].Difficulties.Num() - 1;
	//		}

	//		bool HasPart = false;
	//		int32 PartIndex = InformationTranslation->PartInformation - 1;
	//		/*for (int32 j = 0; j < PlayModeInfo[PlayModeIndex].Levels[LevelIndex].DungeonsInLevel[DungeonIndex].Difficulties[DifficultyIndex].DungeonParts.Num(); j++)
	//		{
	//			if (j == )
	//			{
	//				HasPart = true;
	//				PartIndex = j;
	//				break;
	//			}
	//		}
	//		if (!PartIndex)
	//		{
	//			PlayModeInfo[PlayModeIndex].Levels[LevelIndex].DungeonsInLevel[DungeonIndex].Difficulties[DifficultyIndex].DungeonParts.Add(FDungeonPartInformation());
	//			PartIndex = PlayModeInfo[PlayModeIndex].Levels[LevelIndex].DungeonsInLevel[DungeonIndex].Difficulties[DifficultyIndex].DungeonParts.Num() - 1;
	//		}*/

	//		bool HasPartInLevel = false;
	//		UE_LOG(LogTemp, Warning, TEXT("DungeonParts here: %d"), PlayModeInfo[PlayModeIndex].Levels[LevelIndex].DungeonsInLevel[DungeonIndex].Difficulties[DifficultyIndex].DungeonParts.Num());
	//		
	//		int32 PartInLevelIndex = InformationTranslation->PartOfLevel - 1;
	//		/*for (int32 j = 0; j < PlayModeInfo[PlayModeIndex].Levels[LevelIndex].DungeonsInLevel[DungeonIndex].Difficulties[DifficultyIndex].DungeonParts[PartIndex].PartsWithDifficulty.Num(); j++)
	//		{
	//			if (j == InformationTranslation->PartOfLevel - 1)
	//			{
	//				HasPartInLevel = true;
	//				PartInLevelIndex = j;
	//				break;
	//			}
	//		}
	//		if (!HasDifficulty)
	//		{
	//			PlayModeInfo[PlayModeIndex].Levels[LevelIndex].DungeonsInLevel[DungeonIndex].Difficulties[DifficultyIndex].DungeonParts[PartIndex].PartsWithDifficulty.Add(FPartDifficultyInformation());
	//			PartInLevelIndex = PlayModeInfo[PlayModeIndex].Levels[LevelIndex].DungeonsInLevel[DungeonIndex].Difficulties[DifficultyIndex].DungeonParts[PartIndex].PartsWithDifficulty.Num() - 1;
	//		}*/

	//		FPartDifficultyInformation DifficultySettings = FPartDifficultyInformation();

	//		DifficultySettings.PartTitleMessage = InformationTranslation->TitleMessage;
	//		DifficultySettings.PartEntryMessage = InformationTranslation->SubtitleMessage;
	//		DifficultySettings.NumberOfGarbage = InformationTranslation->NumberOfGarbage;
	//		DifficultySettings.NumberOfChests = InformationTranslation->NumberOfChests;
	//		DifficultySettings.NumberOfTraps = InformationTranslation->NumberOfTraps;
	//		DifficultySettings.NumberOfSpiders = InformationTranslation->NumberOfSpiders;
	//		DifficultySettings.PathNumberMax = InformationTranslation->PathNumberMax;
	//		DifficultySettings.PathSpreadValue = InformationTranslation->PathSpreadValues;
	//		if (DifficultySettings.PathSpreadValue.Num() == 0)
	//			DifficultySettings.PathSpreadValue.Add(1.f);
	//		DifficultySettings.TimeToGetHungry = InformationTranslation->TimeToGetHungry;
	//		DifficultySettings.bWaitForEndOfTime = InformationTranslation->bWaitForEndOfTime;
	//		DifficultySettings.PlayMode = InformationTranslation->PlayModeOfPart;

	//		TArray<FSecretCredential> SecretCredentials;

	//		SecretCredentials.Add(FSecretCredential());
	//		SecretCredentials.Add(FSecretCredential());

	//		SecretCredentials[0].Character = InformationTranslation->Secret0Character;
	//		SecretCredentials[0].TextColorCode = InformationTranslation->Secret0Color;
	//		SecretCredentials[0].OutlineColorCode = InformationTranslation->Secret0SubColor;
	//		SecretCredentials[0].ConnectedSloganIndex = InformationTranslation->Secret0SloganIndex;

	//		SecretCredentials[1].Character = InformationTranslation->Secret1Character;
	//		SecretCredentials[1].TextColorCode = InformationTranslation->Secret1Color;
	//		SecretCredentials[1].OutlineColorCode = InformationTranslation->Secret1SubColor;
	//		SecretCredentials[1].ConnectedSloganIndex = InformationTranslation->Secret1SloganIndex;

	//		DifficultySettings.SecretCredentials = SecretCredentials;

	//		PlayModeInfo[PlayModeIndex].Levels[LevelIndex].DungeonsInLevel[DungeonIndex].Difficulties[DifficultyIndex].DungeonParts[PartIndex].PartsWithDifficulty[PartInLevelIndex] = DifficultySettings;
	//	}
	//}

	//UE_LOG(LogTemp, Warning, TEXT("%d PlayModes in List"), PlayModeInfo.Num());

	//for (int32 i = 0; i < PlayModeInfo.Num(); i++)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("PlayMode %d has %d Levels"), i, PlayModeInfo[i].Levels.Num());
	//	for (int32 j = 0; j < PlayModeInfo[i].Levels.Num(); j++)
	//	{
	//		UE_LOG(LogTemp, Warning, TEXT("PlayMode %d , Level %d has %d dungeons"), i, j, PlayModeInfo[i].Levels[j].DungeonsInLevel.Num());
	//		for (int32 k = 0; k < PlayModeInfo[i].Levels[j].DungeonsInLevel.Num(); k++)
	//		{
	//			UE_LOG(LogTemp, Warning, TEXT("PlayMode %d , Level %d, dungeon %d, has %d difficulties"), i, j, k, PlayModeInfo[i].Levels[j].DungeonsInLevel[k].Difficulties.Num());
	//			for (int32 l = 0; l < PlayModeInfo[i].Levels[j].DungeonsInLevel[k].Difficulties.Num(); l++)
	//			{
	//				UE_LOG(LogTemp, Warning, TEXT("PlayMode %d , Level %d, dungeon %d, difficulty %d has %d parts"), i, j, k, l, PlayModeInfo[i].Levels[j].DungeonsInLevel[k].Difficulties[l].DungeonParts.Num());
	//			}
	//		}
	//	}
	//}

	//UpdateReTranslation(RowNames, PlayModeInfo);
}
