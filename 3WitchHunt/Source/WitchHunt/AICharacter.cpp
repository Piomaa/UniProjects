// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter.h"
#include "TopDownCharacter.h"

// Sets default values
AAICharacter::AAICharacter()
{
    PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));

    if (PawnSensingComponent)
    {
        // sets the values of the componene to what we require
        PawnSensingComponent->SightRadius = 1000.0f;
        PawnSensingComponent->SetPeripheralVisionAngle(90.0f);
        PawnSensingComponent->HearingThreshold = 600.0f;
        PawnSensingComponent->LOSHearingThreshold = 1200.0f;
    }

}

void AAICharacter::BeginPlay()
{
    Super::BeginPlay();

    if (PawnSensingComponent)
    {
        PawnSensingComponent->OnSeePawn.AddDynamic(this, &AAICharacter::OnSeePawn); 
    }

    AIController = Cast<AEnemyAIController>(GetController()); // gets the ai controller, so i can get to the blackboard component in it
}

void AAICharacter::TakeDamage()
{
    OnDeathEvent(); // calls the on death event in the blueprints, that destroys the Ai character
}

void AAICharacter::OnSeePawn(APawn* Pawn)
{

    if (Pawn && Pawn->IsA(ATopDownCharacter::StaticClass()) && !AIController->GetBlackboardComponent()->GetValueAsObject("Player"))
    {
        AIController->GetBlackboardComponent()->SetValueAsObject("Player", Pawn); // sets the player as the player object in the blackboard
        AIController->GetBlackboardComponent()->SetValueAsBool("b_FoundPlayer", true); // sets the blackboard bool true so it knows its found a player

    }


}
