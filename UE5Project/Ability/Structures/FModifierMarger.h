#pragma once
#include "CoreMinimal.h"
#include "Ability/Enums/EMargeFormulaType.h"
#include "Ability/Interfaces/IModifierMarge.h"
#include "Utilities/CLog.h"


class FMargeFormula : public IModifierMarge
{
public:
	virtual float Marge(float BaseValue, float ModifierValue) const override
	{
		return BaseValue + ModifierValue;
	}
};


class FMultiplyFormula : public IModifierMarge
{
public:
	virtual float Marge(float BaseValue, float ModifierValue) const override
	{
		return BaseValue * ModifierValue;
	}
};


class FOverwriteFormula : public IModifierMarge
{
public:
	virtual float Marge(float BaseValue, float ModifierValue) const override
	{
		return ModifierValue;
	}
};


class FHighestFormula : public IModifierMarge
{
public:
	virtual float Marge(float BaseValue, float ModifierValue) const override
	{
		return FMath::Max(BaseValue, ModifierValue);
	}
};


class FLowestFormula : public IModifierMarge
{
public:
	virtual float Marge(float BaseValue, float ModifierValue) const override
	{
		return FMath::Min(BaseValue, ModifierValue);
	}
};


/////////////////////////////////////////////////////////////////////////////////////////////


class FModifierMarger
{
public:
	FModifierMarger()
	{
		Formulas.Add(EMargeFormulaType::Marge, MakeShared<FMargeFormula>());
		Formulas.Add(EMargeFormulaType::Multiply, MakeShared<FMultiplyFormula>());
		Formulas.Add(EMargeFormulaType::Overwrite, MakeShared<FOverwriteFormula>());
		Formulas.Add(EMargeFormulaType::Highest, MakeShared<FHighestFormula>());
		Formulas.Add(EMargeFormulaType::Lowest, MakeShared<FLowestFormula>());
	}

	float Marge(EMargeFormulaType FormulaType, float BaseValue, float ModifierValue) const
	{
		const TSharedPtr<IModifierMarge>* Formula = Formulas.Find(FormulaType);
		if (Formula != nullptr && Formula->IsValid())
		{
			return Formula->Get()->Marge(BaseValue, ModifierValue);
		} 

		CLog::LogError("The Formula does not exist");
		return BaseValue;
	}
	
private:
	TMap<EMargeFormulaType, TSharedPtr<IModifierMarge>> Formulas;
};
