// Fill out your copyright notice in the Description page of Project Settings.


#include "BTAttack.h"
#include "Engine/Engine.h"

#include "Kismet/GameplayStatics.h"

#include "BehaviorTree//BlackboardComponent.h"

#include "AIController.h"

#include "Misc/OutputDeviceDebug.h"

#include "TopDownCharacter.h"

#include "HealthComponent.h"

UBTAttack::UBTAttack()
{
	NodeName = "Attack";
	Damage = 10.f;
}

EBTNodeResult::Type UBTAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto Blackboard = OwnerComp.GetBlackboardComponent();
	UHealthComponent* PlayerHealth = nullptr;

	ATopDownCharacter* Player = Cast<ATopDownCharacter>(Blackboard->GetValueAsObject(BBPlayer.SelectedKeyName)); // gets the player from blackboard

	if (Player)
	{
		PlayerHealth = Player->FindComponentByClass<UHealthComponent>(); // if there is a player in blackboard, get the health component in it
	}


	AAIController* AIController = OwnerComp.GetAIOwner();
	APawn* Pawn = AIController->GetPawn(); // gets the pawn from the ai controller



	if (Player && PlayerHealth) // this check is so that, in case the player is defeated, the ai wont try to attack again, as there is no player to attack
	{

		PlayerHealth->TakeDamage(Damage); // player takes damage and letting the node go to the next in the behaviour tree
		return EBTNodeResult::Succeeded;

	}
	if (!Player)
	{
		Blackboard->SetValueAsBool("b_FoundPlayer", false); // if there is no player in the game, as it was destroyed when it was killed, these bools turn false
		Blackboard->SetValueAsBool("b_InRange", false);
	}
	return EBTNodeResult::Failed;
}
