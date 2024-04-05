using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;

public class UIInventories : UIScene
{
    [SerializeField] private ToggleGroup toggleGroup = default;
    [SerializeField] private Color OnChangeColor = new Color(0, 255, 50, 255);

    [SerializeField] private Toggle evidenceToggle = default;
    [SerializeField] private TMP_Text evidenceToggleText = default;

    [SerializeField] private Toggle possessionToggle = default;
    [SerializeField] private TMP_Text possessionToggleText = default;

    [SerializeField] private Toggle recordToggle = default;
    [SerializeField] private TMP_Text recordToggleText = default;

    private UIScene evidenceInventoryUI = default;
    private UIScene possessionInventoryUI = default;
    private UIScene recordInventoryUI = default;

    void Start()
    {
        evidenceInventoryUI = GameManager.UI.LoadSceneUI<UIInventory>("EvidenceInventory");
        evidenceInventoryUI.transform.SetParent(this.transform);
        evidenceInventoryUI.SetVisible(false);

        possessionInventoryUI = GameManager.UI.LoadSceneUI<UIInventory>("PossessionInventory");
        possessionInventoryUI.transform.SetParent(this.transform);
        possessionInventoryUI.SetVisible(false);

        recordInventoryUI = GameManager.UI.LoadSceneUI<UIInventory>("RecordInventory");
        recordInventoryUI.transform.SetParent(this.transform);
        recordInventoryUI.SetVisible(false);

        // Toggle setting
        evidenceToggle.group = toggleGroup;
        possessionToggle.group = toggleGroup;
        recordToggle.group = toggleGroup;

        evidenceToggle.onValueChanged.AddListener(OnEvidenceToggle);
        possessionToggle.onValueChanged.AddListener(OnPossessionToggle);
        recordToggle.onValueChanged.AddListener(OnRecordToggle);

        OnEvidenceToggle(true);
    }

    private void OnEvidenceToggle(bool value)
    {
        evidenceInventoryUI.SetVisible(value);
        evidenceToggleText.color = value ? OnChangeColor : Color.white;

        GameManager.Sound.Play("SFX/SFX_Click_InventoryTab");
    }

    private void OnPossessionToggle(bool value)
    {
        possessionInventoryUI.SetVisible(value);
        possessionToggleText.color = value ? OnChangeColor : Color.white;

        GameManager.Sound.Play("SFX/SFX_Click_InventoryTab");
    }

    private void OnRecordToggle(bool value)
    {
        recordInventoryUI.SetVisible(value);
        recordToggleText.color = value ? OnChangeColor : Color.white;

        GameManager.Sound.Play("SFX/SFX_Click_InventoryTab");
    }
}
