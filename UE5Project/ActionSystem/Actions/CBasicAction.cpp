#include "ActionSystem/Actions/CBasicAction.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimInstance.h"

// Debug
#include "Utilities/CLog.h"


UCBasicAction::UCBasicAction()
{
	bIsComboAction = false;
}

float UCBasicAction::GetDuration()
{
	return Duration;
}

bool UCBasicAction::IsProgressComboAction()
{
	return false;
}

bool UCBasicAction::StartAction(AActor* Instigator)
{
	bool Result = Super::StartAction(Instigator);
	if (!Result)
	{
		return false;
	}

	// AnimMontage Play
	USkeletalMeshComponent* SkeletalMeshComponent = Instigator->FindComponentByClass<USkeletalMeshComponent>();
	if (!SkeletalMeshComponent)
	{
		CLog::LogError(TEXT("SkeletalMeshComponent is null"));
		return false;
	}

	UAnimInstance* AnimInstance = SkeletalMeshComponent->GetAnimInstance();
	if (!AnimInstance)
	{
		CLog::LogError(TEXT("AnimInstance is null"));
		return false;
	}

	AnimInstance->Montage_Play(Animation);

	return true;
}


bool UCBasicAction::EndAction(AActor* Instigator)
{
	bool Result = Super::EndAction(Instigator);
	if (!Result)
	{
		return false;
	}

	return true;
}
