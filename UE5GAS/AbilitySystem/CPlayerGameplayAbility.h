#pragma once
#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/RoxyGameplayAbility.h"
#include "CPlayerGameplayAbility.generated.h"

class ACPlayerCharacter;
class ACPlayerController;

UCLASS()
class ROXY_API UCPlayerGameplayAbility : public URoxyGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "Ability")
	ACPlayerCharacter* GetPlayerCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Ability")
	ACPlayerController* GetPlayeroControllerFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Ability")
	UPlayerCombatComponent* GetPlayerCombatComponent();
	
private:
	TWeakObjectPtr<ACPlayerCharacter> CachedPlayerCharacter;
	TWeakObjectPtr<ACPlayerController> CachedPlayerController;
};
