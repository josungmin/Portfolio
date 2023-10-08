using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerAttackState : IState
{
    private CharacterBase character;

    private string aniName = "";
    public float[] aniTimes;
    private float currentTime;
    
    private int attackCount = 0;
    private bool isNextAttack = false;
    public bool IsNextAttack {  set => isNextAttack = value; }

    public float damage = 10.0f;

    public PlayerAttackState(StateMachine entity)
    {
        this.character = entity as CharacterBase;
    }

    protected virtual void AttackAction()
    {
        return;
    }

    public void OnEnter()
    {
        character.SetStateType(ECharacterStateType.AttackState);

        currentTime = 0.0f;
        attackCount++;
        isNextAttack = false;

        aniName = "attack_" + attackCount.ToString();
    }

    public void Update()
    {
        character.AniController.SetAnimation(aniName, false, 1.0f);

        if(currentTime < aniTimes[attackCount - 1])
        {
            AttackAction();

            currentTime += Time.deltaTime;
        }
        else
        {
            if(isNextAttack)
            {
                character.SetState(this);
            }
            else
            {
                character.ResetState();
            }
        }
    }

    public void OnExit()
    {
        if (isNextAttack)
        {
            if (attackCount >= aniTimes.Length)
            {
                attackCount = 0;
            }

            return;
        }

        attackCount = 0;
        character.SetStateType(ECharacterStateType.None);
    }
}
