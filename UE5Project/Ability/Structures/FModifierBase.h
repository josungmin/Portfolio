#pragma once
#include "CoreMinimal.h"
#include "Ability/Enums/EAbility.h"
#include "Ability/Enums/EMargeFormulaType.h"
#include "Ability/Enums/ECalculationFormulaType.h"
#include "FModifierBase.generated.h"


USTRUCT(BlueprintType)
struct DEUS_API FModifierBase
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Modifier")
	FGuid ID = FGuid::NewGuid();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modifier")
	int32 Priority = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modifier")
	EAbility TargetAbility = EAbility::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modifier")
	float Value = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modifier")
	ECalculationFormulaType CalculationFormula = ECalculationFormulaType::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modifier")
	EMargeFormulaType MargeFormula = EMargeFormulaType::None;

	bool operator==(const FModifierBase& Other) const
	{
		return ID == Other.ID;
	}

	bool operator<(const FModifierBase& Other) const
	{
		return Priority < Other.Priority;
	}

	bool IsValid() const
	{
		return ID.IsValid()
			&& FMath::IsFinite(Value)
			&& Priority >= 0
			&& IsValidAbility(TargetAbility)
			&& IsValidFormula(CalculationFormula)
			&& IsValidFormula(MargeFormula);
	}

private:
	bool IsValidAbility(EAbility Ability) const
	{
		return Ability != EAbility::None;
	}

	bool IsValidFormula(ECalculationFormulaType Formula) const
	{
		return Formula != ECalculationFormulaType::None;
	}

	bool IsValidFormula(EMargeFormulaType Formula) const
	{
		return Formula != EMargeFormulaType::None;
	}
};

FORCEINLINE uint32 GetTypeHash(const FModifierBase& Modifier)
{
	return GetTypeHash(Modifier.ID);
}
