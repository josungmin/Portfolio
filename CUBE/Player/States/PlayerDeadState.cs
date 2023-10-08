using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerDeadState : IState
{
    private CharacterBase character;

    public PlayerDeadState(StateMachine entity)
    {
        this.character = entity as CharacterBase;
    }

    public void OnEnter()
    {
        character.SetStateType(ECharacterStateType.DeadState);
    }

    void IState.Update()
    {
        character.AniController.SetAnimation("die", false, 1.0f);
    }

    public void OnExit()
    {
        character.SetStateType(ECharacterStateType.None);
    }
}
