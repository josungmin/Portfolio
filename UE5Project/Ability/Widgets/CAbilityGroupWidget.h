#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Ability/Enums/EAbility.h"
#include "Ability/Enums/EAbilityGroup.h"
#include "CAbilityGroupWidget.generated.h"

class UVerticalBox;
class UCAbilityWidgetBase;

UCLASS()
class DEUS_API UCAbilityGroupWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability Group")
	EAbilityGroup AbilityGroup;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability Group")
	TMap<EAbility, UCAbilityWidgetBase*> AbilityWidgets;

	UPROPERTY(meta = (BindWidget), VisibleAnywhere, BlueprintReadOnly)
	UVerticalBox* AbilityWidgetContainer;

public:
	FORCEINLINE EAbilityGroup GetAbilityGroup() const
	{
		return AbilityGroup;
	}

	void InitializeWidget();
	void RemoveAbilityWidget(EAbility AbilityType);

	void BindWidgetToAbility(EAbility AbilityType, FText Name, float Value);
	void UpdateWidgetForAbility(EAbility AbilityType, float Value);
};
