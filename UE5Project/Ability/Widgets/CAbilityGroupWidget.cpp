#include "Ability/Widgets/CAbilityGroupWidget.h"
#include "Components/VerticalBox.h"
#include "Ability/Widgets/CAbilityWidgetBase.h"
#include "Utilities/CLog.h"


void UCAbilityGroupWidget::NativeConstruct()
{
	InitializeWidget();
}


void UCAbilityGroupWidget::InitializeWidget()
{
	if (!AbilityWidgetContainer)
	{
		CLog::LogError("AbilityWidgetContainer is not bound.");
		return;
	}

	for (UWidget* ChildWidget : AbilityWidgetContainer->GetAllChildren())
	{
		UCAbilityWidgetBase* AbilityWidget = Cast<UCAbilityWidgetBase>(ChildWidget);
		if (AbilityWidget)
		{
			AbilityWidgets.Add(AbilityWidget->GetBindAbility(), AbilityWidget);
		}
	}
}


void UCAbilityGroupWidget::RemoveAbilityWidget(EAbility AbilityType)
{
	if (!AbilityWidgets.Contains(AbilityType))
	{
		CLog::LogError("AbilityType is not bound.");
		return;
	}

	AbilityWidgetContainer->RemoveChild(AbilityWidgets[AbilityType]);
	AbilityWidgets.Remove(AbilityType);
}


void UCAbilityGroupWidget::BindWidgetToAbility(EAbility AbilityType, FText Name, float Value)
{
	UCAbilityWidgetBase** WidgetPtr = AbilityWidgets.Find(AbilityType);
	if (*WidgetPtr == nullptr)
	{
		CLog::LogError("Ability widget already bound for ability type.");
		return;
	}

	(*WidgetPtr)->BindAbility(Name, Value);
}


void UCAbilityGroupWidget::UpdateWidgetForAbility(EAbility AbilityType, float Value)
{
	if (UCAbilityWidgetBase** WidgetPtr = AbilityWidgets.Find(AbilityType))
	{
		(*WidgetPtr)->UpdateAbilityValue(Value);
	}
}

