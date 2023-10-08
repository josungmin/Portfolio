using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerSkillState : IState
{
    private CharacterBase character;

    public float latency = 1.0f;
    public float aniTime = 1.0f;
    public float damage = 10.0f;
    private float currentTime = 0.0f;

    public PlayerSkillState(StateMachine entity)
    {
        this.character = entity as CharacterBase;
    }

    protected virtual void SkillAction()
    {
        return;
    }

    public void OnEnter()
    {
        character.SetStateType(ECharacterStateType.SKillState);

        currentTime = 0.0f;
    }

    public void Update()
    {
        character.AniController.SetAnimation("skill", false, 1.0f);

        if(currentTime <= aniTime)
        {
            if(latency <= currentTime)
            {
                SkillAction();
            }

            currentTime += Time.deltaTime;
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
