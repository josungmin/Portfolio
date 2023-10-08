// Base
#include "Character/CCombatCharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
// Input
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
// State Manage
#include "Components/CCharacterStateComponent.h"
// Combat
#include "Components/CCombatComponent.h"
#include "Interfaces/IWeapon.h"
#include "Equipment/Weapons/CWeaponBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
//Interaction
#include "Interfaces/IInteractabl.h"
// Debug
#include "Utilities/CLog.h"



ACCombatCharacterBase::ACCombatCharacterBase()
{
	// Cambat Section
	CombatComponent = CreateDefaultSubobject<UCCombatComponent>(TEXT("CombatComponent"));

	// Character State Sction
	CharacterStateComponent = CreateDefaultSubobject<UCCharacterStateComponent>(TEXT("CharacterStateComponent"));
}

void ACCombatCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void ACCombatCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACCombatCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (DodgeAction)
	{
		EnhancedInputComponent->BindAction(DodgeAction, ETriggerEvent::Triggered, this, &ACCombatCharacterBase::OnDodge);
	}

	if (ToggleEquipAction)
	{
		EnhancedInputComponent->BindAction(ToggleEquipAction, ETriggerEvent::Triggered, this, &ACCombatCharacterBase::OnEquip);
	}

	if (AttackAction)
	{
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &ACCombatCharacterBase::OnAttack);
	}
}

void ACCombatCharacterBase::OnDodge()
{
	if (!CanDodge())
	{
		return;
	}

	if (!CombatComponent->GetMainWeapon())
	{
		PrintLine();
		UE_LOG(Caiman, Error, TEXT("Weapon is NULL"));
		return;
	}

	Dodging(0);
}

void ACCombatCharacterBase::Dodging(int32 Index)
{
	// Initialization
	TArray<UAnimMontage*> DodgeMontages;
	DodgeMontages = CombatComponent->GetMainWeapon()->GetDodgeMontages();

	if (!DodgeMontages.IsValidIndex(Index))
	{
		PrintLine();
		UE_LOG(Caiman, Error, TEXT("DodgeMontages Out Of Range"));
		return;
	}

	UAnimMontage* DodgeMontage;
	DodgeMontage = DodgeMontages[Index];

	if (!DodgeMontage)
	{
		PrintLine();
		UE_LOG(Caiman, Error, TEXT("DodgeMontage is NULL"));
		return;
	}

	// Excute
	CharacterStateComponent->SetState(ECharacterState::DodegState);
	GetMesh()->GetAnimInstance()->Montage_Play(DodgeMontage);
}

FRotator ACCombatCharacterBase::GetDesiredRotation()
{
	bool Result = GetCharacterMovement()->GetLastInputVector().Equals(FVector(0, 0, 0), 0);

	if (!Result)
	{
		return GetActorRotation();
	}

	return UKismetMathLibrary::MakeRotFromX(GetCharacterMovement()->GetLastInputVector());
}

void ACCombatCharacterBase::OnEquip()
{
	ACWeaponBase* Weapon = CombatComponent->GetMainWeapon();

	if (!Weapon)
	{
		PrintLine();
		UE_LOG(Caiman, Error, TEXT("Weapon is NULL"));
		return;
	}

	if (!CanEquip())
	{
		return;
	}

	CharacterStateComponent->SetState(ECharacterState::GeneralState);

	if (!CombatComponent->GetIsWeaponAttachToHand())
	{
		GetMesh()->GetAnimInstance()->Montage_Play(Weapon->GetEquipMontage());
	}
	else
	{
		GetMesh()->GetAnimInstance()->Montage_Play(Weapon->GetUnequipMontage());
	}
}

void ACCombatCharacterBase::OnAttack()
{
	if (!CanAttack())
	{
		return;
	}

	if (!CombatComponent->GetMainWeapon())
	{
		PrintLine();
		UE_LOG(Caiman, Error, TEXT("Weapon is NULL"));
		return;
	}

	if (CharacterStateComponent->GetCurrentState() == ECharacterState::AttackState)
	{
		CombatComponent->SetHasNextComboCommand(true);
	}
	else
	{
		Attacking();
	}
}

void ACCombatCharacterBase::Attacking()
{
	// Initialization
	int32 AttackCount = CombatComponent->GetAttackCount();

	TArray<UAnimMontage*> AttackMontages;
	AttackMontages = CombatComponent->GetMainWeapon()->GetAttackMontages();

	if (!AttackMontages.IsValidIndex(AttackCount))
	{
		PrintLine();
		UE_LOG(Caiman, Error, TEXT("AttackMontages Out Of Range"));
		return;
	}

	UAnimMontage* AttackMontage;
	AttackMontage = AttackMontages[AttackCount];

	if (!AttackMontage)
	{
		PrintLine();
		UE_LOG(Caiman, Error, TEXT("AttackMontage is NULL"));
		return;
	}

	// Excute
	CharacterStateComponent->SetState(ECharacterState::AttackState);
	CombatComponent->SetAttackCount(AttackCount + 1);
	if (AttackMontages.Num() - 1 < CombatComponent->GetAttackCount())
	{
		CombatComponent->SetAttackCount(0);
	}

	GetMesh()->GetAnimInstance()->Montage_Play(AttackMontage);
}

void ACCombatCharacterBase::CheckContinueAttack()
{
	if (!CombatComponent->GetHasNextComboCommand())
	{
		return;
	}

	CombatComponent->SetHasNextComboCommand(false);


	if (CharacterStateComponent->GetCurrentState() == ECharacterState::AttackState)
	{
		CharacterStateComponent->SetState(ECharacterState::None);
	}


	Attacking();
}

void ACCombatCharacterBase::ResetAttack()
{
	CombatComponent->ResetAttack();
}

void ACCombatCharacterBase::ResetCombat()
{
	ResetAttack();
	CharacterStateComponent->ResetState();
}

float ACCombatCharacterBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	return Damage;
}

bool ACCombatCharacterBase::CanAttack()
{
	TArray<ECharacterState> Conditions =
	{
		ECharacterState::GeneralState,
		ECharacterState::DodegState,
		ECharacterState::DeadState,
		ECharacterState::DisabledState
	};

	const bool Result = !CharacterStateComponent->IsCurrentStateToAny(Conditions);

	return !Result && !GetCharacterMovement()->IsFalling();
}

bool ACCombatCharacterBase::CanEquip()
{
	TArray<ECharacterState> Conditions =
	{
		ECharacterState::GeneralState,
		ECharacterState::AttackState,
		ECharacterState::DodegState,
		ECharacterState::DeadState,
		ECharacterState::DisabledState
	};

	const bool Result = CharacterStateComponent->IsCurrentStateToAny(Conditions);

	return !Result && !GetCharacterMovement()->IsFalling();
}

bool ACCombatCharacterBase::CanDodge()
{
	TArray<ECharacterState> Conditions =
	{
		ECharacterState::GeneralState,
		ECharacterState::DodegState,
		ECharacterState::DeadState,
		ECharacterState::DisabledState
	};

	const bool Result = CharacterStateComponent->IsCurrentStateToAny(Conditions);

	return !Result && !GetCharacterMovement()->IsFalling();
}