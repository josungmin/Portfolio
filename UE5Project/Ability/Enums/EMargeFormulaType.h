#pragma once

UENUM(BlueprintType)
enum class EMargeFormulaType : uint8
{
	None				UMETA(DisplayName = "None"),
	Marge				UMETA(DisplayName = "Marge"),
	Multiply			UMETA(DisplayName = "Multiply"),
	Overwrite			UMETA(DisplayName = "Overwrite"),
	Highest				UMETA(DisplayName = "Highest"),
	Lowest				UMETA(DisplayName = "Lowest"),
	MaxClamp			UMETA(DisplayName = "MaxClamp"),
	MinClamp			UMETA(DisplayName = "MinClamp"),

	E_MAX,
};
