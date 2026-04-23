// Fill out your copyright notice in the Description page of Project Settings.


#include "BTCheckDistance.h"
#include "Kismet/GameplayStatics.h"

#include "BehaviorTree//BlackboardComponent.h"

#include "AIController.h"

#include "Misc/OutputDeviceDebug.h"


UBTCheckDistance::UBTCheckDistance()
{
	NodeName = "Check Distance";
	Distance = 1000; // the distance we want to compare to the distance between player and enemy
	Above = false;
}

EBTNodeResult::Type UBTCheckDistance::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto Blackboard = OwnerComp.GetBlackboardComponent();

	APawn* Player = Cast<APawn>(Blackboard->GetValueAsObject(BBPlayer.SelectedKeyName)); // gets the player object then turns it in to a pawn, if it is in the blackboard object
	if (!Player)
	{
		return EBTNodeResult::Failed; // if there is no player in the blackboard, fail this node so it doesnt continue
	}

	AAIController* AIController = OwnerComp.GetAIOwner();
	APawn* Pawn = AIController->GetPawn(); // gets the pawn of the ai controller, so basically the enemy as a whole

	float distancebetween = FVector::Dist(Player->GetActorLocation(), Pawn->GetActorLocation()); // finds the distance between the player and the enemy

	if (!Above)
	{
		if (distancebetween <= Distance)
		{
			Blackboard->SetValueAsBool(BBBool.SelectedKeyName, true); // if the distance is under what is required, it will change the blackboard bool to true

			return EBTNodeResult::Succeeded;
		}
	}

	if (Above)
	{
		if (distancebetween >= Distance)
		{
			Blackboard->SetValueAsBool(BBBool.SelectedKeyName, false); // if the distance is above what we want, it will change the blackboard bool to false

			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
