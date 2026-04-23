// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpellBase.h"
#include "FireballSpell.h"
#include "SpellCastingComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WITCHHUNT_API USpellCastingComponent : public UActorComponent
{
	GENERATED_BODY()
public:	

	UPROPERTY()
	USpellBase* Spell; // base class to host spell, make it into an array to handle multiple spells

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite , Category = "Mana")
	float MaximumMana = 100.f; // currently not in use

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	void CastSpell(FVector SpawnLocation, FVector Location);


		
};
