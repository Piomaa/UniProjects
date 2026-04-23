// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpellBase.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "FireballSpell.generated.h"


UCLASS()
class WITCHHUNT_API UFireballSpell : public USpellBase
{
	GENERATED_BODY()
public:
	UFireballSpell();

	void CastSpell(FVector SpawnLocation, FVector Location); // handle spell logic

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
	UNiagaraSystem* FireballEffect; // storing the niagara system

	UPROPERTY(EditAnywhere, Category = "Spell")
	TSubclassOf<AActor> FireballToSpawn; // not sure why this is the way to do it, but i think it's because it doesnt allow you to create specific blueprint type variables

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_SpawnFireballEffect(FVector SpawnLocation, FVector Velocity); // no idea why this doesn't work right

};
