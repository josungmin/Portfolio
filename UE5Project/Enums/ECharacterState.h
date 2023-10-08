#pragma once

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	None            UMETA(DisplayName = "None"),
	GeneralState    UMETA(DisplayName = "GeneralState"),
	DodegState		UMETA(DisplayName = "DodegState"),
	AttackState		UMETA(DisplayName = "AttackState"),
	DeadState		UMETA(DisplayName = "DeadState"),
	DisabledState   UMETA(DisplayName = "DisabledState"),

	E_MAX,
};