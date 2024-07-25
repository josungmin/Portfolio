#pragma once

#include "CoreMinimal.h"
#include "StatSystem/Enums/EStat.h"
#include "StatSystem/Structs/FStatModifier.h"
#include "FStat.generated.h"

USTRUCT(BlueprintType)
struct DEUS_API FStat
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StatModifier")
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StatModifier")
	EStat StatType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StatModifier")
	float BaseValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StatModifier")
	TArray<FStatModifier> StatModifiers;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StatModifier")
	uint32 bIsChanged : 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StatModifier")
	float FinalValue;
};
