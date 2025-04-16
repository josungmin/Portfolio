#include "Components/Input/CInputPolicy_Default.h"
#include "AbilitySystemComponent.h"

void UCInputPolicy_Default::HandleInputPressed(UAbilitySystemComponent* ASC, const FGameplayTag& InputTag)
{
	if (!ASC || !InputTag.IsValid())
	{
		return;
	}

	for (const FGameplayAbilitySpec& AbilitySpec : ASC->GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			ASC->TryActivateAbility(AbilitySpec.Handle);
			break;
		}
	}
}
