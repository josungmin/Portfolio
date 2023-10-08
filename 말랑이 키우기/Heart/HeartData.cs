using UnityEngine;

[System.Serializable]
public class HeartData
{
    [SerializeField] private int maxCount = default;
    public int MaxCount { get => maxCount; }

    [SerializeField] private int curCount = default;
    public int CurCount { get => curCount; }

    [SerializeField] private int timer = default;
    public int Timer { get => timer; }

    public bool IsFull { get { return maxCount <= curCount; } }
    public bool IsEmpty { get { return curCount <= 0; } }

    // isExceed => true 전달 시 최대 갯수 이상 추가 가능
    public bool Add(int count, bool isExceed = false)
    {
        if (IsFull && !isExceed)
        {
            return false;
        }

        if(maxCount < (curCount + count) && !isExceed)
        {
            curCount = maxCount;
            return true;
        }

        curCount += count;

        return true;
    }

    public bool Delete()
    {
        if (IsEmpty)
        {
            return false;
        }

        curCount -= 1;

        return true;
    }

    public void SetTimer(int time)
    {
        timer = time;
    }

    public bool DecreaseTimer(int second)
    {
        if(timer <= 0 && timer - second < 0)
        {
            return false;
        }

        timer -= second;

        return true;
    }
}
