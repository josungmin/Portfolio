#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Ability/Enums/EAbilityGroup.h"
#include "Ability/Structures/FModifierBase.h"
#include "Ability/Structures/FModifierMarger.h"
#include "Ability/Structures/FModifierCalculator.h"
#include "Utilities/CLog.h"
#include "CModifierContainer.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnModifierValueChanged, float, NewValue);

UCLASS()
class DEUS_API UCModifierContainer : public UObject
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Modifier Container")
	EAbilityGroup AbilityGroup;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Modifier Container")
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Modifier Container")
	EAbility TargetAbility;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Modifier Container")
	float BaseValue;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Modifier Container")
	float FinalValue;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Modifier Container")
	TMap<FGuid, FModifierBase> Modifiers;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Modifier Container")
	uint32 bIsChanged : 1;

public:
	UPROPERTY(BlueprintAssignable, Category = "Modifier Container")
	FOnModifierValueChanged OnModifierValueChanged;

public:
	void Initialize(EAbilityGroup InAbilityGroup, FText InName, EAbility InTargetAbility, float InBaseValue)
	{
		AbilityGroup = InAbilityGroup;
		Name = InName;
		TargetAbility = InTargetAbility;
		BaseValue = InBaseValue;

		FinalValue = InBaseValue;
		bIsChanged = false;
	}

	UFUNCTION(BlueprintCallable)
	EAbilityGroup GetAbilityGroup() const
	{
		return AbilityGroup;
	}

	UFUNCTION(BlueprintCallable)
	EAbility GetTargetAbility() const
	{
		return TargetAbility;
	}

	UFUNCTION(BlueprintCallable)
	FText GetName() const
	{
		return Name;
	}

	UFUNCTION(BlueprintCallable)
	virtual float GetFinalValue()
	{
		if (bIsChanged)
		{
			CalculateModifiers();
		}

		return FinalValue;
	}

	UFUNCTION(BlueprintCallable)
	virtual void AddModifier(const FModifierBase& Modifier)
	{
		if (!Modifier.IsValid())
		{
			CLog::LogError("Invalid modifier");
			return;
		}

		if (Modifiers.Contains(Modifier.ID))
		{
			// Combine modifier values using the merge formula
			FModifierMarger ModifierMarger;
			Modifiers[Modifier.ID].Value = ModifierMarger.Marge(
				Modifier.MargeFormula, Modifiers[Modifier.ID].Value, Modifier.Value);
		}
		else
		{
			Modifiers.Add(Modifier.ID, Modifier);
		}

		bIsChanged = true;
	}

	UFUNCTION(BlueprintCallable)
	virtual void RemoveModifier(const FModifierBase& Modifier)
	{
		if (!Modifier.IsValid())
		{
			CLog::LogError("Invalid modifier");
			return;
		}

		if (!Modifiers.Remove(Modifier.ID))
		{
			CLog::LogError("Modifier does not exist");
			return;
		}

		bIsChanged = true;
	}

	UFUNCTION(BlueprintCallable)
	virtual void CalculateModifiers(float BonusValue = 0)
	{
		if (!bIsChanged)
		{
			return;
		}

		FinalValue = BaseValue + BonusValue;

		Modifiers.ValueSort([](const FModifierBase& A, const FModifierBase& B)
		{
			return A.Priority < B.Priority;
		});

		FModifierCalculator StatFormula;
		for (const TPair<FGuid, FModifierBase>& Pair : Modifiers)
		{
			const FModifierBase& Modifier = Pair.Value;
			if (!Modifier.IsValid())
			{
				CLog::LogError("Modifier is not valid");
				continue;
			}

			FinalValue = StatFormula.Calculate(Modifier.CalculationFormula, FinalValue, Modifier.Value);
		}

		bIsChanged = false;

		OnModifierValueChanged.Broadcast(FinalValue);
	}
};
