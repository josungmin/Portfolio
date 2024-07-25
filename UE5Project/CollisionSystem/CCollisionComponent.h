#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CCollisionComponent.generated.h"

DECLARE_DELEGATE_OneParam(FOnHitSignature, FHitResult);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DINGO_API UCCollisionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCCollisionComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Component")
		TObjectPtr<UPrimitiveComponent> CollisionMeshComponent;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Initialization", Meta = (AllowPrivateAccess = "true"))
		int32 TraceRadius = 20.0f;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Initialization", Meta = (AllowPrivateAccess = "true"))
		FName StartSocketName = FName("Weapon Start");

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Initialization", Meta = (AllowPrivateAccess = "true"))
		FName EndSocketName = FName("Weapon End");

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Initialization", Meta = (AllowPrivateAccess = "true"))
		TArray<TEnumAsByte<EObjectTypeQuery>> CollisionObjectType;

	UPROPERTY()
		TArray<TObjectPtr<AActor>> IgnoreActors;

	UPROPERTY()
		TArray<TObjectPtr<AActor>> AlreadyHitActors;

	bool bIsCollisionEnabled = false;

public:
	FORCEINLINE TObjectPtr<UPrimitiveComponent> GetCollisionMeshComponent() const { return CollisionMeshComponent; }
	FORCEINLINE bool GetIsCollisionEnabled() const { return bIsCollisionEnabled; }
	FORCEINLINE TArray<TObjectPtr<AActor>> GetAlreadyHitActors() const { return AlreadyHitActors; }

	void AddIgnoreActor(AActor* InActor);
	FORCEINLINE void ClearIgnotActors() { IgnoreActors.Empty(); };

public:
	FOnHitSignature OnHit;

	virtual void SetCollisionMesh(UPrimitiveComponent* MeshComp);
	virtual void EnableCollision();
	virtual void DisableCollision();
	virtual void CollisionTrace();

private:
	void ClreatHitActors();
};
