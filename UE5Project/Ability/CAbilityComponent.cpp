#include "Ability/CAbilityComponent.h"
#include "Ability/Base/CAbility.h"
#include "Ability/CStat.h"
#include "Ability/CAttribute.h"
#include "Ability/Widgets/CAbilityWidget.h"
#include "Ability/DataTables/FAttributeData.h"
#include "Ability/DataTables/FStatData.h"
#include "Blueprint/UserWidget.h"
#include "Core/CPlayerController.h"
#include "Utilities/CLog.h"


UCAbilityComponent::UCAbilityComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UCAbilityComponent::BeginPlay()
{
	Super::BeginPlay();

	InitialzeStat();
	InitialzeAttribute();

	// Bind UI
	for (TPair<EAbility, UCModifierContainer*> Pair : Stats->GetAbilities())
	{
		AbilityWidget->BindAbilityWidget(
			Pair.Value->GetAbilityGroup(),
			Pair.Value->GetTargetAbility(),
			Pair.Value->GetName(),
			Pair.Value->GetFinalValue()
			);
	}

	// Bind UI
	for (TPair<EAbility, UCModifierContainer*> Pair : Attributes->GetAbilities())
	{
		AbilityWidget->BindAbilityWidget(
			Pair.Value->GetAbilityGroup(),
			Pair.Value->GetTargetAbility(),
			Pair.Value->GetName(),
			Pair.Value->GetFinalValue()
		);
	}
}


void UCAbilityComponent::InitialzeStat()
{
	if (!StatDataTable)
	{
		CLog::LogError(TEXT("StatDataTable is not set."));
		return;
	}

	Stats = NewObject<UCAbility>();

	static const FString ContextString(TEXT("Stat Load Context"));
	TArray<FName> RowNames = StatDataTable->GetRowNames();
	for (const FName& RowName : RowNames)
	{
		FStatData* StatRow = StatDataTable->FindRow<FStatData>(RowName, ContextString);
		if (StatRow)
		{
			UCStat* NewStat = NewObject<UCStat>();
			NewStat->InitializeStat(
				StatRow->AbilityGroup, 
				StatRow->Name, 
				StatRow->TargetAbility, 
				StatRow->BaseValue
			);

			Stats->AddAbility(StatRow->TargetAbility, NewStat);
		}
	}
}


UCStat* UCAbilityComponent::FindStat(EAbility StatType)
{
	return Cast<UCStat>(Stats->GetAbility(StatType));
}


TOptional<float> UCAbilityComponent::GetStatValue(EAbility StatType)
{
	UCStat* Stat = FindStat(StatType);
	if (Stat == nullptr)
	{
		return TOptional<float>();
	}

	return Stat->GetFinalValue();
}


void UCAbilityComponent::AddStatModifier(const FModifierBase& StatModifier)
{
	Stats->AddModifierToAbility(StatModifier.TargetAbility, StatModifier);

	// Update UI
	UCStat* Stat = FindStat(StatModifier.TargetAbility);
	if (Stat == nullptr)
	{
		CLog::LogError("Stat does not exist");
		return;
	}

	AbilityWidget->UpdateAbilityWidget(Stat->GetAbilityGroup(), Stat->GetTargetAbility(), Stat->GetFinalValue());
}


void UCAbilityComponent::RemoveStatModifier(const FModifierBase& StatModifier)
{
	Stats->RemoveModifierToAbility(StatModifier.TargetAbility, StatModifier);

	// Update UI
	UCStat* Stat = FindStat(StatModifier.TargetAbility);
	if (Stat == nullptr)
	{
		CLog::LogError("Stat does not exist");
		return;
	}

	AbilityWidget->UpdateAbilityWidget(Stat->GetAbilityGroup(), Stat->GetTargetAbility(), Stat->GetFinalValue());
}


void UCAbilityComponent::InitialzeAttribute()
{
	if (!AttributeDataTable)
	{
		CLog::LogError(TEXT("AttributeDataTable is not set."));
		return;
	}

	Attributes = NewObject<UCAbility>();

	static const FString ContextString(TEXT("Attribute Load Context"));
	TArray<FName> RowNames = AttributeDataTable->GetRowNames();
	for (const FName& RowName : RowNames)
	{
		FAttributeData* AttributeRow = AttributeDataTable->FindRow<FAttributeData>(RowName, ContextString);
		if (AttributeRow)
		{
			UCAttribute* NewAttribute = NewObject<UCAttribute>();
			NewAttribute->InitializeAttribute(
				AttributeRow->AbilityGroup,
				AttributeRow->Name,
				AttributeRow->TargetAbility,
				AttributeRow->BaseValue,
				AttributeRow->AttributeToStatInfluence
			);

			Attributes->AddAbility(AttributeRow->TargetAbility, NewAttribute);
		}
	}
}


UCAttribute* UCAbilityComponent::FindAttribute(EAbility AttributeType)
{
	return Cast<UCAttribute>(Attributes->GetAbility(AttributeType));

	UCAttribute* Attribute = Cast<UCAttribute>(Attributes->GetAbility(AttributeType));
	if (!Attribute)
	{
		CLog::LogError("Ability does not exists");
		return nullptr;
	}

	return Attribute;
}


TOptional<float> UCAbilityComponent::GetAttributeValue(EAbility AttributeType)
{
	UCAttribute* Attribute = FindAttribute(AttributeType);
	if (Attribute == nullptr)
	{
		return TOptional<float>();
	}

	return Attribute->GetFinalValue();
}


void UCAbilityComponent::AddAttributeModifier(const FModifierBase& AttributeModifier)
{
	Attributes->AddModifierToAbility(AttributeModifier.TargetAbility, AttributeModifier);
	UpdateStatWithAttributes(AttributeModifier.TargetAbility);

	// Update UI
	UCAttribute* Attribute = FindAttribute(AttributeModifier.TargetAbility);
	if (Attribute == nullptr)
	{
		CLog::LogError("Attribute does not exist");
		return;
	}

	AbilityWidget->UpdateAbilityWidget(Attribute->GetAbilityGroup(), Attribute->GetTargetAbility(), Attribute->GetFinalValue());
}


void UCAbilityComponent::RemoveAttributeModifier(const FModifierBase& AttributeModifier)
{
	Attributes->RemoveModifierToAbility(AttributeModifier.TargetAbility, AttributeModifier);
	UpdateStatWithAttributes(AttributeModifier.TargetAbility);

	// Update UI
	UCAttribute* Attribute = FindAttribute(AttributeModifier.TargetAbility);
	if (Attribute == nullptr)
	{
		CLog::LogError("Attribute does not exist");
		return;
	}

	AbilityWidget->UpdateAbilityWidget(Attribute->GetAbilityGroup(), Attribute->GetTargetAbility(), Attribute->GetFinalValue());
}


void UCAbilityComponent::UpdateStatWithAttributes(EAbility AttributeType)
{
	UCAttribute* Attribute = FindAttribute(AttributeType);
	if (!Attribute)
	{
		CLog::LogError("Attribute does not exist");
		return;
	}

	const TMap<EAbility, float> AttributeInfluences = Attribute->GetAttributeToStatInfluence();

	for (const TPair<EAbility, float>& InfluencePair : AttributeInfluences)
	{
		UCStat* Stat = FindStat(InfluencePair.Key);
		if (Stat)
		{
			float CalculatedInfluence = Attribute->CalculateStatInfluence(InfluencePair.Key);
			Stat->UpdateAttributeBonusValue(CalculatedInfluence);
		}
	}
}
