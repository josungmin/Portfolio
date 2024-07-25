#pragma once

#include "CoreMinimal.h"
#include "StatSystem/Enums/EStat.h"
#include "StatSystem/Enums/EStatFormulaType.h"
#include "FStatModifier.generated.h"

USTRUCT(BlueprintType)
struct DEUS_API FStatModifier
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StatModifier")
	EStat TargetStat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StatModifier")
	EStatFormulaType FormulaType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StatModifier")
	float Value;

	bool operator==(const FStatModifier& Other) const
	{
		return TargetStat == Other.TargetStat && FormulaType == Other.FormulaType && FMath::IsNearlyEqual(Value, Other.Value);
	}
};
