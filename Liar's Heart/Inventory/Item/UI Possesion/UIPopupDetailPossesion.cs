using UnityEngine;
using UnityEngine.UI;
using TMPro;

public class UIPopupDetailPossesion : UIPopup
{
    [SerializeField] private ItemStack curItem = default;

    [SerializeField] private TMP_Text titleText = default;
    [SerializeField] private Image previewImage = default;
    [SerializeField] private TMP_Text examineResultText = default;
    [SerializeField] private TMP_Text trivialText = default;
    [SerializeField] private Button exitButton = default;

    private void Start()
    {
        exitButton.onClick.AddListener(() => SetVisible(false));
    }

    public void Init(ItemStack curItem)
    {
        this.curItem = curItem;

        PossessionSO item = this.curItem.Item as PossessionSO;
        titleText.text = item.Title;
        previewImage.sprite = item.PreviewImage;
        examineResultText.text = item.ExamineResult;
        trivialText.text = item.TrivialText;
    }
}
