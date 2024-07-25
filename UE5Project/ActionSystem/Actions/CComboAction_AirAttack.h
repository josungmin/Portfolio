#pragma once

#include "CoreMinimal.h"
#include "ActionSystem/Actions/CComboAction.h"
#include "CComboAction_AirAttack.generated.h"


UCLASS()
class DEUS_API UCComboAction_AirAttack : public UCComboAction
{
	GENERATED_BODY()

public:
	UCComboAction_AirAttack();
	
public:
	virtual bool StartAction(AActor* Instigator) override;
	virtual bool EndAction(AActor* Instigator) override;

private:
	float SavedPositionZ;
};
