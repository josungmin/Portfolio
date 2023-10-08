#include "Components/CCombatComponent.h"
#include "Character/CCharacterBase.h"
#include "Interfaces/IWeapon.h"
#include "Equipment/Weapons/CWeaponBase.h"

UCCombatComponent::UCCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UCCombatComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UCCombatComponent::SetMainWeapon(ACWeaponBase* InWeapon)
{
	if (MainWeapon)
	{
		MainWeapon->OnUnequiped();
		MainWeapon->Destroy();
		MainWeapon = nullptr;
	}

	MainWeapon = InWeapon;
}

void UCCombatComponent::SetIsWeaponAttachToHand(bool InBoolean)
{
	IsWeaponAttachToHand = InBoolean;

	ACCharacterBase* Owner = Cast<ACCharacterBase>(GetOwner());

	// Animation Update
	IIWeapon* AnimBP = Cast<IIWeapon>(Owner->GetMesh()->GetAnimInstance());
	AnimBP->SetIsAttachedHand(InBoolean);
}

void UCCombatComponent::ResetAttack()
{
	AttackCount = 0;
	bHasNextComboCommand = false;
}

