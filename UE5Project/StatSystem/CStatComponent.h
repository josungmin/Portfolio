#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatSystem/Enums/EStat.h"
#include "StatSystem/Structs/FStat.h"
#include "CStatComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEUS_API UCStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCStatComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "temp")
	FDataTableRowHandle BaseStatsDataTable;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "temp")
	TMap<EStat, FStat> Stats;


public:
	UFUNCTION(BlueprintCallable)
	float GetStatValue(EStat StatType);

	// Stat Modifier
	void AddStatModifier(const FStatModifier& StatModifier);
	void RemoveStatModifier(const FStatModifier& StatModifier);


private:
	void InitializeStats();
	
	// Stat Modifier
	void ApplyModifiers(FStat& Stat) const;
	void ModifyStat(EStat StatType);
	void ModifyAllStats();
};
