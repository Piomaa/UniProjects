// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"


#include "Perception/PawnSensingComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"

#include "EnemyAIController.h"


#include "AICharacter.generated.h"

UCLASS()

class WITCHHUNT_API AAICharacter : public ACharacter
{
	GENERATED_BODY()

public:

	AAICharacter();
	void BeginPlay();

	UFUNCTION(BlueprintCallable, Category = "Damage")
	void TakeDamage();


	UPROPERTY(VisibleAnywhere, Category = "AI")
	UPawnSensingComponent* PawnSensingComponent;

	AEnemyAIController* AIController;

	UFUNCTION(BlueprintImplementableEvent)
	void OnDeathEvent();

	// the on see pawn function for the ai, it uses the sight
	UFUNCTION()
	void OnSeePawn(APawn* Pawn);



};
