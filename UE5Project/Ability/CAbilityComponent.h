#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Enums/EAbility.h"
#include "CAbilityComponent.generated.h"


class UCModifierContainer;
struct FModifierBase;
class UCAbility;
class UCStat;
class UCAttribute;
class UCAbilityWidget;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEUS_API UCAbilityComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCAbilityComponent();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AbilityComponent | DataTable")
	UDataTable* AttributeDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AbilityComponent | DataTable")
	UDataTable* StatDataTable;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilityComponent | Stat")
	TObjectPtr<UCAbility> Stats;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilityComponent | Attribute")
	TObjectPtr<UCAbility> Attributes;

	UPROPERTY(Transient)
	TObjectPtr<UCAbilityWidget> AbilityWidget;

public:
	void InitialzeStat();
	UCStat* FindStat(EAbility StatType);

	UFUNCTION(BlueprintCallable, Category = "Stat")
	TOptional<float> GetStatValue(EAbility StatType);

	UFUNCTION(BlueprintCallable, Category = "Stat")
	void AddStatModifier(const FModifierBase& StatModifier);

	UFUNCTION(BlueprintCallable, Category = "Stat")
	void RemoveStatModifier(const FModifierBase& StatModifier);


public:
	void InitialzeAttribute();
	UCAttribute* FindAttribute(EAbility AttributeType);

	UFUNCTION(BlueprintCallable, Category = "Attribute")
	TOptional<float> GetAttributeValue(EAbility AttributeType);

	UFUNCTION(BlueprintCallable, Category = "Attribute")
	void AddAttributeModifier(const FModifierBase& AttributeModifier);

	UFUNCTION(BlueprintCallable, Category = "Attribute")
	void RemoveAttributeModifier(const FModifierBase& AttributeModifier);

	UFUNCTION(BlueprintCallable, Category = "Attribute")
	void UpdateStatWithAttributes(EAbility AttributeType);
};


//if (!AttributeDataTable)
//{
//	CLog::LogError(TEXT("AttributeDataTable is not set."));
//	return;
//}
//
//static const FString ContextString(TEXT("Attribute Load Context"));
//TArray<FName> RowNames = AttributeDataTable->GetRowNames();
//for (const FName& RowName : RowNames)
//{
//	FAttribute* AttributeRow = AttributeDataTable->FindRow<FAttribute>(RowName, ContextString);
//	if (AttributeRow)
//	{
//		Attributes.Add(AttributeRow->AttributeType, *AttributeRow);
//	}
//}