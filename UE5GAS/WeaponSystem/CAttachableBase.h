#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CAttachableBase.generated.h"


UCLASS()
class ROXY_API ACAttachableBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ACAttachableBase();

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Item|Attachable")
	TObjectPtr<USceneComponent> SceneComponent;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Item|Attachable")
	TObjectPtr<USkeletalMeshComponent> SkeletalMesh;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Item|Attachable")
	TObjectPtr<UStaticMeshComponent> StaticMesh;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item|Attachable", Meta = (AllowPrivateAccess = "true"))
	FName AttachSocketName;

public:
	UFUNCTION(BlueprintCallable)
	virtual UPrimitiveComponent* GetMesh();

	UFUNCTION(BlueprintCallable)
	virtual void OnAttach(FName InSocketName = NAME_None);

	UFUNCTION(BlueprintCallable)
	virtual void OnDetach();

public:
	FORCEINLINE FName GetAttachSocketName() const { return AttachSocketName; }
};
