using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerIdleState : IState
{
    private CharacterBase character;

    public PlayerIdleState(StateMachine entity)
    {
        character = entity as CharacterBase;
    }

    public void OnEnter()
    {
        character.SetStateType(ECharacterStateType.IdleState);
    }

    public void Update()
    {
        character.AniController.SetAnimation("idle", true, 1.0f);
    }

    public void OnExit()
    {
        character.SetStateType(ECharacterStateType.None);
    }
}
