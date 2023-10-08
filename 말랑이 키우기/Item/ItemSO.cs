using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(fileName = "Item", menuName = "Inventory/Item")]
public class ItemSO : ScriptableObject
{
	[Tooltip("아이템의 이름")]
	[SerializeField] private string title = default;
	public string Title { get => title; }

	[Tooltip("아이템의 프리뷰 이미지(아이콘)")]
	[SerializeField] private Sprite previewImage = default;
	public Sprite PreviewImage { get => previewImage; }

	[Tooltip("아이템 설명")]
	[TextArea] [SerializeField] private string description = default;
	public string Description { get => description; }

	[Tooltip("아이템의 등급")]
	[SerializeField] private EItemQuality itemQuality = default;
	public EItemQuality ItemQuality { get => itemQuality; }

	[Tooltip("아이템의 종족")]
	[SerializeField] private EItemTribeType itemTribeType = default;
	public EItemTribeType ItemTribeType { get => itemTribeType; }

	[Tooltip("아이템의 종류")]
	[SerializeField] private EItemType itemType = default;
	public EItemType ItemType { get => itemType; }

	[Tooltip("인벤토리에서 아이템 정렬 조건")]
	[SerializeField] private EInventoryTabType tabType = default;
	public EInventoryTabType TabType { get => tabType; }

    [Tooltip("한 아이템 당 최대 중복 개수")]
	[SerializeField] private int maxStack = default;
	public int MaxStack { get => maxStack; }
}
