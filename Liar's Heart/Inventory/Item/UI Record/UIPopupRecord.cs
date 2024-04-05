using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;

public class UIPopupRecord : UIPopup
{
    [SerializeField] private ItemStack curItem = default;
    [SerializeField] private TMP_Text titleText = default;

    [SerializeField] private Transform parent;
    [SerializeField] private GameObject ChatMessagePrefab;

    [SerializeField] Button exitButton;

    private void Start()
    {
        exitButton.onClick.AddListener(() => SetVisible(false));
    }

    public void Init(ItemStack curItem)
    {
        this.curItem = curItem;

        RecordSO item = this.curItem.Item as RecordSO;
        titleText.text = item.Title;
        
        for(int i = 0; i < item.DialogueDatas.Count; i++)
        {
            UIChatMessage clone = Instantiate(ChatMessagePrefab, parent).GetComponent<UIChatMessage>();
            CharacterSO tmp = item.DialogueDatas[i].Speeker;
            
            clone.Init(tmp);
            clone.SetText(item.DialogueDatas[i].Content);
        }
    }
}
