using UnityEngine;
using UnityEngine.UI;

public class UIHeart : MonoBehaviour
{
    [SerializeField] private Text heartText = default;
    [SerializeField] private Text timeText = default;

    // Listening
    public StringEventChannelSO setHeartTextEvent;
    public StringEventChannelSO setTimeTextEvent;

    private void OnEnable()
    {
        setHeartTextEvent.OnEventRaised += SetHeartText;
        setTimeTextEvent.OnEventRaised += SetTimeText;
    }

    private void OnDisable()
    {
        setHeartTextEvent.OnEventRaised -= SetHeartText;
        setTimeTextEvent.OnEventRaised -= SetTimeText;
    }

    private void SetHeartText(string heart)
    {
        heartText.text = heart;
    }

    private void SetTimeText(string time)
    {
        timeText.text = time;
    }
}