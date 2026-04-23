// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"

#include "EnemyAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BehaviorTree.h"

#include "BehaviorTree//BlackboardComponent.h"
#include "Misc/OutputDeviceDebug.h"

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	if (AIBehavior != nullptr)
	{
		RunBehaviorTree(AIBehavior);
	}
}
