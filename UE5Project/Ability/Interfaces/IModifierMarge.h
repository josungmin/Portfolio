#pragma once
#include "CoreMinimal.h"


class IModifierMarge
{
public:
	virtual ~IModifierMarge() = default;
	virtual float Marge(float BaseValue, float ModifierValue) const = 0;
};
