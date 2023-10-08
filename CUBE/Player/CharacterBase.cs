using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public enum ECharacterStateType
{
    None,
    IdleState,
    MoveState,
    DashState,
    AttackState,
    SKillState,
    DeadState,
}

public class CharacterBase : StateMachine
{
    private ECharacterStateType currentState = ECharacterStateType.None;

    // Components
    private SpineAnimationContoroller aniController;
    public SpineAnimationContoroller AniController { get => aniController; }

    private new Rigidbody2D rigidbody;
    public Rigidbody2D Rigidbody { get => rigidbody; }

    // States
    protected PlayerIdleState idleState;
    protected PlayerMoveState moveState;
    protected PlayerDashState dashState;
    protected PlayerAttackState attackState;
    protected PlayerSkillState skillState;

    public PlayerIdleState IdleState { get => idleState; }
    public PlayerMoveState MoveState { get => moveState; }
    public PlayerDashState DashState { get => dashState; }
    public PlayerAttackState AttackState { get => attackState; }
    public PlayerSkillState SkillState { get => skillState; }


    public Vector2 Direction { get => new Vector2(Input.GetAxisRaw("Horizontal"), Input.GetAxisRaw("Vertical")); }


    protected virtual void Awake()
    {
        aniController = Utility.GetOrAddComponent<SpineAnimationContoroller>(this.gameObject);
        rigidbody = Utility.GetOrAddComponent<Rigidbody2D>(this.gameObject);
    }

    protected virtual void Update()
    {
        if (Input.GetKeyDown(KeyCode.A)) OnAttack();
        if (Input.GetKeyDown(KeyCode.S)) OnSkill();

        if (Input.GetKeyDown(KeyCode.Space)) OnDash();
        else if (Direction != Vector2.zero) OnMove();
        else OnIdle();

        Excute();
    }

    // Idle Section
    private void OnIdle()
    {
        if (!CanIdle())
        {
            SetState(idleState);
        }
    }

    protected virtual bool CanIdle()
    {
        return
            currentState == ECharacterStateType.DashState ||
            currentState == ECharacterStateType.AttackState ||
            currentState == ECharacterStateType.DeadState;
    }

    // Move Section
    private void OnMove()
    {
        if (!CanMove())
        {
            SetState(moveState);
        }
    }

    protected virtual bool CanMove()
    {
        return
            currentState == ECharacterStateType.DashState ||
            currentState == ECharacterStateType.AttackState ||
            currentState == ECharacterStateType.SKillState ||
            currentState == ECharacterStateType.DeadState;
    }

    // Dash Section
    private void OnDash()
    {
        if (!CanDash())
        {
            SetState(dashState);
        }
    }

    protected virtual bool CanDash()
    {
        return
            currentState == ECharacterStateType.IdleState ||
            currentState == ECharacterStateType.DashState ||
            currentState == ECharacterStateType.AttackState ||
            currentState == ECharacterStateType.SKillState ||
            currentState == ECharacterStateType.DeadState;
    }

    // Attack Section
    private void OnAttack()
    {
        if (!CanAttack())
        {
            if (currentState == ECharacterStateType.AttackState)
            {
                attackState.IsNextAttack = true;
            }
            else
            {
                SetState(attackState);
            }
        }
    }

    protected virtual bool CanAttack()
    {
        return
            currentState == ECharacterStateType.DashState ||
            currentState == ECharacterStateType.SKillState ||
            currentState == ECharacterStateType.DeadState;
    }

    // Skill Section
    private void OnSkill()
    {
        if(!CanSkill())
        {
            SetState(skillState);
        }
    }

    protected virtual bool CanSkill()
    {
        return
            currentState == ECharacterStateType.DashState ||
            currentState == ECharacterStateType.AttackState ||
            currentState == ECharacterStateType.SKillState ||
            currentState == ECharacterStateType.DeadState;
    }

    // Default Section
    public void SetStateType(ECharacterStateType StateType)
    { 
        if(currentState != StateType)
        {
            currentState = StateType;
        }
    }

    public void ResetState()
    {
        SetState(IdleState);
    }

    public void Filp()
    {
        Vector3 newScale = transform.localScale;

        if (Direction.x == 1)
        {
            newScale.x = -Mathf.Abs(newScale.x);
        }
        else if (Direction.x == -1)
        {
            newScale.x = Mathf.Abs(newScale.x);
        }

        this.transform.localScale = newScale;
    }
}
