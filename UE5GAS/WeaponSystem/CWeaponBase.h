#pragma once
#include "CoreMinimal.h"
#include "Items/CAttachableBase.h"
#include "DataTypes/RoxyStructType.h"
#include "CWeaponBase.generated.h"

DECLARE_DELEGATE_OneParam(FOnTargetInteractedDelegate, const FWeaponHitInfo&)


UENUM(BlueprintType)
enum class EWeaponState : uint8
{
	Unequipped		UMETA(DisplayName = "Unequipped"),
	Equipped		UMETA(DisplayName = "Equipped"),
	Tracing			UMETA(DisplayName = "Tracing"),
	Drawn			UMETA(DisplayName = "Drawn"),
};

UCLASS()
class ROXY_API ACWeaponBase : public ACAttachableBase
{
	GENERATED_BODY()

public:
	ACWeaponBase();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|WeaponBase")
	EWeaponState WeaponState;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Item|WeaponBase")
	FName TraceStartSocketName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Item|WeaponBase")
	FName TraceEndSocketName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Item|WeaponBase")
	float TraceRadius;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Item|WeaponBase", Meta = (AllowPrivateAccess = "true"))
	TArray<TEnumAsByte<EObjectTypeQuery>> CollisionObjectTypes;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Item|WeaponBase", Meta = (AllowPrivateAccess = "true"))
	TArray<AActor*> ActorsToIgnore;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Item|WeaponBase", Meta = (AllowPrivateAccess = "true"))
	TSet<AActor*> AlreadyHitActors;

public:
	UFUNCTION(BlueprintCallable)
	virtual void OnEquipWeapon();

	UFUNCTION(BlueprintCallable)
	virtual void OnUnequipWeapon();

public:
	UFUNCTION(BlueprintCallable)
	void StartTrace();

	UFUNCTION(BlueprintCallable)
	void StopTrace();

	UFUNCTION(BlueprintCallable)
	void PerformSweep();

public:
	FOnTargetInteractedDelegate OnWeaponHitTarget;

	FORCEINLINE void AddActorToIgnore(AActor* InActor) { ActorsToIgnore.AddUnique(InActor); }
	FORCEINLINE void RemoveActorToIgnore(AActor* InActor) { ActorsToIgnore.Remove(InActor); } 

private:
	bool bIsTracing = false;
};

/*
1. ������ ���� ���� ����
������ ����(������, ����, �浹 ���� Ȱ��ȭ)�� ��Ȯ�ϰ� �����Ͽ� �����Ͽ�, ���� ��ȯ ���� ���׸� ���̰� �ڵ� �������� ����
������ ���¸� ��Ȯ�� �����ϴ� ���� �ӽ��� ���������ν�, �� ���¿��� ���Ǵ� �۾��� ��ȯ�� ����ϰ� ���� ��Ȳ�� ������ �� �־� �ڵ� �������� ���˴ϴ�.

2. �浹 ������ ���� ����ü ����
�ܼ��� ��Ʈ�� ���͸� �����ϴ°��� �ƴ� �浹 ��ġ, ������ �� ���� ������ �Բ� ������ �� �ֵ��� ����ü�� �����ϰ� �̸� ���ڷ� ���
��Ʈ �̺�Ʈ�� �ܼ� ���� ���޿��� ���, ������, ��Ʈ ��ġ �� �߰� ������ ������ ����ü�� �����Ͽ� ���� �����÷��� ����(��: ������ ���, Ư�� ȿ�� ó��) Ȯ���� ����

3. Trace�� �浹ó��
��������
*/