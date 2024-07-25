#pragma once

#include "CoreMinimal.h"
#include "ActionSystem/Actions/CBasicAction.h"
#include "CBasicAction_Dash.generated.h"


UCLASS()
class DEUS_API UCBasicAction_Dash : public UCBasicAction
{
	GENERATED_BODY()

public:
	UCBasicAction_Dash();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Action")
	float DashDistance;

public:
	virtual bool StartAction(AActor* Instigator) override;
	virtual bool EndAction(AActor* Instigator) override;

};
