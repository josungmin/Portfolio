#pragma once
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "DataAsset_InputConfig.generated.h"

class UInputAction;
class UInputMappingContext;
class UCInputPolicy;

UENUM(BlueprintType)
enum class EInputTriggerPolicy : uint8
{
	None							UMETA(DisplayName = "None"),
	ActivateAbilityOnly				UMETA(DisplayName = "Activate Ability Only"),
	TriggerGameplayEventOnly		UMETA(DisplayName = "Trigger Gameplay Event Only"),
	ActivateAbilityAndTriggerEvent	UMETA(DisplayName = "Activate Ability And Trigger Event")
};


USTRUCT(BlueprintType)
struct FInputActionConfig
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag"))
	FGameplayTag InputTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputAction;

	UPROPERTY(EditDefaultsOnly, Instanced, BlueprintReadOnly)
	UCInputPolicy* InputPolicy;


	bool IsValid() const
	{
		return InputTag.IsValid() && InputAction && InputPolicy;
	}
};


UCLASS()
class ROXY_API UDataAsset_InputConfig : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputTag"))
	TArray<FInputActionConfig> NativeInputActions;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputTag"))
	TArray<FInputActionConfig> AbilityInputActions;

public:
	UInputAction* FindNativeInputActionByTag(const FGameplayTag& InInputTag) const;
};
