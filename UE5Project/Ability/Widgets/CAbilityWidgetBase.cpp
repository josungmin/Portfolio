#include "Ability/Widgets/CAbilityWidgetBase.h"
#include "Components/TextBlock.h"
#include "Utilities/CLog.h"


void UCAbilityWidgetBase::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (!NameText)
	{
		CLog::LogError("The NameText is not bind");
		return;
	}

	NameText->SetText(Name);

	if (!ValueText)
	{
		CLog::LogError("The ValueText is not bind");
		return;
	}

	ValueText->SetText(FText::AsNumber(Value));
}


void UCAbilityWidgetBase::BindAbility(FText AbilityName, float InitialValue)
{
	if (!NameText)
	{
		CLog::LogError("The NameText is not bind");
		return;
	}

	NameText->SetText(Name);

	UpdateAbilityValue(InitialValue);
}


void UCAbilityWidgetBase::UpdateAbilityValue(float NewValue)
{
	if (!ValueText)
	{
		CLog::LogError("The ValueText is not bind");
		return;
	}

	ValueText->SetText(FText::AsNumber(NewValue));
}

