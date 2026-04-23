// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SpellCastingComponent.h"
#include "TopDownPlayerController.generated.h"
class UInputMappingContext;
class UInputAction;
class USpellCastingComponent;


UCLASS()
class WITCHHUNT_API ATopDownPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATopDownPlayerController();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold; // amount of time required for the nav mesh input to occur

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input");
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true")); // not sure if allow private access does anything important
	UInputAction* SetDestinationClickAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true")); 
	UInputAction* QSpellAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spell")
	USpellCastingComponent* SpellCastingComponent; // this shouldn't have been integrated on any player controller, a better implementation should be done in order to have different player combat etc...

protected:

	uint32 bMoveToMouseCursor : 1;

	void SetupInputComponent();

	void BeginPlay();

	void OnInputStarted(); // for mouse click
	void OnSetDestinationTriggered(); // same
	void OnSetDestinationReleased(); // same

	void QSpellTriggered(); // for casting a spell

private:
	FVector CachedDestination; //storing target location for movement
	FVector CachedTarget; // storing target location for spell
	float FollowTime; // stores time spent holding movement input before releasing

public:
	void ServerCastSpell(FVector ActorLoc, FVector Target); // multiplayer stuff, ServerCast spell should be used by server only
	UFUNCTION(Server, Reliable)
	void ClientCastSpell(FVector ActorLoc, FVector Target); // this one should be used by client
};
