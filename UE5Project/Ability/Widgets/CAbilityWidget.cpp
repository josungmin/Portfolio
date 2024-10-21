#include "Ability/Widgets/CAbilityWidget.h"
#include "Ability/Widgets/CAbilityGroupWidget.h"
#include "Components/PanelWidget.h"
#include "Utilities/CLog.h"

void UCAbilityWidget::NativeConstruct()
{
    InitializeWidget();
}


void UCAbilityWidget::InitializeWidget()
{
    if (!AbilityGroupWidgetContainer)
    {
        CLog::LogError("Parent panel is null.");
        return;
    }

    const TArray<UWidget*>& ChildWidgets = AbilityGroupWidgetContainer->GetAllChildren();
    for (UWidget* ChildWidget : ChildWidgets)
    {
        UCAbilityGroupWidget* GroupWidget = Cast<UCAbilityGroupWidget>(ChildWidget);
        if (GroupWidget)
        {         
            AddAbilityGroupWidget(GroupWidget->GetAbilityGroup(), GroupWidget);
        }
    }
}


void UCAbilityWidget::BindAbilityWidget(EAbilityGroup AbilityGroup, EAbility AbilityType, FText Name, float Value)
{
    UCAbilityGroupWidget** GroupWidgetPtr = AbilityGroupWidgets.Find(AbilityGroup);
    if (GroupWidgetPtr == nullptr || *GroupWidgetPtr == nullptr)
    {
        CLog::LogError("Group widget not found for updating ability.");
        return;
    }

    (*GroupWidgetPtr)->BindWidgetToAbility(AbilityType, Name, Value);
}


void UCAbilityWidget::AddAbilityGroupWidget(EAbilityGroup AbilityGroup, UCAbilityGroupWidget* GroupWidget)
{
    if (AbilityGroupWidgets.Contains(AbilityGroup))
    {
        CLog::LogError("Group widget with this name already exists.");
        return;
    }

    AbilityGroupWidgets.Add(AbilityGroup, GroupWidget);
}


void UCAbilityWidget::RemoveAbilityGroupWidget(EAbilityGroup AbilityGroup)
{
    if (!AbilityGroupWidgets.Contains(AbilityGroup))
    {
        CLog::LogError("Group widget not found.");
        return;
    }

    AbilityGroupWidgets.Remove(AbilityGroup);
}


void UCAbilityWidget::UpdateAbilityWidget(EAbilityGroup AbilityGroup, EAbility AbilityType, float NewValue)
{
    UCAbilityGroupWidget** GroupWidgetPtr = AbilityGroupWidgets.Find(AbilityGroup);
    if (GroupWidgetPtr == nullptr || *GroupWidgetPtr == nullptr)
    {
        CLog::LogError("Group widget not found for updating ability.");
        return;
    }

    (*GroupWidgetPtr)->UpdateWidgetForAbility(AbilityType, NewValue);
}
