#include "ActionSystem/CActionComponent.h"
#include "ActionSystem/CAction.h"
#include "TimerManager.h"
#include "Engine/World.h"

// Debug
#include "Utilities/CLog.h"

UCActionComponent::UCActionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	CurrentState = EStateType::General;

}


void UCActionComponent::BeginPlay()
{
	Super::BeginPlay();
	InitializeActions();

}


void UCActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}


void UCActionComponent::SetState(EStateType NewState)
{
	if (CurrentState == NewState)
	{
		CLog::LogWarning("Attempted to set the same state: " + StaticEnum<EStateType>()->GetValueAsString(CurrentState));
		return;
	}

	CurrentState = NewState;
}


bool UCActionComponent::SetAction(AActor* Instigator, FName ActionName)
{
	UCAction* NewAction = FindActionByName(ActionName);
	if (NewAction == nullptr)
	{
		CLog::LogError(ActionName.ToString() + TEXT(" is not Found"));
		return false;
	}

	if (!NewAction->CanStartAction(CurrentState))
	{
		CLog::LogError(TEXT("Cannot changed action"));
		return false;
	}

	// CurrentAction->EndAction(Instigator);
	CurrentAction = NewAction;
	CurrentAction->StartAction(Instigator);

	return true;
}


UCAction* UCActionComponent::FindActionByName(const FName& TargetActionName)
{
	if (UCAction** FoundAction = ActionMap.Find(TargetActionName))
	{
		return *FoundAction;
	}

	return nullptr;
}


void UCActionComponent::InitializeActions()
{
	for (TSubclassOf<UCAction> ActionClass : Actions)
	{
		UCAction* ActionInstance = ActionClass.GetDefaultObject();
		if (ActionInstance)
		{
			ActionInstance->OnActionStarted.AddUniqueDynamic(this, &UCActionComponent::OnActionStarted);
			ActionInstance->OnActionEnded.AddUniqueDynamic(this, &UCActionComponent::OnActionEnded);

			ActionMap.Add(ActionInstance->GetActionName(), ActionInstance);
		}
	}
}


void UCActionComponent::OnActionStarted()
{
	SetState(CurrentAction->GetStateType());

	//CLog::LogWarning(TEXT("Enter State : ") + StaticEnum<EStateType>()->GetValueAsString(CurrentState));
}


void UCActionComponent::OnActionEnded()
{
	SetState(EStateType::General);

	//CLog::LogWarning(TEXT("Exit State : ") + StaticEnum<EStateType>()->GetValueAsString(CurrentState));
}
