// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellCastingComponent.h"

// Called when the game starts
void USpellCastingComponent::BeginPlay()
{
	Super::BeginPlay();
	Spell = NewObject<UFireballSpell>(this); // add spell to the player's arsenal, if we were to add more spells, this is where they would get assigned
}


void USpellCastingComponent::CastSpell(FVector SpawnLocation, FVector Location)
{
	if (IsValid(Spell) && Spell->LastCastTime < GetWorld()->GetTimeSeconds() - Spell->Cooldown) // if target spell exists and the cooldown has expired
	{
		Spell->CastSpell(SpawnLocation, Location); // run the code specific to the spell 
	}
}



