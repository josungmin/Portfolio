using UnityEngine;

[CreateAssetMenu(fileName = "ItemEvidenceSO", menuName = "Inventory/Evidence")]
public class EvidenceSO : ItemSO
{
	[Tooltip("아이템 아이콘")]
	[SerializeField] private Sprite icon = default;
	public Sprite Icon { get => icon; }

	[Tooltip("아이템 설명")]
	[TextArea(10, 20)] [SerializeField] private string description = default;
	public string Description { get => description; }

	[Tooltip("아이템 감식 결과")]
	[TextArea(10, 20)] [SerializeField] private string examineResult = default;
	public string ExamineResult { get => examineResult; }

	[Tooltip("아이템 부가 설명")]
	[TextArea(10, 20)] [SerializeField] private string trivialText = default;
	public string TrivialText { get => trivialText; }
}
