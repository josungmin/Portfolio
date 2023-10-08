using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class UIInventory : MonoBehaviour
{
    [SerializeField] private InventorySO inventory = default;
    [SerializeField] private EInventoryTabType inventoryTabType = default;

    [SerializeField] private Transform parent = default;
    [SerializeField] private GameObject itemSlotPrefab = default;
    [SerializeField] private List<UIItemSlot> itemSlots = new List<UIItemSlot>();

    // Listening
    [SerializeField] private IntEventChannelSO createItemSlotsEvent;
    [SerializeField] private VoidEventChannelSO updateInventoryEvent;

    private void OnEnable()
    {
        createItemSlotsEvent.OnEventRaised += CreateItemSlots;
        updateInventoryEvent.OnEventRaised += UpdateInventory;
    }

    private void OnDisable()
    {
        createItemSlotsEvent.OnEventRaised -= CreateItemSlots;
        updateInventoryEvent.OnEventRaised -= UpdateInventory;
    }

    private void Start()
    {
        CreateItemSlots(inventory.MaxItemCount);
        UpdateInventory();
    }

    private void InitItemSlots()
    {
        foreach(UIItemSlot data in itemSlots)
        {
            data.Init();
        }
    }

    private void CreateItemSlots(int amount = 0)
    {
        if(amount == 0)
        {
            return;
        }

        for (int i = 0; i < amount; i++)
        {
            UIItemSlot itemSlot = Instantiate(itemSlotPrefab).GetComponent<UIItemSlot>();
            itemSlots.Add(itemSlot);

            itemSlot.transform.SetParent(parent);
        }
    }

    private void UpdateInventory()
    {
        InitItemSlots();

        if (inventoryTabType == EInventoryTabType.None)
        {
            for (int i = 0; i < inventory.Items.Count; i++)
            {
                itemSlots[i].SetItem(inventory.Items[i]);
            }
        }
        else
        {
            int slotCount = 0;

            foreach(ItemStack data in inventory.Items)
            {
                if(data.Item.TabType == inventoryTabType)
                {
                    itemSlots[slotCount++].SetItem(data);
                }
            }
        }
    }

    public void SetInventoryTab(EInventoryTabType tabType = EInventoryTabType.None)
    {
        inventoryTabType = tabType;
    }
}
