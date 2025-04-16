#pragma once
#include "CoreMinimal.h"
#include "Items/Weapon/CWeaponBase.h"
#include "GameplayAbilitySpecHandle.h"
#include "CPlayerWeapon.generated.h"


UCLASS()
class ROXY_API ACPlayerWeapon : public ACWeaponBase
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item|PlayerWeapon", Meta = (AllowPrivateAccess = "true"))
	FName DrawSocketName;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item|PlayerWeapon", Meta = (AllowPrivateAccess = "true"))
	FPlayerWeaponData PlayerWeaponData;

public:
	UFUNCTION(BlueprintCallable)
	void OnDrawWeapon();

	UFUNCTION(BlueprintCallable)
	void OnSheathedWeapon();

public:
	UFUNCTION(BlueprintCallable)
	void SetGrantedAbilitySpecHandles(const TArray<FGameplayAbilitySpecHandle>& InSpecHandles);

	UFUNCTION(BlueprintCallable)
	TArray<FGameplayAbilitySpecHandle> GetGrantedAbilitySpecHandles() const;

private:
	TArray<FGameplayAbilitySpecHandle> GrantedAbilitySpecHandles;
};
