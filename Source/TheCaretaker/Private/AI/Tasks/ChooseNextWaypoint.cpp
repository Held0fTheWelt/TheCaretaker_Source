/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#include "AI/Tasks/ChooseNextWaypoint.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/TargetPoint.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto Blackboard = OwnerComp.GetBlackboardComponent();
	// Gets the current index by selected blackboard keyname
	auto Index = Blackboard->GetValueAsInt(IndexKey.SelectedKeyName);
	
	// Return finish of the task
	return EBTNodeResult::Succeeded;
}

int UChooseNextWaypoint::SetCurrentPatrolPoint()
{
	return 0;
}

void UChooseNextWaypoint::CycleIndex(int Index)
{

}
