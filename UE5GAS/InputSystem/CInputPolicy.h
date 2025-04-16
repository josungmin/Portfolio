#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTagContainer.h"
#include "CInputPolicy.generated.h"

class UAbilitySystemComponent;

UCLASS(Abstract, BlueprintType, EditInlineNew)
class ROXY_API UCInputPolicy : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "InputPolicy")
	virtual void HandleInputPressed(UAbilitySystemComponent* ASC, const FGameplayTag& InputTag);

	UFUNCTION(BlueprintCallable, Category = "InputPolicy")
	virtual void HandleInputReleased(UAbilitySystemComponent* ASC, const FGameplayTag& InputTag);
};
