#pragma once

#include "CoreMinimal.h"
#include "ActionSystem/CAction.h"
#include "CBasicAction.generated.h"


UCLASS()
class DEUS_API UCBasicAction : public UCAction
{
	GENERATED_BODY()

public:
	UCBasicAction();
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Action")
	TObjectPtr<UAnimMontage> Animation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Action")
	float Duration;

public:
	virtual float GetDuration() final;
	virtual bool IsProgressComboAction() final;

public:
	virtual bool StartAction(AActor* Instigator) override;
	virtual bool EndAction(AActor* Instigator) override;
};
