#pragma once
#include "CoreMinimal.h"


class IModifierCalculate
{
public:
	virtual ~IModifierCalculate() = default;
	virtual float Calculate(float BaseValue, float ModifierValue) const = 0;
};
