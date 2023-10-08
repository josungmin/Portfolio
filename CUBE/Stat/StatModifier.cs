using UnityEngine;

public enum EStatModifierType
{
    Add,
    PercentAdd,
    PercentMulti,
}

[System.Serializable]
public class StatModifier
{
    [SerializeField] private EStatType targetStat;
    public EStatType TargetStat { get => targetStat; }

    [SerializeField] private float value = default;
    public float Value { get => value; }

    [SerializeField] private EStatModifierType modifierType;
    public EStatModifierType ModifierType { get => modifierType; }
   

    public float Modify(float baseValue)
    {
        if(modifierType == EStatModifierType.Add)
        {
            return baseValue + value;
        }
        else if (modifierType == EStatModifierType.PercentMulti)
        {
            return baseValue * (1 + value);
        }

        return baseValue;
    }
}
