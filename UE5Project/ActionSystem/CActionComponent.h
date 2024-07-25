#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActionSystem/Enums/EStateType.h"
#include "CActionComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DEUS_API UCActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCActionComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnyWhere, Meta = (AllowPrivateAccess = "true"))
	EStateType CurrentState;

	UPROPERTY(BlueprintReadOnly, VisibleAnyWhere, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCAction> CurrentAction;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<class UCAction>> Actions;


public:
	FORCEINLINE UCAction* GetCurrentAction() const { return CurrentAction; }
	FORCEINLINE EStateType GetCurrentState() const { return CurrentState; }
	FORCEINLINE void ResetState() { SetState(EStateType::None); }
	void SetState(EStateType NewState);


public:
	UFUNCTION(BlueprintCallable)
	bool SetAction(AActor* Instigator, FName ActionName);

	UFUNCTION(BlueprintCallable)
	UCAction* FindActionByName(const FName& TargetActionName);

	// Action Class Bind Delegate
	UFUNCTION()
	void OnActionStarted();

	// Action Class Bind Delegate
	UFUNCTION()
	void OnActionEnded();

private:
	void InitializeActions();

protected:
	FTimerHandle StopActionTimerHandle;
	TMap<FName, UCAction*> ActionMap;
};
