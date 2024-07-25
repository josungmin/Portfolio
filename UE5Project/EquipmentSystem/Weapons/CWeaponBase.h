#pragma once

#include "CoreMinimal.h"
#include "Equipment/CEquipableBase.h"
#include "Enums/EWeaponType.h"
#include "CWeaponBase.generated.h"

UCLASS()
class DINGO_API ACWeaponBase : public ACEquipableBase
{
	GENERATED_BODY()

public:
	ACWeaponBase();

public:
	static ACWeaponBase* Spawn(UWorld* InWorld, UClass* InClass, AActor* InOwner);

public:
	virtual void OnEquiped() override;

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Initialization")
		FName HandSocketName;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Initialization")
		float Damage;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Initialization", Meta = (AllowPrivateAccess = "true"))
		EWeaponType WeaponType = EWeaponType::None;


protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Component")
		TObjectPtr<class UCCollisionComponent> CollisionComponent;


protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animation", Meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UAnimMontage> EquipMontage;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animation", Meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UAnimMontage> UnequipMontage;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animation", Meta = (AllowPrivateAccess = "true"))
		TArray<TObjectPtr<UAnimMontage>> AttackMontages;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animation", Meta = (AllowPrivateAccess = "true"))
		TArray<TObjectPtr<UAnimMontage>> DodgeMontages;

public:
	FORCEINLINE FName GetHandSocketName() const { return HandSocketName; }

	FORCEINLINE TObjectPtr<UAnimMontage> GetEquipMontage() const { return EquipMontage; }
	FORCEINLINE TObjectPtr<UAnimMontage> GetUnequipMontage() const { return UnequipMontage; }
	FORCEINLINE TArray<TObjectPtr<UAnimMontage>> GetAttackMontages() const { return AttackMontages; }
	FORCEINLINE TArray<TObjectPtr<UAnimMontage>> GetDodgeMontages() const { return DodgeMontages; }

protected:
	UFUNCTION()
		virtual void OnHit(FHitResult InHitResult);
};
