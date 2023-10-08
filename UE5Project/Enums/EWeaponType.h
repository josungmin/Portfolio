#pragma once

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	None            UMETA(DisplayName = "None"),
	LightSword		UMETA(DisplayName = "LightSword"),
	GreatSword		UMETA(DisplayName = "GreatSword"),

	E_MAX,
};