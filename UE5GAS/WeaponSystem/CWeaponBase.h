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
1. 무기의 상태 관리 도입
무기의 상태(미장착, 장착, 충돌 검출 활성화)를 명확하게 구분하여 관리하여, 상태 전환 관련 버그를 줄이고 코드 가독성을 높임
무기의 상태를 명확히 구분하는 상태 머신을 도입함으로써, 각 상태에서 허용되는 작업과 전환을 명시하고 예외 상황을 방지할 수 있어 코드 안정성이 향상됩니다.

2. 충돌 정보를 담을 구조체 정의
단순히 히트한 액터만 전달하는것이 아닌 충돌 위치, 데미지 등 여러 정보를 함께 전달할 수 있도록 구조체를 정의하고 이를 인자로 사용
히트 이벤트를 단순 액터 전달에서 벗어나, 데미지, 히트 위치 등 추가 정보를 포함한 구조체를 전달하여 향후 게임플레이 로직(예: 데미지 계산, 특수 효과 처리) 확장이 용이

3. Trace로 충돌처리
이유적기
*/