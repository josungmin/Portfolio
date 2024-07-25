#pragma once

#include "CoreMinimal.h"
#include "ActionSystem/Actions/CBasicAction.h"
#include "CBasicAction_RisingAttack.generated.h"


UCLASS()
class DEUS_API UCBasicAction_RisingAttack : public UCBasicAction
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Action")
	float RisingPower;
	
public:
	virtual bool StartAction(AActor* Instigator) override;
};
