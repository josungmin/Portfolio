#include "Items/Weapon/CPlayerWeapon.h"

void ACPlayerWeapon::OnDrawWeapon()
{
	//TODO : �ӽ��ڵ�
	OnAttach(DrawSocketName);
}

void ACPlayerWeapon::OnSheathedWeapon()
{
	//TODO : �ӽ��ڵ�
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
