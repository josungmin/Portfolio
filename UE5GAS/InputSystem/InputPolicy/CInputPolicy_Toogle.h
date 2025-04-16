#pragma once
#include "CoreMinimal.h"
#include "Components/Input/CInputPolicy.h"
#include "CInputPolicy_Toogle.generated.h"


UCLASS()
class ROXY_API UCInputPolicy_Toogle : public UCInputPolicy
{
	GENERATED_BODY()
	
public:
	virtual void HandleInputPressed(UAbilitySystemComponent* ASC, const FGameplayTag& InputTag) override;
	virtual void HandleInputReleased(UAbilitySystemComponent* ASC, const FGameplayTag& InputTag) override;
};
