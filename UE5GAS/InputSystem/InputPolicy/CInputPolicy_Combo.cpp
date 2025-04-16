#include "Components/Input/CInputPolicy_Combo.h"
#include "AbilitySystemComponent.h"


void UCInputPolicy_Combo::HandleInputPressed(UAbilitySystemComponent* ASC, const FGameplayTag& InputTag)
{
	if (!ASC || !InputTag.IsValid()) return;

	for (const FGameplayAbilitySpec& AbilitySpec : ASC->GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			if (AbilitySpec.IsActive() && !ASC->HasMatchingGameplayTag(ContinueComboTag))
			{
				ASC->AddLooseGameplayTag(ContinueComboTag);
			}
			else
			{
				ASC->TryActivateAbility(AbilitySpec.Handle);
			}

			break;
		}
	}
}
