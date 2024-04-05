using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;
using TMPro;


public class UIRecordSlot : UIItemSlotBase
{
    [SerializeField] private Image hoverImage = default;
    [SerializeField] private TMP_Text titleText = default;
    [SerializeField] private UIEventHandler eventHandler = default;

    private void Awake()
    {
        eventHandler = Utility.GetOrAddComponent<UIEventHandler>(this.gameObject);
    }

    private void Start()
    {
        eventHandler.AddUIEvent(Click, EUIEventType.Click);
        eventHandler.AddUIEvent(ToggleHover, EUIEventType.Enter);
        eventHandler.AddUIEvent(ToggleHover, EUIEventType.Exit);
    }

    public override void Init()
    {
        base.Init();

        hoverImage.gameObject.SetActive(false);
    }

    public override void SetItem(ItemStack itemStack)
    {
        base.SetItem(itemStack);

        titleText.text = currentItem.Item.Title;
    }

    // Enter & Exit UI Event
    private void ToggleHover(PointerEventData eventData)
    {
        if (hoverImage.gameObject.activeSelf)
        {
            hoverImage.gameObject.SetActive(false);
        }
        else
        {
            hoverImage.gameObject.SetActive(true);
        }
    }

    // Click UI Event
    private void Click(PointerEventData eventData)
    {
        if (currentItem == null)
        {
            Debug.Log("This slot does not hold any items");
            return;
        }

        UIPopupRecord popupUI = GameManager.UI.LoadPopupUI<UIPopupRecord>("RecordPopup");
        popupUI.Init(currentItem);
        popupUI.SetVisible(true);
    }
}
