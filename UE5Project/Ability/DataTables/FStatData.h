#pragma once
#include "CoreMinimal.h"
#include "Ability/Enums/EAbility.h"
#include "Ability/Enums/EAbilityGroup.h"
#include "FStatData.generated.h"


USTRUCT(BlueprintType)
struct DEUS_API FStatData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stat Data")
	EAbilityGroup AbilityGroup;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stat Data")
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stat Data")
	EAbility TargetAbility;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stat Data")
	float BaseValue;
};