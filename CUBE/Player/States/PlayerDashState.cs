using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerDashState : IState
{
    private CharacterBase character;
    private Rigidbody2D rigidbody;

    private Vector2 lastDirection = Vector2.zero;
    private float currentTime = 0.0f;

    public float speed = 3.0f;
    public float time = 1.0f;

    public PlayerDashState(StateMachine entity)
    {
        this.character = entity as CharacterBase;

        rigidbody = character.Rigidbody;
    }

    public void OnEnter()
    {
        character.SetStateType(ECharacterStateType.DashState);
        
        lastDirection = character.Direction;
        currentTime = 0;
    }

    public void Update()
    {
        character.AniController.SetAnimation("dash", true, 1.0f);

        if(currentTime < time)
        {
            rigidbody.MovePosition(rigidbody.position + lastDirection * speed * Time.fixedDeltaTime);

            currentTime += Time.fixedDeltaTime;
        }
        else
        {
            character.ResetState();
        }
    }

    public void OnExit()
    {
        character.SetStateType(ECharacterStateType.None);
    }
}
