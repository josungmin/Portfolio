#include "CCombatComponent.h"
#include "EquipmentSystem/CWeaponBase.h"
#include "Kismet/GameplayStatics.h"
#include "CollisionSystem/CCollisionComponent.h"


UCCombatComponent::UCCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UCCombatComponent::BeginPlay()
{
	Super::BeginPlay();

}


void UCCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}


void UCCombatComponent::ApplyDamage(AActor* Target, int32 Damage)
{
	if (!Target)
	{
		return;
	}

	UGameplayStatics::ApplyDamage(Target, 20, GetOwner()->GetInstigatorController(), GetOwner(), UDamageType::StaticClass());
}


void UCCombatComponent::ApplyDamage(const FHitResult& HitResult)
{
	UGameplayStatics::ApplyDamage(HitResult.GetActor(), 20, GetOwner()->GetInstigatorController(), GetOwner(), UDamageType::StaticClass());
}


void UCCombatComponent::SetMainWeapon(ACWeaponBase* InWeapon)
{
	if (IsValid(MainWeapon))
	{
		MainWeapon->Detach();
	}

	MainWeapon = InWeapon;

	MainWeapon->GetCollisionComponent()->OnHit.BindUObject(this, &UCCombatComponent::ApplyDamage);
}