using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

[Serializable]
public class Stat
{
    [SerializeField] private string name;
    public string Name { get => name; }

    [SerializeField] private EStatType statType;
    public EStatType StatType { get => statType; }

    [SerializeField] private float baseValue = default;
    public float BaseValue { get => baseValue; }

    [SerializeField] private List<StatModifier> statModifiers;

    [SerializeField] private float finalValue = default;
    private bool isChanged = true;
    public float FinalValue { 
        get
        {
            // statModifiers 변동 사항이 있을 경우 다시 계산
            if (isChanged)
            {
                finalValue = CalculateFinalStat();
                isChanged = false;
            }
            return finalValue;
        }
    }

    public Stat()
    {
        this.name = string.Empty;
        this.statType = EStatType.None;
        this.baseValue = 0;

        statModifiers = new List<StatModifier>();
    }

    public Stat(string name, EStatType statType, float baseValue)
    {
        this.name = name;
        this.statType = statType;
        this.baseValue = baseValue;

        statModifiers = new List<StatModifier>();
    }

    public void AddModifier(StatModifier statModifier)
    {
        isChanged = true;
        statModifiers.Add(statModifier);
    }

    public bool RemoveModifier(StatModifier statModifier)
    {
        isChanged = true;
        return statModifiers.Remove(statModifier);
    }

    public void RemoveAllModifier()
    {
        statModifiers.Clear();
    }

    private float CalculateFinalStat()
    {
        float finalStat = baseValue;

        foreach(StatModifier data in statModifiers)
        {
            finalValue = data.Modify(finalValue);
        }

        // 결과 값의 소수점 2번째 자리에서 반올림한다.
        return (float)Math.Round(finalStat, 2);
    }
}
