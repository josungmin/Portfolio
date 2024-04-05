using UnityEngine;
using UnityEngine.UI;

public class UIItemSlotBase : MonoBehaviour
{
    [SerializeField] protected ItemStack currentItem = default;
    [SerializeField] protected Image previewImage = default;

    public virtual void Init()
    {
        currentItem = null;
        previewImage.gameObject.SetActive(false);
    }

    public virtual void SetItem(ItemStack itemStack)
    {
        currentItem = itemStack;
        previewImage.gameObject.SetActive(true);
        previewImage.sprite = itemStack.Item.PreviewImage;
    }
}
