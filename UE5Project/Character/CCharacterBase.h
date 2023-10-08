#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "CCharacterBase.generated.h"

UCLASS()
class DINGO_API ACCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ACCharacterBase();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Cameara")
		TObjectPtr<class USpringArmComponent> SpringArm;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Cameara")
		TObjectPtr<class UCameraComponent> Camera;

protected:
	UPROPERTY()
		TObjectPtr<class UEnhancedInputComponent> EnhancedInputComponent;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Input", Meta = (AllowPrivateAccess = "true"))
		TObjectPtr<class UInputMappingContext> DefaultMappingContext;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Input", Meta = (AllowPrivateAccess = "true"))
		TObjectPtr<class UInputAction> LookAction;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Input", Meta = (AllowPrivateAccess = "true"))
		TObjectPtr<class UInputAction> MoveAction;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Input", Meta = (AllowPrivateAccess = "true"))
		TObjectPtr<class UInputAction> JumpAction;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Input", Meta = (AllowPrivateAccess = "true"))
		TObjectPtr<class UInputAction> InteractAction;

protected:
	void OnMove(const FInputActionValue& Value);
	void OnLook(const FInputActionValue& Value);

	void OnInteract();
};
