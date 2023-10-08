using UnityEngine;

public class StateMachine : MonoBehaviour
{
    private IState currentState;
    public IState CurrentState { get => currentState; }

    public void SetState(IState nextState)
    {
        if (currentState != null)
        {
            currentState.OnExit();
        }

        currentState = nextState;
        currentState.OnEnter();
    }

    public IState GetState()
    {
        Debug.Log(currentState);
        return this.currentState;
    }

    public void Excute()
    {
        currentState.Update();
    }
}
