#include "ActionSystem/Actions/CBasicAction_Dash.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"


UCBasicAction_Dash::UCBasicAction_Dash()
{

}


bool UCBasicAction_Dash::StartAction(AActor* Instigator)
{
	bool Result = Super::StartAction(Instigator);
	if (!Result)
	{
		return false;
	}

	FVector StartLocation = Instigator->GetActorLocation();
	FVector ForwardVector = Instigator->GetActorForwardVector();
	FVector EndLocation = StartLocation + (ForwardVector * DashDistance);

	// ����� ��ǥ ��ġ (DashEndLocation)���� �浹�� ����
	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(Instigator);

	bool bHit = Instigator->GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECC_Visibility,
		CollisionParams
	);

	// �浹�� ������ ��� �浹 ���������� �̵�
	if (bHit)
	{
		EndLocation = HitResult.Location;
	}

	if (ACharacter* Character = Cast<ACharacter>(Instigator))
	{
		Character->GetCharacterMovement()->BrakingFrictionFactor = 0.0f;
		Character->LaunchCharacter((EndLocation - StartLocation).GetSafeNormal() * (DashDistance / Duration), true, true);
	}

	return false;
}


bool UCBasicAction_Dash::EndAction(AActor* Instigator)
{
	bool Result = Super::EndAction(Instigator);
	if (!Result)
	{
		return false;
	}

	if (ACharacter* Character = Cast<ACharacter>(Instigator))
	{
		Character->GetCharacterMovement()->StopMovementImmediately();
		Character->GetCharacterMovement()->BrakingFrictionFactor = 2.0f;
	}

	return true;
}
