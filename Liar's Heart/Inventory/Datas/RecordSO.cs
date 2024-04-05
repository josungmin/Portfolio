using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(fileName = "RecordSO", menuName = "Inventory/Record")]
public class RecordSO : ItemSO
{
    [SerializeField] private List<ChatData> dialogueDatas = new List<ChatData>();
    public List<ChatData> DialogueDatas { get => dialogueDatas; }
}
