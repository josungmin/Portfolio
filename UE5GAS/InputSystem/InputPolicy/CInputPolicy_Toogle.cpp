#include "Components/Input/CInputPolicy_Toogle.h"
#include "AbilitySystemComponent.h"

void UCInputPolicy_Toogle::HandleInputPressed(UAbilitySystemComponent* ASC, const FGameplayTag& InputTag)
{
	if (!ASC || !InputTag.IsValid()) return;

	for (const FGameplayAbilitySpec& AbilitySpec : ASC->GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			ASC->TryActivateAbility(AbilitySpec.Handle);
			break;
		}
	}
}

void UCInputPolicy_Toogle::HandleInputReleased(UAbilitySystemComponent* ASC, const FGameplayTag& InputTag)
{
	if (!ASC || !InputTag.IsValid()) return;

	for (const FGameplayAbilitySpec& AbilitySpec : ASC->GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag) && AbilitySpec.IsActive())
		{
			ASC->CancelAbilityHandle(AbilitySpec.Handle);
			break;
		}
	}
}
