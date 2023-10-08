using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerCharacterExample : CharacterBase
{
    [SerializeField] private StatCollection stats;

    private void Start()
    {
        idleState = new PlayerIdleState(this);

        moveState = new PlayerMoveState(this);
        moveState.speed = stats.GetStat(EStatType.MoveSpeed).FinalValue;

        dashState = new PlayerDashState(this);
        dashState.speed = stats.GetStat(EStatType.DashSpeed).FinalValue;
        dashState.time = stats.GetStat(EStatType.DashTime).FinalValue;

        attackState = new PlayerAttackState(this);
        attackState.aniTimes = new float[3] { 0.833f, 0.833f, 0.833f };
        attackState.damage = stats.GetStat(EStatType.AtkPoint).FinalValue;

        skillState = new PlayerSkillState(this);
        skillState.aniTime = 0.8330f;
        skillState.latency = 0.6f;
        skillState.damage = stats.GetStat(EStatType.SkillAtkPoint).FinalValue;
    }
}
