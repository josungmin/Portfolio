using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerMoveState : IState
{
    private CharacterBase character;
    private Rigidbody2D rigidbody;

    public float speed = 3.0f;

    public PlayerMoveState(StateMachine entity)
    {
        this.character = entity as CharacterBase;

        rigidbody = character.Rigidbody;
    }

    public void OnEnter()
    {
        character.SetStateType(ECharacterStateType.MoveState);
    }

    public void Update()
    {
        character.AniController.SetAnimation("run", true, 1.0f);

        rigidbody.MovePosition(rigidbody.position + character.Direction * speed * Time.fixedDeltaTime);

        character.Filp();
    }

    public void OnExit()
    {
        character.SetStateType(ECharacterStateType.None);
    }
}
