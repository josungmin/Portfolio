#pragma once

UENUM(BlueprintType)
enum class EStateType : uint8
{
	None            UMETA(DisplayName = "None"),
	General		    UMETA(DisplayName = "General"),
	Attack		    UMETA(DisplayName = "Attack"),
	AirAttack		UMETA(DisplayName = "AirAttack"),
	Dodge		    UMETA(DisplayName = "Dodge"),
	Dead		    UMETA(DisplayName = "Dead"),
	Disable		    UMETA(DisplayName = "Disable"),

	E_MAX,
};
