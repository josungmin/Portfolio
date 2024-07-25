#pragma once

#include "CoreMinimal.h"
#include "ActionSystem/CAction.h"
#include "CComboAction.generated.h"

USTRUCT(BlueprintType)
struct FComboActionAnimation
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAnimMontage> ActionMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Duration;
};

UCLASS()
class DEUS_API UCComboAction : public UCAction
{
	GENERATED_BODY()

public:
	UCComboAction();
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Action")
	TArray<FComboActionAnimation> Animations;

public:
	virtual bool StartAction(AActor* Instigator) override;
	virtual bool EndAction(AActor* Instigator) override;

public:
	virtual float GetDuration() final;


public:
	/* Call from Animation Notify */
	UFUNCTION(BlueprintCallable)
	virtual void NextComboAction(AActor* Instigator);

	/* Call from Animation Notify */
	UFUNCTION(BlueprintCallable)
	virtual void InitComboAction();

protected:
	virtual void PerformComboAction(AActor* Instigator);

protected:
	bool bIsNextAnimation;
	int32 CurrentAnimationIndex;

	// Cached Components
	USkeletalMeshComponent* CachedSkeletalMeshComponent;
	UAnimInstance* CachedAnimInstance;

};
