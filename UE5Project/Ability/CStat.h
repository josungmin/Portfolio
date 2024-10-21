#pragma once
#include "CoreMinimal.h"
#include "Ability/Base/CModifierContainer.h"
#include "CStat.generated.h"


UCLASS()
class DEUS_API UCStat : public UCModifierContainer
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Modifier Container | Stat")
	float AttributeBonusValue;

public:
	void InitializeStat(EAbilityGroup InAbilityGroup, FText InName, EAbility InTargetAbility, float InBaseValue)
	{
		AttributeBonusValue = 0.0f;
	}

	virtual float GetFinalValue() override
	{
		if (bIsChanged)
		{
			CalculateModifiers(AttributeBonusValue);
		}

		return FinalValue;
	}

	virtual void AddModifier(const FModifierBase& Modifier) override
	{
		Super::AddModifier(Modifier);
	}

	virtual void RemoveModifier(const FModifierBase& Modifier) override
	{
		Super::RemoveModifier(Modifier);
	}

	virtual void CalculateModifiers(float BonusValue = 0) override
	{
		Super::CalculateModifiers(BonusValue);
	}

	void UpdateAttributeBonusValue(float NewBonusValue)
	{
		AttributeBonusValue = NewBonusValue;
		bIsChanged = true;
	}

public:
	FORCEINLINE float GetAttributeBonusValue() const
	{
		return AttributeBonusValue;
	}
};
