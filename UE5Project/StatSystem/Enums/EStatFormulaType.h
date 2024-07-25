#pragma once

UENUM(BlueprintType)
enum class EStatFormulaType : uint8
{
	Add					UMETA(DisplayName = "Add"),
	PercentAdd			UMETA(DisplayName = "PercentAdd"),
	PercentMulti		UMETA(DisplayName = "PercentMulti"),

	E_MAX,
};
