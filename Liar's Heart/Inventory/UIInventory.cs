using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class UIInventory : UIScene
{
    [SerializeField] private InventorySO curInventory = default;

    [SerializeField] private Transform parent = default;
    [SerializeField] private GameObject itemSlotPrefab = default;
    [SerializeField] private List<UIItemSlotBase> itemSlots = new List<UIItemSlotBase>();

    // Listening
    [SerializeField] private VoidEventChannelSO updateInventoryEvent;

    private void Awake()
    {
        updateInventoryEvent = Resources.Load<VoidEventChannelSO>("Events/Inventory/UpdateInventoyEvent");
    }

    private void OnEnable()
    {
        updateInventoryEvent.OnEventRaised += UpdateInventory;
    }

    private void OnDisable()
    {
        updateInventoryEvent.OnEventRaised -= UpdateInventory;
    }

    private void Start()
    {
        CreateItemSlots(curInventory.MaxItemCount);
        UpdateInventory();
    }

    private void InitItemSlots()
    {
        foreach(UIItemSlotBase data in itemSlots)
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
            UIItemSlotBase itemSlot = Instantiate(itemSlotPrefab).GetComponent<UIItemSlotBase>();
            itemSlots.Add(itemSlot);

            itemSlot.transform.SetParent(parent);
            itemSlot.GetComponent<RectTransform>().localScale = new Vector3(1, 1, 1);
        }
    }

    private void UpdateInventory()
    {
        InitItemSlots();

        for (int i = 0; i < curInventory.Items.Count; i++)
        {
            itemSlots[i].SetItem(curInventory.Items[i]);
        }
    }
}
