#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IInteractabl.generated.h"

UINTERFACE(MinimalAPI)
class UIInteractabl : public UInterface
{
	GENERATED_BODY()
};

class DINGO_API IIInteractabl
{
	GENERATED_BODY()

public:
	virtual void Interact(AActor* InCaller) = 0;
};
