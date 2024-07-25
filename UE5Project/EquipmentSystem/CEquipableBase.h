#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CEquipableBase.generated.h"

UCLASS()
class DINGO_API ACEquipableBase : public AActor
{
	GENERATED_BODY()

public:
	ACEquipableBase();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Component")
		TObjectPtr<USceneComponent> SceneComponent;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Component")
		TObjectPtr<USkeletalMeshComponent> SkeletalMesh;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Component")
		TObjectPtr<UStaticMeshComponent> StaticMesh;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Initialization", Meta = (AllowPrivateAccess = "true"))
		FName AttachSocketName;

public:
	virtual UPrimitiveComponent* GetMesh();
	FORCEINLINE FName GetAttachSocketName() const { return AttachSocketName; }

	virtual void OnEquiped();
	virtual void OnUnequiped();
	FORCEINLINE bool GetIsEquiped() const { return bIsEquiped; }
	FORCEINLINE void SetIsEquiped(bool InEquiped) { bIsEquiped = InEquiped; }

	UFUNCTION(BlueprintCallable)
		virtual void AttachActor(FName InSocketName);

private:
	bool bIsEquiped = false;
};
