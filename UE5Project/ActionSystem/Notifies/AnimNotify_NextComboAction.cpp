#include "ActionSystem/Notifies/AnimNotify_NextComboAction.h"
#include "ActionSystem/CActionComponent.h"
#include "ActionSystem/Actions/CComboAction.h"

void UAnimNotify_NextComboAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	//FindComponentByClass

	if (!IsValid(MeshComp->GetOwner()))
	{
		return;
	}

	UCActionComponent* ActionComponent = MeshComp->GetOwner()->FindComponentByClass<UCActionComponent>();
	if (!ActionComponent)
	{
		return;
	}

	UCComboAction* ComboAction = Cast<UCComboAction>(ActionComponent->GetCurrentAction());
	if (!ComboAction)
	{
		return;
	}

	ComboAction->NextComboAction(MeshComp->GetOwner());
}
