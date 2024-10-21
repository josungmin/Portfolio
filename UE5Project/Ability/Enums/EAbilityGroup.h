#pragma once

UENUM(BlueprintType)
enum class EAbilityGroup : uint8
{
	Default		UMETA(DisplayName = "Default"),
	Common		UMETA(DisplayName = "Common"),
	Combat		UMETA(DisplayName = "Combat"),
};
