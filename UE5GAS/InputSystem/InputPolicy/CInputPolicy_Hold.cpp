#include "Components/Input/CInputPolicy_Hold.h"
#include "AbilitySystemComponent.h"

void UCInputPolicy_Hold::HandleInputPressed(UAbilitySystemComponent* ASC, const FGameplayTag& InputTag)
{
	if (!ASC || !InputTag.IsValid())
	{
		return;
	}

	for (const FGameplayAbilitySpec& AbilitySpec : ASC->GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			if (AbilitySpec.IsActive())
			{
				ASC->CancelAbilityHandle(AbilitySpec.Handle);
			}
			else
			{
				ASC->TryActivateAbility(AbilitySpec.Handle);
			}
			break;
		}
	}
}
