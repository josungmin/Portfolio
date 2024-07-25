#include "ActionSystem/CAction.h"
#include "TimerManager.h"
#include "Engine/World.h"

// Debug
#include "Utilities/CLog.h"

UCAction::UCAction()
{
	ActionState = EActionState::Ready;
}


bool UCAction::StartAction(AActor* Instigator)
{
	if (!Instigator)
	{
		CLog::LogError(TEXT("Instigator is null"));
		return false;
	}

	if (ActionState != EActionState::Ready)
	{
		CLog::LogWarning(ActionName.ToString() + TEXT(" is not Ready"));
		return false;
	}

	// Excute extra functions in StartAction
	if (OnActionStarted.IsBound())
	{
		OnActionStarted.Broadcast();
	}

	// Set Action State
	ActionState = EActionState::Active;

	// Set End Action Timer
	SetEndActionTimer(Instigator);

	// CLog::Log("Start Action : " + GetActionName().ToString());
	return true;
}


bool UCAction::EndAction(AActor* Instigator)
{
	if (!Instigator)
	{
		CLog::LogError(TEXT("Instigator is null"));
		return false;
	}

	if (ActionState != EActionState::Active)
	{
		CLog::LogWarning(ActionName.ToString() + TEXT(" is not Active"));
		return false;
	}

	// Excute extra functions in EndAction
	if (OnActionEnded.IsBound())
	{
		OnActionEnded.Broadcast();
	}

	// Set Action State
	ActionState = EActionState::Cooldown;

	// Set Cooldown Timer
	SetCooldownTimer(Instigator);

	// Initialization End Action Timer
	InitEndActionTimer(Instigator);

	// CLog::LogWarning("End Action : " + GetActionName().ToString());
	return true;
}


void UCAction::CooldownComplete(AActor* Instigator)
{
	// Initialization Cooldown Timer
	InitCooldownTimer(Instigator);

	// Set Action State
	ActionState = EActionState::Ready;

	// CLog::LogWarning("CooldownComplete : " + GetActionName().ToString());
}


bool UCAction::CanStartAction(EStateType CurrentStateType)
{
	return !UnchangeableStates.Contains(CurrentStateType);
}


float UCAction::GetDuration()
{
	return -1.0f;
}


void UCAction::SetEndActionTimer(AActor* Instigator)
{
	if (!Instigator)
	{
		CLog::LogError(TEXT("Instigator is null"));
		return;
	}

	UWorld* World = Instigator->GetWorld();
	if (!World)
	{
		CLog::LogError(TEXT("World is null"));
		return;
	}

	if (!World->GetTimerManager().IsTimerActive(EndActionTimerHandle))
	{
		FTimerDelegate TimerDel;
		TimerDel.BindUFunction(this, FName("EndAction"), Instigator);

		World->GetTimerManager().SetTimer
		(
			EndActionTimerHandle,
			TimerDel,
			GetDuration(),
			false
		);
	}
	else
	{
		CLog::LogError(TEXT("EndActionTimer is active"));
		return;
	}

	// CLog::LogWarning("Set EndAction Timer : " + GetActionName().ToString());
}


void UCAction::InitEndActionTimer(AActor* Instigator)
{
	if (!Instigator)
	{
		CLog::LogError(TEXT("Instigator is null"));
		return;
	}

	UWorld* World = Instigator->GetWorld();
	if (!World)
	{
		CLog::LogError(TEXT("World is null"));
		return;
	}

	if (World->GetTimerManager().IsTimerActive(EndActionTimerHandle))
	{
		World->GetTimerManager().ClearTimer(EndActionTimerHandle);
	}

	//if (Instigator->GetWorld()->GetTimerManager().IsTimerActive(EndActionTimerHandle))
	//{
	//	Instigator->GetWorld()->GetTimerManager().ClearTimer(EndActionTimerHandle);
	//}

	// CLog::LogWarning("Init EndAction Timer : " + GetActionName().ToString());
}


void UCAction::SetCooldownTimer(AActor* Instigator)
{
	if (!Instigator)
	{
		CLog::LogError(TEXT("Instigator is null"));
		return;
	}

	if (Cooldown >= 0.0f)
	{
		CooldownComplete(Instigator);
		return;
	}

	UWorld* World = Instigator->GetWorld();
	if (!World)
	{
		CLog::LogError(TEXT("World is null"));
		return;
	}

	if (!World->GetTimerManager().IsTimerActive(CooldownTimerHandle))
	{
		FTimerDelegate TimerDel;
		TimerDel.BindUFunction(this, FName("CooldownComplete"), Instigator);

		World->GetTimerManager().SetTimer
		(
			CooldownTimerHandle,
			TimerDel,
			Cooldown,
			false
		);
	}
	else
	{
		CLog::LogError(TEXT("CooldownTimer is active"));
		return;
	}

	// CLog::LogWarning("Set Cooldown Timer : " + GetActionName().ToString());
}


void UCAction::InitCooldownTimer(AActor* Instigator)
{
	if (!Instigator)
	{
		CLog::LogError(TEXT("Instigator is null"));
		return;
	}

	UWorld* World = Instigator->GetWorld();
	if (!World)
	{
		CLog::LogError(TEXT("World is null"));
		return;
	}

	if (World->GetTimerManager().IsTimerActive(CooldownTimerHandle))
	{
		World->GetTimerManager().ClearTimer(CooldownTimerHandle);
	}

	//if (Instigator->GetWorld()->GetTimerManager().IsTimerActive(CooldownTimerHandle))
	//{
	//	Instigator->GetWorld()->GetTimerManager().ClearTimer(CooldownTimerHandle);
	//}

	// CLog::LogWarning("Init Cooldown Timer : " + GetActionName().ToString());
}
