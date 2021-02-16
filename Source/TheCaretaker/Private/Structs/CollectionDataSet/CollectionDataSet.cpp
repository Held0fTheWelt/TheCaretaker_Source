/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "Structs/CollectionDataSet/CollectionDataSet.h"

#include "Engine/StaticMesh.h"
#include "Enums/Collections/CollectionDataType.h"

FCollectionData::FCollectionData()
{
	Mesh = nullptr;
	DataType = ECollectionDataType::ECDT_NONE;
}

FCollectionData::FCollectionData(ECollectionDataType Type)
{
	Mesh = nullptr;
	DataType = Type;
}

FCollectionDataSet::FCollectionDataSet()
{
	CollectionData.Empty();

	CollectionData.Add(FCollectionData(ECollectionDataType::ECDT_FLOOR));
	CollectionData.Add(FCollectionData(ECollectionDataType::ECDT_GROUND));
	CollectionData.Add(FCollectionData());
	CollectionData.Add(FCollectionData());
	CollectionData.Add(FCollectionData());
	CollectionData.Add(FCollectionData());
	CollectionData.Add(FCollectionData());
	CollectionData.Add(FCollectionData());
	CollectionData.Add(FCollectionData());
	CollectionData.Add(FCollectionData());
	CollectionData.Add(FCollectionData());
	CollectionData.Add(FCollectionData());
	CollectionData.Add(FCollectionData());
	CollectionData.Add(FCollectionData());
	CollectionData.Add(FCollectionData());
	CollectionData.Add(FCollectionData());
	CollectionData.Add(FCollectionData());
	CollectionData.Add(FCollectionData());
	CollectionData.Add(FCollectionData());
	CollectionData.Add(FCollectionData());
	CollectionData.Add(FCollectionData());
	CollectionData.Add(FCollectionData());
	CollectionData.Add(FCollectionData());

	LevelIndex = -1;
}

