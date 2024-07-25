#include "ActionSystem/Actions/CComboAction.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "Animation/AnimInstance.h"
#include "Components/SkeletalMeshComponent.h"

// Debug
#include "Utilities/CLog.h"


UCComboAction::UCComboAction()
{
	bIsComboAction = true;
	InitComboAction();
}


bool UCComboAction::StartAction(AActor* Instigator)
{
	if (!Instigator)
	{
		CLog::LogError(TEXT("Instigator is null"));
		return false;
	}

	if (ActionState == EActionState::Active)
	{
		bIsNextAnimation = true;
		return true;
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

	InitComboAction();
	PerformComboAction(Instigator);

	return true;
}


bool UCComboAction::EndAction(AActor* Instigator)
{
	bool Result = Super::EndAction(Instigator);
	if (!Result)
	{
		return false;
	}

	InitComboAction();

	return true;
}


float UCComboAction::GetDuration()
{
	return Animations[CurrentAnimationIndex].Duration;
}


void UCComboAction::NextComboAction(AActor* Instigator)
{
	if (!Instigator)
	{
		CLog::LogError(TEXT("Instigator is null"));
		return;
	}

	if (!bIsNextAnimation)
	{
		return;
	}

	CurrentAnimationIndex++;
	if (CurrentAnimationIndex >= Animations.Num())
	{
		CurrentAnimationIndex = 0;
	}

	// Initialization Next Combo Setting
	bIsNextAnimation = false;
	InitEndActionTimer(Instigator);

	PerformComboAction(Instigator);
}


void UCComboAction::InitComboAction()
{
	CurrentAnimationIndex = 0;
	bIsNextAnimation = false;
	CachedSkeletalMeshComponent = nullptr;
	CachedAnimInstance = nullptr;
}


void UCComboAction::PerformComboAction(AActor* Instigator)
{
	if (!Instigator)
	{
		CLog::LogError(TEXT("Instigator is null"));
		return;
	}

	if (!Animations.IsValidIndex(CurrentAnimationIndex))
	{
		CLog::LogError(TEXT("Invalid Animation Index : ") + FString::FromInt(CurrentAnimationIndex));
		return;
	}

	// AnimMontage Play
	if (!CachedSkeletalMeshComponent)
	{
		CachedSkeletalMeshComponent = Instigator->FindComponentByClass<USkeletalMeshComponent>();
		if (!CachedSkeletalMeshComponent)
		{
			CLog::LogError(TEXT("SkeletalMeshComponent is null"));
			return;
		}
	}

	if (!CachedAnimInstance)
	{
		CachedAnimInstance = CachedSkeletalMeshComponent->GetAnimInstance();
		if (!CachedAnimInstance)
		{
			CLog::LogError(TEXT("AnimInstance is null"));
			return;
		}
	}

	TObjectPtr<UAnimMontage> CurrentAnimation = Animations[CurrentAnimationIndex].ActionMontage;
	if (CurrentAnimation)
	{
		CachedAnimInstance->Montage_Play(CurrentAnimation);
	}
	else
	{
		CLog::LogError(TEXT("Montage is null"));
	}

	// Set End Action Timer
	SetEndActionTimer(Instigator);
}
