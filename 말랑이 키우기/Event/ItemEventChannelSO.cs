using UnityEngine;
using UnityEngine.Events;

[CreateAssetMenu(menuName = "Events/Item Event Channel")]
public class ItemEventChannelSO : ScriptableObject
{
	public UnityAction<ItemSO> OnEventRaised;

	public void RaiseEvent(ItemSO value)
	{
		if (OnEventRaised != null)
			OnEventRaised.Invoke(value);
	}
}
