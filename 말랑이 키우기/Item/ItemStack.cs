using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[System.Serializable]
public class ItemStack 
{
	[SerializeField] private ItemSO item = default;
	public ItemSO Item { get => item; }

	[SerializeField] private int amount = default;
	public int Amount { get => amount; }

	public ItemStack()
	{
		item = null;
		amount = 0;
	}

	public ItemStack(ItemStack itemStack)
	{
		item = itemStack.Item;
		amount = itemStack.amount;
	}

	public ItemStack(ItemSO item, int amount = 1)
	{
		this.item = item;
		this.amount = amount;
	}

	public bool Add(int amount)
    {
		this.amount += amount;

		return true;
    }

	public bool Delete(int amount)
    {
		if(this.amount <= 0)
        {
			return false;
        }

		this.amount -= amount;

		return true;
    }
}
