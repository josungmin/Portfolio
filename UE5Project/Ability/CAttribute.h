#pragma once

#include "CoreMinimal.h"
#include "Ability/Base/CModifierContainer.h"
#include "CAttribute.generated.h"


UCLASS()
class DEUS_API UCAttribute : public UCModifierContainer
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Modifier Container | Attribute")
	TMap<EAbility, float> AttributeToStatInfluence;

public:
	void InitializeAttribute(EAbilityGroup InAbilityGroup, FText InName, EAbility InTargetAbility, float InBaseValue, const TMap<EAbility, float>& InAttributeToStatInfluence)
	{
		Initialize(InAbilityGroup, InName, InTargetAbility, InBaseValue);
		AttributeToStatInfluence = InAttributeToStatInfluence;
	}

	virtual float GetFinalValue() override
	{
		if (bIsChanged)
		{
			CalculateModifiers();
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

	TMap<EAbility, float> GetAttributeToStatInfluence() const
	{
		return AttributeToStatInfluence;
	}

	float CalculateStatInfluence(EAbility StatType) const
	{
		const float* StatModifier = AttributeToStatInfluence.Find(StatType);
		if (StatModifier)
		{
			return BaseValue * (*StatModifier);
		}

		return 0.0f;
	}
};
