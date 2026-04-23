// Fill out your copyright notice in the Description page of Project Settings.

#include "TopDownPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "TopDownCharacter.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "Engine/Engine.h"

ATopDownPlayerController::ATopDownPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
	SpellCastingComponent = CreateDefaultSubobject<USpellCastingComponent>(TEXT("SpellComponent"));
}

void ATopDownPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// initialising Enhanced input action
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void ATopDownPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Setup mouse input events and Q spell
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &ATopDownPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &ATopDownPlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &ATopDownPlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this, &ATopDownPlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(QSpellAction, ETriggerEvent::Triggered, this, &ATopDownPlayerController::QSpellTriggered);
	}

}


void ATopDownPlayerController::OnInputStarted()
{
	StopMovement(); //stop current movement before starting again
}

void ATopDownPlayerController::OnSetDestinationTriggered()
{
	FollowTime += GetWorld()->GetDeltaSeconds(); // add time since last click

	FHitResult Hit;
	bool bHitSuccessful = false;
	bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit); // get whatever xyz was under the cursor in world space

	if (bHitSuccessful)
	{
		CachedDestination = Hit.Location; // store the hit if it was a success
	}

	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal(); // calculate the distance between player and the target destination, normalise it to get the general direction
		ControlledPawn->AddMovementInput(WorldDirection, 1.0, false); // move towards that direction
	}
}

void ATopDownPlayerController::OnSetDestinationReleased()
{
	// If it was a short press
	if (FollowTime <= ShortPressThreshold)
	{

		// We move there 
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination); // this should automatically use the navmesh however, it requires some complex process to be able to be replicated as the client
	}

	FollowTime = 0.f; //reset the time that the player has been holding the input for
}

void ATopDownPlayerController::QSpellTriggered()
{
	FHitResult Hit; // variable to store the cursor hit
	bool bHitSuccessful = false;
	bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit); // check if the position is valid
	APawn* ControlledPawn = GetPawn();
	if (bHitSuccessful && ControlledPawn)
	{
		FVector ActorLocation = ControlledPawn->GetActorLocation(); // store position of actor for the spell part
		CachedTarget = FVector(Hit.Location.X, Hit.Location.Y, ActorLocation.Z); // store position of target, however, to keep it in line with player, the Z axis is taken from player
		if (HasAuthority()) // if host
		{
			ServerCastSpell(ActorLocation, CachedTarget); // cast spell as host
		}
		else
		{
			ClientCastSpell(ActorLocation, CachedTarget); // cast spell as client
			if (SpellCastingComponent)
			{
				SpellCastingComponent->CastSpell(ActorLocation, CachedTarget);  // i believe this duplicates the fireball for the client, but it's the only solution i could find
			}																	// to have the niagara effects replicated
		}
	}
}

void ATopDownPlayerController::ServerCastSpell(FVector ActorLoc, FVector Target)
{
		if (SpellCastingComponent)
		{
			SpellCastingComponent->CastSpell(ActorLoc, Target);  // get cursor location and player position and pass it through to the spell
		}
}

void ATopDownPlayerController::ClientCastSpell_Implementation(FVector ActorLoc, FVector Target) // i don't entirely understand how this works ¯\_(x.x)_/¯ 
{
	ServerCastSpell(ActorLoc, Target);
}