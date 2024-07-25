#pragma once

#include "CoreMinimal.h"
#include "StatSystem/Structs/FStat.h"
#include "FBaseStats.generated.h"

USTRUCT(BlueprintType)
struct DEUS_API FBaseStats : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FBaseStats")
	FStat Stat;
};
