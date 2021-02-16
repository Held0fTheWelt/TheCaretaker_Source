/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ChooseNextWaypoint.generated.h"

/**
 */
UCLASS()
class THECARETAKER_API UChooseNextWaypoint : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	struct FBlackboardKeySelector IndexKey;

	//UPROPERTY(EditAnywhere, Category = "Blackboard")

	// Sets the current PatrolPoint
	int SetCurrentPatrolPoint();

	// Cycles through the index of 
	void CycleIndex(int CurrentIndex);

	// Current PatrolPoint Index
	int CurrentIndex;
};
