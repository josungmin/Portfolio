using UnityEngine;

public class ItemSO : ScriptableObject
{
	[Tooltip("아이템의 이름")]
	[SerializeField] private string title = default;
	public string Title { get => title; }

	[Tooltip("아이템의 프리뷰 이미지(아이콘)")]
	[SerializeField] private Sprite previewImage = default;
	public Sprite PreviewImage { get => previewImage; }

	[Tooltip("한 아이템 당 최대 중복 개수")]
	[SerializeField] private int maxStack = 1;
	public int MaxStack { get => maxStack; }
}
