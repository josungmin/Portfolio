#include "Items/Weapon/CPlayerWeapon.h"

void ACPlayerWeapon::OnDrawWeapon()
{
	//TODO : 임시코드
	OnAttach(DrawSocketName);
}

void ACPlayerWeapon::OnSheathedWeapon()
{
	//TODO : 임시코드
	OnAttach();
}

void ACPlayerWeapon::SetGrantedAbilitySpecHandles(const TArray<FGameplayAbilitySpecHandle>& InSpecHandles)
{
	GrantedAbilitySpecHandles = InSpecHandles;
}

TArray<FGameplayAbilitySpecHandle> ACPlayerWeapon::GetGrantedAbilitySpecHandles() const
{
	return GrantedAbilitySpecHandles;
}
