#pragma once

UENUM(BlueprintType)
enum class EAttributeType : uint8
{
	Strength			UMETA(DisplayName = "STR"),
	Dexterity			UMETA(DisplayName = "DEX"),
	Intelligence		UMETA(DisplayName = "INT"),
	Wisdom				UMETA(DisplayName = "WIS"),
	Constitution		UMETA(DisplayName = "CON"),
	Charisma			UMETA(DisplayName = "CHA"),

	E_MAX,
};
