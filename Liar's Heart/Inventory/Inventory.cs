using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Inventory : MonoBehaviour
{
    [SerializeField] private InventorySO curInventory = default;

    // Listening
    [SerializeField] private ItemEventChannelSO addItemEvent = default;
    [SerializeField] private ItemEventChannelSO removeItemEvent = default;
    [SerializeField] private ItemStackEventChannelSO addItemStackEvent = default;
    [SerializeField] private ItemStackEventChannelSO removeItemStackEvent = default;

    // Broadcasting
    [SerializeField] private VoidEventChannelSO updateInventoryEvent;

    private void Awake()
    {
        addItemEvent = Resources.Load<ItemEventChannelSO>("Events/Inventory/AddItemEvent");
        removeItemEvent = Resources.Load<ItemEventChannelSO>("Events/Inventory/RemoveItemEvent");
        addItemStackEvent = Resources.Load<ItemStackEventChannelSO>("Events/Inventory/AddItemStackEvent");
        removeItemStackEvent = Resources.Load<ItemStackEventChannelSO>("Events/Inventory/RemoveItemStackEvent");
        updateInventoryEvent = Resources.Load<VoidEventChannelSO>("Events/Inventory/UpdateInventoyEvent");
    }

    public void SetInventory(InventorySO inventory)
    {
        curInventory = inventory;
    }

    private void OnEnable()
    {
        addItemEvent.OnEventRaised += AddItem;
        removeItemEvent.OnEventRaised += RemoveItem;
        addItemStackEvent.OnEventRaised += AddItemStack;
        removeItemStackEvent.OnEventRaised += RemoveItemStack;
    }

    private void OnDisable()
    {
        addItemEvent.OnEventRaised -= AddItem;
        removeItemEvent.OnEventRaised -= RemoveItem;
        addItemStackEvent.OnEventRaised -= AddItemStack;
        removeItemStackEvent.OnEventRaised -= RemoveItemStack;
    }

    private void AddItem(ItemSO item)
    {
        bool result = curInventory.Add(item);
        updateInventoryEvent.RaiseEvent(); // UI Update

        if (!result)
        {
            Debug.LogError("아이템 추가 실패");
            return;
        }
    }

    private void RemoveItem(ItemSO item)
    {
        bool result = curInventory.Delete(item);
        updateInventoryEvent.RaiseEvent(); // UI Update

        if (!result)
        {
            Debug.LogError("아이템 삭재 실패");
            return;
        }
    }

    private void AddItemStack(ItemStack itemStack)
    {
        bool result = curInventory.Add(itemStack.Item, itemStack.Amount);
        updateInventoryEvent.RaiseEvent(); // UI Update

        if (!result)
        {
            Debug.LogError("아이템 추가 실패");
            return;
        }
    }

    private void RemoveItemStack(ItemStack itemStack)
    {
        bool result = curInventory.Delete(itemStack.Item, itemStack.Amount);
        updateInventoryEvent.RaiseEvent(); // UI Update

        if (!result)
        {
            Debug.LogError("아이템 삭재 실패");
            return;
        }
    }
}
