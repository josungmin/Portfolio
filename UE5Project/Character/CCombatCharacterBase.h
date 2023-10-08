#pragma once

#include "CoreMinimal.h"
#include "Character/CCharacterBase.h"
#include "InputActionValue.h"
#include "Interfaces/ICombat.h"
#include "CCombatCharacterBase.generated.h"

UCLASS()
class DINGO_API ACCombatCharacterBase : public ACCharacterBase, public IICombat
{
	GENERATED_BODY()

public:
	ACCombatCharacterBase();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Component")
		TObjectPtr<class UCCombatComponent> CombatComponent;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Component")
		TObjectPtr<class UCCharacterStateComponent> CharacterStateComponent;

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Input", Meta = (AllowPrivateAccess = "true"))
		TObjectPtr<class UInputAction> DodgeAction;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Input", Meta = (AllowPrivateAccess = "true"))
		TObjectPtr<class UInputAction> ToggleEquipAction;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Input", Meta = (AllowPrivateAccess = "true"))
		TObjectPtr<class UInputAction> AttackAction;

public:
	FORCEINLINE TObjectPtr<class UCCombatComponent> GetCombatComponent() const { return CombatComponent; }

protected:
	void OnDodge();
	virtual void Dodging(int32 Index);
	virtual FRotator GetDesiredRotation() override;

	void OnEquip();

	void OnAttack();
	virtual void Attacking();
	virtual void CheckContinueAttack() override;
	virtual void ResetAttack() override;
	virtual void ResetCombat() override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

private:
	bool CanAttack();
	bool CanEquip();
	bool CanDodge();
};
