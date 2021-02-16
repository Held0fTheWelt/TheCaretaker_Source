/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "Structs/BlueprintData/BlueprintData.h"

#include "Engine/StaticMesh.h"
#include "Enums/BlueprintData/BlueprintDataType.h"

FBlueprintData::FBlueprintData()
{
	DataType = EBlueprintDataType::EBDT_NONE;
	BlueprintTemplate = nullptr;
}

FBlueprintData::FBlueprintData(EBlueprintDataType Type)
{
	DataType = Type;
	BlueprintTemplate = nullptr;
}

