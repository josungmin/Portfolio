#include "StatSystem/CStatComponent.h"
#include "StatSystem/Enums/EStatFormulaType.h"
#include "StatSystem/Structs/FStatModifier.h"
#include "StatSystem/DateTables/FBaseStats.h"


UCStatComponent::UCStatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UCStatComponent::BeginPlay()
{
	Super::BeginPlay();

	InitializeStats();
}


void UCStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}


float UCStatComponent::GetStatValue(EStat StatType)
{
	FStat* Stat = Stats.Find(StatType);
	if (!Stat)
	{
		return 0.0f;;
	}

	if (Stat->bIsChanged)
	{
		ModifyStat(StatType);
	}	

	return Stat->FinalValue;
}


void UCStatComponent::AddStatModifier(const FStatModifier& StatModifier)
{
	FStat* Stat = Stats.Find(StatModifier.TargetStat);
	if (!Stat)
	{
		return;
	}

	if (Stat->StatModifiers.Contains(StatModifier))
	{
		return;
	}

	Stat->StatModifiers.Add(StatModifier);
	Stat->bIsChanged = true;
	ModifyStat(StatModifier.TargetStat);
}


void UCStatComponent::RemoveStatModifier(const FStatModifier& StatModifier)
{
	FStat* Stat = Stats.Find(StatModifier.TargetStat);
	if (!Stat)
	{
		return;
	}

	if (!Stat->StatModifiers.Contains(StatModifier))
	{
		return;
	}

	Stat->StatModifiers.Remove(StatModifier);
	Stat->bIsChanged = true;
	ModifyStat(StatModifier.TargetStat);
}


void UCStatComponent::InitializeStats()
{
	if (!BaseStatsDataTable.DataTable)
	{
		return;
	}

	TArray<FBaseStats*> Rows;
	static const FString ContextString(TEXT("BaseStats Context"));
	BaseStatsDataTable.DataTable->GetAllRows<FBaseStats>(ContextString, Rows);

	for (const FBaseStats* Row : Rows)
	{
		if (Row)
		{
			Stats.Add(Row->Stat.StatType, Row->Stat);
		}
	}
}


void UCStatComponent::ApplyModifiers(FStat& Stat) const
{
	Stat.FinalValue = Stat.BaseValue;
	for (const FStatModifier& StatModifier : Stat.StatModifiers)
	{
		switch (StatModifier.FormulaType)
		{
		case EStatFormulaType::Add:
			Stat.FinalValue += StatModifier.Value;
			break;
		case EStatFormulaType::PercentAdd:
			Stat.FinalValue += Stat.FinalValue * (StatModifier.Value * 0.01f);
			break;
		case EStatFormulaType::PercentMulti:
			Stat.FinalValue *= StatModifier.Value * 0.01f;
			break;
		default:
			break;
		}
	}
}


void UCStatComponent::ModifyStat(EStat StatType)
{
	FStat* Stat = Stats.Find(StatType);
	if (!Stat)
	{
		return;
	}

	if (!Stat->bIsChanged)
	{
		return;
	}

	ApplyModifiers(*Stat);
	Stat->bIsChanged = false;

	// Notify stat change Event
}


void UCStatComponent::ModifyAllStats()
{
	for (auto& Pair : Stats)
	{
		FStat& Stat = Pair.Value;
		if (Stat.bIsChanged)
		{
			ApplyModifiers(Stat);
			Stat.bIsChanged = false;

			// Notify stat change Event
		}
	}
}