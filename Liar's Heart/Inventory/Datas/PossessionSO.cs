using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(fileName = "PossessionSO", menuName = "Inventory/Possession")]
public class PossessionSO : ItemSO
{
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