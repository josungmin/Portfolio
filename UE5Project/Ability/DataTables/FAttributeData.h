#pragma once
#include "CoreMinimal.h"
#include "Ability/Enums/EAbility.h"
#include "Ability/Enums/EAbilityGroup.h"
#include "FAttributeData.generated.h"


USTRUCT(BlueprintType)
struct DEUS_API FAttributeData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stat Data")
	EAbilityGroup AbilityGroup;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribute Data")
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribute Data")
	EAbility TargetAbility;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribute Data")
	float BaseValue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribute Data")
	TMap<EAbility, float> AttributeToStatInfluence;
};