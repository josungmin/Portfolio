using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(fileName = "Inventory", menuName = "Inventory/Inventory")]
public class InventorySO : ScriptableObject
{
    [Tooltip("보유 아이템의 목록")]
    [SerializeField] private List<ItemStack> items = new List<ItemStack>();
    public List<ItemStack> Items { get => items; }

    [Tooltip("인벤토리 슬롯 개수")]
    [SerializeField] private int maxItemCount = 50;
    public int MaxItemCount { get => maxItemCount; }

    public bool Add(ItemSO item, int amount = 1)
    {
        if(amount <= 0)
        {
            return false;
        }

        if (Contains(item))
        {
            ItemStack itemStack = Find(item);
            itemStack.Add(amount);

            if (IsFull())
            {
                //itemStack.Delete(amount);
                return false;
            }
        }
        else
        {
            ItemStack itemStack = new ItemStack(item, amount);
            items.Add(itemStack);

            if (IsFull())
            {
                items.Remove(itemStack);
                return false;
            }
        }

        //items.Sort(Compare);

        return true;
    }

    public bool Delete(ItemSO item, int amount = 1)
    {
        if (amount <= 0 || !Contains(item))
        {
            return false;
        }

        ItemStack itemStack = Find(item);
        itemStack.Remove(amount);

        items.Sort(Compare);

        return true;
    }

    public void DeleteAll()
    {
        items.Clear();
    }

    private bool IsFull()
    {
        int curCount = 0;

        foreach (ItemStack data in items)
        {
            curCount += data.Amount / data.Item.MaxStack;

            if (0 < data.Amount % data.Item.MaxStack)
            {
                curCount += 1;
            }
        }

        return curCount < maxItemCount ? false : false;
    }

    private ItemStack Find(ItemSO item)
    {
        foreach (ItemStack data in items)
        {
            if (data.Item == item)
            {
                return data;
            }
        }

        return null;
    }
     
    private bool Contains(ItemSO item)
    {
        foreach (ItemStack data in items)
        {
            if (data.Item == item)
            {
                return true;
            }
        }

        return false;
    }

    private int Compare(ItemStack a, ItemStack b)
    {
        if (object.ReferenceEquals(a, b))
        {
            return 0;
        }

        return a.Item.Title.CompareTo(b.Item.Title);
    }
}
