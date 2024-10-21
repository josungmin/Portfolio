#pragma once

UENUM(BlueprintType)
enum class EAbility : uint8
{
	None				UMETA(DisplayName = "None"),

	// Attribute
	Vitality		UMETA(DisplayName = "Vitality"),
	Vigor			UMETA(DisplayName = "Vigor"),
	Agility			UMETA(DisplayName = "Agility"),
	Fate			UMETA(DisplayName = "Fate"),
	Technique		UMETA(DisplayName = "Technique"),
	Advance			UMETA(DisplayName = "Advance"),

	// Stat
	// Combat
	AttackPower						UMETA(DisplayName = "AttackPower"),
	CriticalDamage					UMETA(DisplayName = "CriticalDamage"),
	CriticalHitRate					UMETA(DisplayName = "CriticalHitRate"),
	CooldownReduction				UMETA(DisplayName = "CooldownReduction"),
	ItemUseSpeed					UMETA(DisplayName = "ItemUseSpeed"),

	// Survivability
	Speed							UMETA(DisplayName = "Speed"),
	Health							UMETA(DisplayName = "Health"),
	HealthRegen						UMETA(DisplayName = "HealthRegen"),
	HealingBoost					UMETA(DisplayName = "HealingBoost"),
	Defense							UMETA(DisplayName = "Defense"),
	StunResistance					UMETA(DisplayName = "StunResistance"),
	BlindResistance					UMETA(DisplayName = "BlindResistance"),

	// Resource 
	Mana							UMETA(DisplayName = "Mana"),
	ManaRegen						UMETA(DisplayName = "ManaRegen"),
	ManaCostReduction				UMETA(DisplayName = "ManaCostReduction"),
	Stamina							UMETA(DisplayName = "Stamina"),
	StaminaRegen					UMETA(DisplayName = "StaminaRegen"),
	StaminaCostReduction			UMETA(DisplayName = "StaminaCostReduction"),
	ItemDropRate					UMETA(DisplayName = "ItemDropRate"),
	GoldGainRate					UMETA(DisplayName = "GoldGainRate"),

	E_MAX,
};
