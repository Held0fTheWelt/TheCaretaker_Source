/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Structs/Part/PartInformation.h"
#include "DoorInterface.generated.h"


UINTERFACE(MinimalAPI)
class UDoorInterface : public UInterface
{
	GENERATED_BODY()
};

class THECARETAKER_API IDoorInterface
{
	GENERATED_BODY()

public:
	virtual void SetDoorEnabled(bool CanBeUsed) = 0;
	virtual TEnumAsByte<EPartInformation> GetDoorLevel() const = 0;
	virtual void OpenDoorByMaster() = 0;
};
