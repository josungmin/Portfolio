using UnityEngine;
using UnityEngine.UI;

public class UIItemSlot : MonoBehaviour
{
    [SerializeField] private ItemStack currentItem = default;

    [SerializeField] private Image itemPreviewImage = default;
    [SerializeField] private Text itemStackCountText = default;

    public void Init()
    {
        currentItem = null;

        itemPreviewImage.sprite = null;
        itemPreviewImage.color = new Color(1, 1, 1, 0);

        itemStackCountText.text = "";
    }

    public void SetItem(ItemStack itemStack)
    {
        currentItem = itemStack;

        itemPreviewImage.sprite = itemStack.Item.PreviewImage;
        itemPreviewImage.color = new Color(1, 1, 1, 1);

        itemStackCountText.text = itemStack.Amount == 0 ? "" : itemStack.Amount.ToString();
    }
}
