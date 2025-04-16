#pragma once
#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "DataTypes/RoxyStructType.h"
#include "RoxyAbilitySystemComponent.generated.h"


UCLASS()
class ROXY_API URoxyAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Ability")
	bool TryActivateAbilityByTag(FGameplayTag AbilityTagToActivate);


	UFUNCTION(BlueprintCallable, Category = "Ability")
	void GrantPlayerWeaponAbilities(const TArray<FPlayerAbilitySet>& InDefaultWeaponAbilities, const TArray<TSubclassOf<UCPlayerGameplayAbility>>& InReactiveAbilities, int32 ApplyLevel, TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandles);

	UFUNCTION(BlueprintCallable, Category = "Ability")
	void RemovedPlayerWeaponAbilities(UPARAM(ref) TArray<FGameplayAbilitySpecHandle>& InSpecHandlesToRemove);

	UFUNCTION(BlueprintCallable, Category = "Ability")
	void SendGameplayEvent(const FGameplayTag& EventTag);
};
