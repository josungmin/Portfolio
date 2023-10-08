#include "Components/CCharacterStateComponent.h"


UCCharacterStateComponent::UCCharacterStateComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCCharacterStateComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UCCharacterStateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UCCharacterStateComponent::SetState(ECharacterState NewState)
{
	if (CurrentState == NewState)
	{
		return;
	}

	if (!OnStateEnd.IsBound())
	{
		return;
	}

	OnStateEnd.Execute(CurrentState);
	CurrentState = NewState;

	if (!OnStateBegin.IsBound())
	{
		return;
	}

	OnStateBegin.Execute(CurrentState);
}

void UCCharacterStateComponent::ResetState()
{
	SetState(ECharacterState::None);
}

bool UCCharacterStateComponent::IsCurrentStateToAny(TArray<ECharacterState> InStates)
{
	return InStates.Contains(CurrentState);
}

