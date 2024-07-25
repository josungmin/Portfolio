#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CCombatComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEUS_API UCCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCCombatComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Initialization", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class ACWeaponBase> MainWeapon;

public:
	void ApplyDamage(AActor* Target, int32 Damage);
	void ApplyDamage(const FHitResult& HitResult);


public:
	UFUNCTION(BlueprintCallable)
	void SetMainWeapon(ACWeaponBase* InWeapon);
	FORCEINLINE ACWeaponBase* GetMainWeapon() const { return MainWeapon; }
};
