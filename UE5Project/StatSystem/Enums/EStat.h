#pragma once

UENUM(BlueprintType)
enum class EStat
{
	MaxHealth					UMETA(DisplayName = "MaxHealth"),
	HealthRegen					UMETA(DisplayName = "HealthRegen"),
	MaxMana						UMETA(DisplayName = "MaxMana"),
	ManaRegen					UMETA(DisplayName = "ManaRegen"),
	ManaCostReduction			UMETA(DisplayName = "ManaCostReduction"),

	AttackPower					UMETA(DisplayName = "AttackPower"),
	MeleeAttackPower			UMETA(DisplayName = "MeleeAttackPower"),
	RangedAttackPower			UMETA(DisplayName = "RangedAttackPower"),
	MagicAttackPower			UMETA(DisplayName = "MagicAttackPower"),

	Accuracy					UMETA(DisplayName = "Accuracy"),
	MeleeAccuracy				UMETA(DisplayName = "MeleeAccuracy"),
	RangedAccuracy				UMETA(DisplayName = "RangedAccuracy"),
	MagicAccuracy				UMETA(DisplayName = "MagicAccuracy"),

	CriticalHitChance			UMETA(DisplayName = "CriticalHitChance"),
	MeleeCriticalHitChance		UMETA(DisplayName = "MeleeCriticalHitChance"),
	RangedCriticalHitChance		UMETA(DisplayName = "RangedCriticalHitChance"),
	MagicCriticalHitChance		UMETA(DisplayName = "MagicCriticalHitChance"),

	MaxCarryWeight				UMETA(DisplayName = "MaxCarryWeight"),

	E_MAX,
};
