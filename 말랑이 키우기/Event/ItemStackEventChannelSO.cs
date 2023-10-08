using UnityEngine;
using UnityEngine.Events;

[CreateAssetMenu(menuName = "Events/ItemStack Event Channel")]
public class ItemStackEventChannelSO : ScriptableObject
{
	public UnityAction<ItemStack> OnEventRaised;

	public void RaiseEvent(ItemStack value)
	{
		if (OnEventRaised != null)
			OnEventRaised.Invoke(value);
	}
}
