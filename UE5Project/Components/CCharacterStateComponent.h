#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ECharacterState.h"
#include "CCharacterStateComponent.generated.h"

DECLARE_DELEGATE_OneParam(FOnStateBeginSignature, ECharacterState);
DECLARE_DELEGATE_OneParam(FOnStateEndSignature, ECharacterState);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DINGO_API UCCharacterStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCCharacterStateComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	FORCEINLINE ECharacterState GetCurrentState() const { return CurrentState; }
	void SetState(ECharacterState NewState);
	void ResetState();

	bool IsCurrentStateToAny(TArray<ECharacterState> InStates);

public:
	FOnStateBeginSignature OnStateBegin;
	FOnStateEndSignature OnStateEnd;

private:
	ECharacterState CurrentState = ECharacterState::None;
};
