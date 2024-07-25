#pragma once

#include "CoreMinimal.h"
#include "Game/Characters/CCharacterBase.h"
#include "CCombatCharacter.generated.h"


UCLASS()
class DEUS_API ACCombatCharacter : public ACCharacterBase
{
	GENERATED_BODY()

public:
	ACCombatCharacter();
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	class UCActionComponent* ActionComponent;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	class UCCombatComponent* CombatComponent;

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Input", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> DashAction;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Input", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> Attack_01Action;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Input", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> Attack_02Action;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Input", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> RisingAttackAction;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Input", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> AirAttack_01Action;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Input", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> AirAttack_02Action;

protected:
	void OnDash();

	void OnAttack_01();
	void OnAttack_02();
	
	void OnRisingAttack();
	void OnAirAttack_01();
	void OnAirAttack_02();

protected:
	virtual void Landed(const FHitResult& Hit) override;

private:
	bool bIsInAir = false;
};
