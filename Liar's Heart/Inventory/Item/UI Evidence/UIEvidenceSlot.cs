using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;

public class UIEvidenceSlot : UIItemSlotBase
{
    [SerializeField] private Image hoverImage = default;

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
        if(currentItem == null)
        {
            Debug.Log("This slot does not hold any items");
            return;
        }

        UIPopupEvidence popupUI = GameManager.UI.LoadPopupUI<UIPopupEvidence>("EvidencePopup");
        popupUI.Init(currentItem);
        popupUI.SetVisible(true);
    }
}
