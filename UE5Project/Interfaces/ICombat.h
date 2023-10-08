#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ICombat.generated.h"

UINTERFACE(MinimalAPI)
class UICombat : public UInterface
{
	GENERATED_BODY()
};

class DINGO_API IICombat
{
	GENERATED_BODY()

public:
	virtual void ResetCombat() = 0;

	virtual void CheckContinueAttack() = 0;
	virtual void ResetAttack() = 0;
	virtual FRotator GetDesiredRotation() = 0;
};
