//Base class for spells, unfortunately we couldn't get the mana system to work on time with the UI so we scrapped it

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SpellBase.generated.h"

UCLASS()
class WITCHHUNT_API USpellBase : public UObject
{
	GENERATED_BODY()
	
public:
    USpellBase();

    virtual void CastSpell(FVector SpawnLocation, FVector Location);
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spell")
    float ManaCost;

    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spell")
    float Cooldown; // cooldown time in seconds

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spell")
    FString Name; // name of spell
    float LastCastTime; // when spell was last cast
};
