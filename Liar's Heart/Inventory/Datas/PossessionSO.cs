using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(fileName = "PossessionSO", menuName = "Inventory/Possession")]
public class PossessionSO : ItemSO
{
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