using UnityEngine;
using UnityEngine.UI;
using TMPro;

public class UIPopupEvidence : UIPopup
{
    [SerializeField] private ItemStack curItem = default;

    [SerializeField] private TMP_Text titleText = default;
    [SerializeField] private Image previewImage = default;
    [SerializeField] private TMP_Text descriptionText = default;
    [SerializeField] private Button detailButton = default;
    [SerializeField] private Button exitButton = default;

    private void Start()
    {
        exitButton.onClick.AddListener(() => SetVisible(false));
        detailButton.onClick.AddListener(() => DetailButtonClick());
    }

    public void Init(ItemStack curItem)
    {
        this.curItem = curItem;

        EvidenceSO item = this.curItem.Item as EvidenceSO;
        titleText.text = item.Title;
        previewImage.sprite = item.PreviewImage;
        descriptionText.text = item.Description;
    }

    private void DetailButtonClick()
    {
        if (curItem == null)
        {
            Debug.Log("This slot does not hold any items");
            return;
        }

        UIPopupDetailEvidence popupUI = GameManager.UI.LoadPopupUI<UIPopupDetailEvidence>("EvidencePopupDetail");
        popupUI.Init(curItem);
        popupUI.SetVisible(true);
    }
}

