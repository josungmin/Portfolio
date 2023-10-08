using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(fileName = "StatCollection", menuName = "Stat/StatCollection")]
[System.Serializable]
public class StatCollection : ScriptableObject
{
    [SerializeField] private List<Stat> stats = new List<Stat>();

    public Stat CreateStat(string name, EStatType statType, float baseValue)
    {
        Stat stat = GetStat(statType);
        if (stat != null)
        {
            return stat;
        }

        stat = new Stat(name, statType, baseValue);
        stats.Add(stat);

        return stat;
    }

    public bool RemoveStat(EStatType statType)
    {
        if (!Contain(statType))
        {
            return false;
        }

        stats.Remove(GetStat(statType));

        return true;
    }

    public bool Contain(EStatType statType)
    {
        return GetStat(statType) != null;
    }

    public Stat GetStat(EStatType statType)
    {
        foreach(Stat data in stats)
        {
            if (data.StatType == statType)
            {
                return data;
            }        
        }

        return null;
    }
}
