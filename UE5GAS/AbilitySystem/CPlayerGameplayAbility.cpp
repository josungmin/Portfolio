#include "AbilitySystem/Abilities/CPlayerGameplayAbility.h"
#include "Characters/CPlayerCharacter.h"
#include "Controllers/CPlayerController.h"


ACPlayerCharacter* UCPlayerGameplayAbility::GetPlayerCharacterFromActorInfo()
{
	if (!CachedPlayerCharacter.IsValid())
	{
		CachedPlayerCharacter = Cast<ACPlayerCharacter>(CurrentActorInfo->AvatarActor);
	}

	return CachedPlayerCharacter.IsValid() ? CachedPlayerCharacter.Get() : nullptr;
}

ACPlayerController* UCPlayerGameplayAbility::GetPlayeroControllerFromActorInfo()
{
	if (!CachedPlayerController.IsValid())
	{
		CachedPlayerController = Cast<ACPlayerController>(CurrentActorInfo->PlayerController);
	}

	return CachedPlayerController.IsValid() ? CachedPlayerController.Get() : nullptr;
}

UPlayerCombatComponent* UCPlayerGameplayAbility::GetPlayerCombatComponent()
{
	return GetPlayerCharacterFromActorInfo()->GetPlayerCombatComponent();
}
