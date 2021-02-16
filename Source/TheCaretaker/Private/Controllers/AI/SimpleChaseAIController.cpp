/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "SimpleChaseAIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"

#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

ASimpleChaseAIController::ASimpleChaseAIController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	if (BlackBoardComponent == nullptr)
		BlackBoardComponent = CreateDefaultSubobject<UBlackboardComponent>(FName("BlackBoardComponent"));
		
	if (BehaviorTreeComponent == nullptr)
		BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(FName("BehaviorTreeComponent"));
		
	KeyName = FName("PlayerTarget");

	bSetupOkay = false;
}

void ASimpleChaseAIController::BeginPlay()
{
	Super::BeginPlay();
	
	if (ChaseBlackBoard == nullptr)
	{
		return;
	}

	if (ChaseBehaviorTree == nullptr)
	{
		return;
	}

	BlackBoardComponent->InitializeBlackboard(*ChaseBlackBoard);
	BlackBoardComponent->SetValueAsObject(KeyName, UGameplayStatics::GetPlayerPawn(GetWorld(),0));

	BehaviorTreeComponent->StartTree(*ChaseBehaviorTree);
	
}

void ASimpleChaseAIController::StopMovement()
{
	Super::StopMovement();

	BehaviorTreeComponent->StopTree();
}
