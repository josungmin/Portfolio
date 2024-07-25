#include "Game/Characters/CCombatCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

// Combat System
#include "CombatSystem/CCombatComponent.h"
#include "EquipmentSystem/CWeaponBase.h"

// Action System
#include "ActionSystem/CActionComponent.h"
#include "ActionSystem/CAction.h"

// Input
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// Debug
#include "Utilities/CLog.h"

ACCombatCharacter::ACCombatCharacter()
{
	ActionComponent = CreateDefaultSubobject<UCActionComponent>(TEXT("ActionComponent"));
	CombatComponent = CreateDefaultSubobject<UCCombatComponent>(TEXT("CombatComponent"));
}

void ACCombatCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ACCombatCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACCombatCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (DashAction)
	{
		EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Triggered, this, &ACCombatCharacter::OnDash);
	}

	if (Attack_01Action)
	{
		EnhancedInputComponent->BindAction(Attack_01Action, ETriggerEvent::Triggered, this, &ACCombatCharacter::OnAttack_01);
	}

	if (Attack_02Action)
	{
		EnhancedInputComponent->BindAction(Attack_02Action, ETriggerEvent::Triggered, this, &ACCombatCharacter::OnAttack_02);
	}

	if (RisingAttackAction)
	{
		EnhancedInputComponent->BindAction(RisingAttackAction, ETriggerEvent::Triggered, this, &ACCombatCharacter::OnRisingAttack);
	}

	if (AirAttack_01Action)
	{
		EnhancedInputComponent->BindAction(AirAttack_01Action, ETriggerEvent::Triggered, this, &ACCombatCharacter::OnAirAttack_01);
	}

	if (AirAttack_02Action)
	{
		EnhancedInputComponent->BindAction(AirAttack_02Action, ETriggerEvent::Triggered, this, &ACCombatCharacter::OnAirAttack_02);
	}
}

void ACCombatCharacter::OnDash()
{
	if (!IsValid(ActionComponent))
	{
		CLog::LogError("ActionComponent is not valid");
		return;
	}

	ActionComponent->SetAction(this, "Dash");
}

void ACCombatCharacter::OnAttack_01()
{
	if (!IsValid(ActionComponent))
	{
		CLog::LogError("ActionComponent is not valid");
		return;
	}

	if (bIsInAir)
	{
		ActionComponent->SetAction(this, "AirAttack_01");
	}
	else
	{
		ActionComponent->SetAction(this, "Attack_01");
	}
	
}

void ACCombatCharacter::OnAttack_02()
{
	if (!IsValid(ActionComponent))
	{
		CLog::LogError("ActionComponent is not valid");
		return;
	}

	ActionComponent->SetAction(this, "Attack_02");
}

void ACCombatCharacter::OnRisingAttack()
{
	if (!IsValid(ActionComponent))
	{
		CLog::LogError("ActionComponent is not valid");
		return;
	}

	bIsInAir = true;
	ActionComponent->SetAction(this, "RisingAttack");
}

void ACCombatCharacter::OnAirAttack_01()
{
	if (!IsValid(ActionComponent))
	{
		CLog::LogError("ActionComponent is not valid");
		return;
	}

	if (!GetCharacterMovement()->IsFalling())
	{
		return;
	}

	ActionComponent->SetAction(this, "AirAttack_01");
}


void ACCombatCharacter::OnAirAttack_02()
{
	if (!IsValid(ActionComponent))
	{
		CLog::LogError("ActionComponent is not valid");
		return;
	}

	ActionComponent->SetAction(this, "AirAttack_02");
}


void ACCombatCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	bIsInAir = false;
	CLog::LogError("Landed : " + bIsInAir);
}

