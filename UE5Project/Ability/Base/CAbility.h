#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Ability/Base/CModifierContainer.h"
#include "Utilities/CLog.h"
#include "CAbility.generated.h"


UCLASS()
class DEUS_API UCAbility : public UObject
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability")
	TMap<EAbility, UCModifierContainer*> Abilities;

public:
    UFUNCTION(BlueprintCallable, Category = "Abilities")
    const TMap<EAbility, UCModifierContainer*>& GetAbilities() const
    {
        return Abilities;
    }

    UFUNCTION(BlueprintCallable, Category = "Abilities")
    UCModifierContainer* GetAbility(EAbility AbilityType) const
    {
        UCModifierContainer* const* FoundAbility = Abilities.Find(AbilityType);
        if (FoundAbility == nullptr)
        {
            CLog::LogError("Ability does not exists");
            return nullptr;
        }

        return *FoundAbility;
    }

    UFUNCTION(BlueprintCallable, Category = "Abilities")
    void AddAbility(EAbility AbilityType, UCModifierContainer* Ability)
    {
        if (Abilities.Contains(AbilityType))
        {
            CLog::LogError("Ability already exists");
            return;
        }

        Abilities.Add(AbilityType, Ability);
    }

    UFUNCTION(BlueprintCallable, Category = "Abilities")
    void RemoveAbility(EAbility AbilityType)
    {
        if (Abilities.Contains(AbilityType))
        {
            CLog::LogError("Ability does not exists");
            return;
        }

        Abilities.Remove(AbilityType);
    }

    UFUNCTION(BlueprintCallable, Category = "Abilities")
    void AddModifierToAbility(EAbility AbilityType, const FModifierBase& Modifier)
    {
        UCModifierContainer* Ability = GetAbility(AbilityType);
        if (Ability == nullptr)
        {
            CLog::LogError("Ability does not exists");
            return;
        }

        Ability->AddModifier(Modifier);
    }

    UFUNCTION(BlueprintCallable, Category = "Abilities")
    void RemoveModifierToAbility(EAbility AbilityType, const FModifierBase& Modifier)
    {
        UCModifierContainer* Ability = GetAbility(AbilityType);
        if (Ability == nullptr)
        {
            CLog::LogError("Ability does not exists");
            return;
        }

        Ability->RemoveModifier(Modifier);
    }
};
