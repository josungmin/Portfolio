#pragma once
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IAbilityWidget.generated.h"


UINTERFACE(MinimalAPI)
class UIAbilityWidget : public UInterface
{
	GENERATED_BODY()
};


class DEUS_API IIAbilityWidget
{
	GENERATED_BODY()

public:
	virtual void BindAbility(class UCAbilityComponent* InAbilityComponent) = 0;
	virtual void UpdateAbilityValue(float NewValue) = 0;
};
