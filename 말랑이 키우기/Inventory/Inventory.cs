using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Inventory : MonoBehaviour
{
    [SerializeField] private InventorySO inventory = default;

    // Listening
    [SerializeField] private ItemEventChannelSO addItemEvent = default;
    [SerializeField] private ItemEventChannelSO deleteItemEvent = default;
    [SerializeField] private ItemStackEventChannelSO addItemStackEvent = default;
    [SerializeField] private ItemStackEventChannelSO deleteItemStackEvent = default;
    [SerializeField] private IntEventChannelSO expansionInventoryEvent = default;

    // Broadcasting
    [SerializeField] private IntEventChannelSO createItemSlotsEvent;
    [SerializeField] private VoidEventChannelSO updateInventoryEvent;

    private void Start()
    {
        inventory = GameManager.Instance.GameData.Inventory;
    }

    private void OnEnable()
    {
        addItemEvent.OnEventRaised += AddItem;
        deleteItemEvent.OnEventRaised += DeleteItem;
        addItemStackEvent.OnEventRaised += AddItemStack;
        deleteItemStackEvent.OnEventRaised += DeleteItemStack;
        expansionInventoryEvent.OnEventRaised += ExpansionInventory;
    }

    private void OnDisable()
    {
        addItemEvent.OnEventRaised -= AddItem;
        deleteItemEvent.OnEventRaised -= DeleteItem;
        addItemStackEvent.OnEventRaised -= AddItemStack;
        deleteItemStackEvent.OnEventRaised -= DeleteItemStack;
        expansionInventoryEvent.OnEventRaised -= ExpansionInventory;
    }

    private void AddItem(ItemSO item)
    {
        bool result = inventory.Add(item);
        updateInventoryEvent.RaiseEvent(); // UI Update

        if (!result)
        {
            Debug.LogError("아이템 추가 실패");
            return;
        }
    }

    private void AddItemStack(ItemStack itemStack)
    {
        bool result = inventory.Add(itemStack.Item, itemStack.Amount);
        updateInventoryEvent.RaiseEvent(); // UI Update

        if (!result)
        {
            Debug.LogError("아이템 추가 실패");
            return;
        }
    }

    private void DeleteItem(ItemSO item)
    {
        bool result = inventory.Delete(item);
        updateInventoryEvent.RaiseEvent(); // UI Update

        if (!result)
        {
            Debug.LogError("아이템 삭재 실패");
            return;
        }
    }

    private void DeleteItemStack(ItemStack itemStack)
    {
        bool result = inventory.Delete(itemStack.Item, itemStack.Amount);
        updateInventoryEvent.RaiseEvent(); // UI Update

        if (!result)
        {
            Debug.LogError("아이템 삭재 실패");
            return;
        }
    }

    private void ExpansionInventory(int amount)
    {
        bool result = inventory.Expansion(amount);
        createItemSlotsEvent.RaiseEvent(amount); // UI Update

        if (!result)
        {
            Debug.LogError("인벤토리 확장 실패");
            return;
        }
    }

    private void OnApplicationQuit()
    {
        GameManager.Instance.GameData.SetInventory(inventory);
    }
}
