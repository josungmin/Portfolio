#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Ability/Enums/EAbility.h"
#include "CAbilityWidgetBase.generated.h"

class UTextBlock;

UCLASS()
class DEUS_API UCAbilityWidgetBase : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativePreConstruct() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
	EAbility BoundAbility;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
	FText Name = FText::FromString(TEXT("New Ability"));

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
	float Value = 0;

	UPROPERTY(meta = (BindWidget), VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UTextBlock> NameText;

	UPROPERTY(meta = (BindWidget), VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UTextBlock> ValueText;


public:
	FORCEINLINE EAbility GetBindAbility() const
	{
		return BoundAbility;
	}

public:
	virtual void BindAbility(FText AbilityName, float InitialValue);
	virtual void UpdateAbilityValue(float NewValue);
};
