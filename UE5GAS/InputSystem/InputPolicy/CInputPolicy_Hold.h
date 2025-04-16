#pragma once
#include "CoreMinimal.h"
#include "Components/Input/CInputPolicy.h"
#include "CInputPolicy_Hold.generated.h"


UCLASS()
class ROXY_API UCInputPolicy_Hold : public UCInputPolicy
{
	GENERATED_BODY()
	
public:
	virtual void HandleInputPressed(UAbilitySystemComponent* ASC, const FGameplayTag& InputTag) override;
};
