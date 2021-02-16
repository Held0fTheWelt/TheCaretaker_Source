/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "SpiderSpawnPoint.h"

ASpiderSpawnPoint::ASpiderSpawnPoint()
{
    PathIndex = 0;
}

TArray<AConnectedTargetPoint*, FDefaultAllocator> ASpiderSpawnPoint::GetTargetPoints() const
{
    return TargetWayPoints;
}

int32 ASpiderSpawnPoint::GetPathIndex() const
{
    return PathIndex;
}

FString ASpiderSpawnPoint::GetName() const
{
    return Super::GetName();
}
