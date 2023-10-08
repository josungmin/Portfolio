#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CCombatComponent.generated.h"

class ACWeaponBase;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DINGO_API UCCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCCombatComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	FORCEINLINE ACWeaponBase* GetMainWeapon() const { return MainWeapon; }
	void SetMainWeapon(ACWeaponBase* InWeapon);

	FORCEINLINE bool GetIsWeaponAttachToHand() const { return IsWeaponAttachToHand; }
	void SetIsWeaponAttachToHand(bool InBoolean);

private:
	class ACWeaponBase* MainWeapon = nullptr;
	bool IsWeaponAttachToHand = false;


public:
	FORCEINLINE int32 GetAttackCount() const { return AttackCount; }
	FORCEINLINE void SetAttackCount(int32 InCount) { AttackCount = InCount; }

	FORCEINLINE bool GetHasNextComboCommand() const { return bHasNextComboCommand; }
	FORCEINLINE void SetHasNextComboCommand(bool InBoolean) { bHasNextComboCommand = InBoolean; }

	void ResetAttack();

private:
	int32 AttackCount = 0;
	bool bHasNextComboCommand = false;
};
