#pragma once
#include "CoreMinimal.h"
#include "Components/Input/CInputPolicy.h"
#include "CInputPolicy_Combo.generated.h"


UCLASS()
class ROXY_API UCInputPolicy_Combo : public UCInputPolicy
{
	GENERATED_BODY()
	
public:
	virtual void HandleInputPressed(UAbilitySystemComponent* ASC, const FGameplayTag& InputTag) override;

private:
	const FGameplayTag ContinueComboTag = FGameplayTag::RequestGameplayTag("Player.Status.ContinueCombo");
};