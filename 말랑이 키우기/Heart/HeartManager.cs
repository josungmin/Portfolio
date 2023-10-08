using System.Collections;
using UnityEngine;
using System;

public class HeartManager : MonoBehaviour
{
    private HeartData heartData;
    private Coroutine curCorotine = null;

    [SerializeField] private int createTime = 600;
    private const string fullCountText = "MAX";

    // Broadcasting
    [SerializeField] private StringEventChannelSO setHeartTextEvent;
    [SerializeField] private StringEventChannelSO setTimeTextEvent;

    private void Start()
    {
        heartData = GameManager.Instance.GameData.HeartData;

        Init();
        ProduceHeart();
    }

    private void Init()
    {
        TimeSpan timeSpan = DateTime.Now - GameManager.Instance.GameData.LatestAccess;

        // heart count section
        int createdHeart = (int)timeSpan.TotalSeconds / createTime;
        AddHeart(createdHeart);

        setHeartTextEvent.RaiseEvent(heartData.CurCount.ToString()); // UI Update

        // heart timer section
        int resultTime = (int)timeSpan.TotalSeconds % createTime;
        heartData.SetTimer(resultTime);

        string time = (heartData.Timer / 60).ToString() + ":" + (heartData.Timer % 60).ToString();

        if (heartData.IsFull)
        {
            setTimeTextEvent.RaiseEvent(fullCountText);
            return;
        }

        setTimeTextEvent.RaiseEvent(time); // UI Update
    }

    public void AddHeart(int count)
    {
        bool result = heartData.Add(count);
        if (!result)
        {
            Debug.LogError("하트 획득 실패");
            return;
        }

        setHeartTextEvent.RaiseEvent(heartData.CurCount.ToString()); // UI Update
    }

    public void DeleteHeart()
    {
        if (!heartData.Delete())
        {
            Debug.LogError("하트 소모 실패");
            return;
        }

        setHeartTextEvent.RaiseEvent(heartData.CurCount.ToString()); // UI Update
    }

    private void ProduceHeart()
    {
        if (curCorotine != null)
        {
            return;
        }

        curCorotine = StartCoroutine(Producing());
    }

    private IEnumerator Producing()
    {
        heartData.SetTimer(createTime);

        while (true)
        {
            if(heartData.Timer == 0)
            {
                AddHeart(1);
                heartData.SetTimer(createTime);
            }

            if(heartData.IsFull)
            {
                setTimeTextEvent.RaiseEvent(fullCountText); // UI Update
            }

            yield return new WaitUntil(() => !heartData.IsFull);

            string time = (heartData.Timer / 60).ToString() + ":" + (heartData.Timer % 60).ToString();
            setTimeTextEvent.RaiseEvent(time); // UI Update

            yield return new WaitForSeconds(1.0f);
            heartData.DecreaseTimer(1);
        }

        StopProducing();
    }

    private void StopProducing()
    {
        if(curCorotine != null)
        {
            StopCoroutine(curCorotine);
        }

        curCorotine = null;
    }

    private void OnApplicationQuit()
    {
        GameManager.Instance.GameData.SetHeart(heartData);
    }
}
