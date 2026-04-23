//Base class for spells, unfortunately we couldn't get the mana system to work on time with the UI so we scrapped it

#include "SpellBase.h"

USpellBase::USpellBase()
{
	Name = "Blank";
	ManaCost = 10.f;
	Cooldown = 0.5f;

}

void USpellBase::CastSpell(FVector SpawnLocation, FVector Location) // this function is meant to be overridden but is good for testing purposes, the idea is that each spell has different logic to it
{
	if (LastCastTime < GetWorld()->GetTimeSeconds() - Cooldown) // if spell was cast longer ago than the cooldown, then run the code
	{
		DrawDebugSphere(GetWorld(), Location, 50.f, 12, FColor::Red, false, 2.f);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, *FString::Printf(TEXT("Casting spell: %s At: %.2f, %.2f, %.2f"), *Name, Location.X, Location.Y, Location.Z));
		LastCastTime = GetWorld()->GetTimeSeconds();
	}
	else 
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, *FString::Printf(TEXT("%s spell is on cooldown"), *Name));
	}

}

