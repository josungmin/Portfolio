using UnityEngine;

[CreateAssetMenu(fileName = "ItemEvidenceSO", menuName = "Inventory/Evidence")]
public class EvidenceSO : ItemSO
{
	[Tooltip("������ ������")]
	[SerializeField] private Sprite icon = default;
	public Sprite Icon { get => icon; }

	[Tooltip("������ ����")]
	[TextArea(10, 20)] [SerializeField] private string description = default;
	public string Description { get => description; }

	[Tooltip("������ ���� ���")]
	[TextArea(10, 20)] [SerializeField] private string examineResult = default;
	public string ExamineResult { get => examineResult; }

	[Tooltip("������ �ΰ� ����")]
	[TextArea(10, 20)] [SerializeField] private string trivialText = default;
	public string TrivialText { get => trivialText; }
}
