#include "ActionSystem/Actions/CComboAction_AirAttack.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"


UCComboAction_AirAttack::UCComboAction_AirAttack()
{

}


bool UCComboAction_AirAttack::StartAction(AActor* Instigator)
{
	bool Result = Super::StartAction(Instigator);
	if (!Result)
	{
		return false;
	}

	ACharacter* Character = Cast<ACharacter>(Instigator);
	if (Character)
	{
		SavedPositionZ = Character->GetActorLocation().Z;
		Character->GetCharacterMovement()->SetMovementMode(MOVE_None);
	}

	return true;
}


bool UCComboAction_AirAttack::EndAction(AActor* Instigator)
{
	Super::EndAction(Instigator);

	ACharacter* Character = Cast<ACharacter>(Instigator);
	if (Character)
	{
		//FVector CurrentLocation = Character->GetActorLocation();
		//CurrentLocation.Z = SavedPositionZ;
		//Character->SetActorLocation(CurrentLocation);
		Character->GetCharacterMovement()->SetMovementMode(MOVE_Falling);
	}

	return true;
}
