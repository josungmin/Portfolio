#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Ability/Enums/EAbility.h"
#include "Ability/Enums/EAbilityGroup.h"
#include "CAbilityWidget.generated.h"

class UCAbilityGroupWidget;
class UPanelWidget;

UCLASS()
class DEUS_API UCAbilityWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
    virtual void NativeConstruct() override;

protected:
    UPROPERTY(meta = (BindWidget), VisibleAnywhere, BlueprintReadOnly)
    UPanelWidget* AbilityGroupWidgetContainer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability")
	TMap<EAbilityGroup, UCAbilityGroupWidget*> AbilityGroupWidgets;

public:
    void InitializeWidget();
    void BindAbilityWidget(EAbilityGroup AbilityGroup, EAbility AbilityType, FText Name, float Value);
    void UpdateAbilityWidget(EAbilityGroup AbilityGroup, EAbility AbilityType, float NewValue);

    void AddAbilityGroupWidget(EAbilityGroup AbilityGroup, UCAbilityGroupWidget* GroupWidget);
    void RemoveAbilityGroupWidget(EAbilityGroup AbilityGroup);
    
};
