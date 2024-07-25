#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ActionSystem/Enums/EStateType.h"
#include "CAction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnActionStateChanged);

UENUM(BlueprintType)
enum class EActionState : uint8
{
	Ready,
	Active,
	Cooldown
};

UCLASS(Blueprintable)
class DEUS_API UCAction : public UObject
{
	GENERATED_BODY()

public:
	UCAction();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Action")
	EActionState ActionState;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Action")
	FName ActionName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Action")
	uint32 bIsComboAction : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Action")
	uint32 bIsCancellable : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Action")
	float Cooldown;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "State")
	EStateType StateType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "State")
	TSet<EStateType> UnchangeableStates;

public:
	UFUNCTION(BlueprintCallable)
	virtual bool StartAction(AActor* Instigator);

	UFUNCTION(BlueprintCallable)
	virtual bool EndAction(AActor* Instigator);

	UFUNCTION(BlueprintCallable)
	virtual void CooldownComplete(AActor* Instigator);

	UPROPERTY(BlueprintAssignable)
	FOnActionStateChanged OnActionStarted;

	UPROPERTY(BlueprintAssignable)
	FOnActionStateChanged OnActionEnded;


public:
	FORCEINLINE EActionState GetActionState() const { return ActionState; }
	FORCEINLINE FName GetActionName() const { return ActionName; }
	FORCEINLINE bool GetIsComboAction() const { return bIsComboAction; }
	FORCEINLINE bool GetIsCancellable() const { return bIsCancellable; }
	FORCEINLINE float GetCooldown() const { return Cooldown; }
	FORCEINLINE EStateType GetStateType() const { return StateType; }

	/**
	* �׼��� ���� �ð��� ��ȯ - �ڽ� Ŭ�������� �ݵ�� ������ �ʿ�
	* @return ���� �ð�
	*/
	virtual float GetDuration();

	/**
	* ���� ���¿��� ���� �׼����� ������ �������� ���θ� Ȯ��
	* @param  ���� ����
	* @return ���� ���� ����
	*/
	virtual bool CanStartAction(EStateType CurrentStateType);


protected:
	void SetEndActionTimer(AActor* Instigator);
	void InitEndActionTimer(AActor* Instigator);

	void SetCooldownTimer(AActor* Instigator);
	void InitCooldownTimer(AActor* Instigator);


protected:
	FTimerHandle EndActionTimerHandle;
	FTimerHandle CooldownTimerHandle;
};
 