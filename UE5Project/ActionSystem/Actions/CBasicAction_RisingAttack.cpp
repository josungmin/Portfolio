#include "ActionSystem/Actions/CBasicAction_RisingAttack.h"
#include "GameFramework/Character.h"
#include "Utilities/CLog.h"

bool UCBasicAction_RisingAttack::StartAction(AActor* Instigator)
{
	bool Result = Super::StartAction(Instigator);
    if (!Result)
    {
        return false;
    }

    ACharacter* Character = Cast<ACharacter>(Instigator);
    if (!Character)
    {
        CLog::LogError("Instigator is not a character");
        return false;
    }

    FVector LaunchVelocity = FVector(0, 0, RisingPower);
    Character->LaunchCharacter(LaunchVelocity, true, true);

    return true;
}
