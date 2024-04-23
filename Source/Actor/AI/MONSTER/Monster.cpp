#include "stdafx.h"
#include "Monster.h"
#include <time.h>
#include <stdlib.h>

#define GetNowScene()          GameManager->GetNowScene()
#define TIME                   Time::Get::Delta()

#define non_Inter              GetNowScene()->noninter_Cols
#define     Inter              GetNowScene()->inter_Cols

#define RIGHT                  LeftRight ==  1
#define LEFT                   LeftRight == -1

#define PLAYER_XPOS            GameManager->BS->GetPlayerLocation()[0]
#define PLAYER_YPOS            GameManager->BS->GetPlayerLocation()[1]

#define BEAM_COOL 0.13f
#define BEAM_COUNT 6


using namespace Collision;

AMonster::AMonster()
{

#pragma region ElderBrother [ Ani / Collider ]
    // Idle
    Elder_Idle_A.Content = "Mon_Elder/IDLE/Idle";
    Elder_Idle_A.Length = { 400 , 300 };
    Elder_Idle_A.Loop = true;
    Elder_Idle_A.Duration = 1;

    // JUMP
    Elder_JumpOn_A.Content = "Mon_Elder/JUMP/JumpOn";
    Elder_JumpOn_A.Length = { 400 , 300 };
    Elder_JumpOn_A.Loop = false;
    Elder_JumpOn_A.Duration = 0.7f;

    Elder_Jumping_A.Content = "Mon_Elder/JUMP/Jumping";
    Elder_Jumping_A.Length = { 400 , 300 };
    Elder_Jumping_A.Loop = false;
    Elder_Jumping_A.Duration = 1;

    Elder_JumpOff_A.Content = "Mon_Elder/JUMP/JumpOff";
    Elder_JumpOff_A.Length = { 400 , 300 };
    Elder_JumpOff_A.Loop = false;
    Elder_JumpOff_A.Duration = 0.7f;
    // Attack
    Elder_Attack_A.Content = "Mon_Elder/ATTACK/Attack";
    Elder_Attack_A.Length = { 400 , 300 };
    Elder_Attack_A.Loop = false;
    Elder_Attack_A.Duration = 1.6f;

    //Death
    Elder_Death1_A.Content = "Mon_Elder/DEATH/Death1";
    Elder_Death1_A.Length = { 400 , 300 };
    Elder_Death1_A.Loop = false;
    Elder_Death1_A.Duration = 3.8f;

    Elder_Death2_A.Content = "Mon_Elder/DEATH/Death2";
    Elder_Death2_A.Length = { 400 , 300 };
    Elder_Death2_A.Loop = false;
    Elder_Death2_A.Duration = 2;

    Elder_Beam_A.Content = "Mon_Elder/BEAM/BEAM";
    Elder_Beam_A.Length = { 118 , 85 };
    Elder_Beam_A.Loop = false;
    Elder_Beam_A.Duration = 1;

    // Collider
    Elder_Feet_Col.Content = "M_Col/FeetCol";
    Elder_Feet_Col.Length = { 120,10 };

    Elder_Hitbox_Col.Content = "M_Col/HitboxCol";
    Elder_Hitbox_Col.Length = { 100,130 };

    Elder_Hit_Col.Content = "M_Col/InRangeCol";
    Elder_Hit_Col.Length = { 90, 30 };

    Elder_Attack_Col.Content = "M_Col/InRangeCol";
    Elder_Attack_Col.Length = { 160,100 };

    Beam_Col.Content = "M_Col/HitCol";
    Beam_Col.Length = { 40,30 };

#pragma endregion 

#pragma region Shield_Mon [ Ani / Collider ]
    // Idle
    Shield_Idle_A.Content = "Mon_Shield/IDLE/Idle";
    Shield_Idle_A.Length = { 200,100 };
    Shield_Idle_A.Loop = true;
    Shield_Idle_A.Duration = 1;


    // Attack
    Shield_AttackOn_A.Content = "Mon_Shield/ATTACK/Attack_On";
    Shield_AttackOn_A.Length = { 200,100 };
    Shield_AttackOn_A.Loop = false;
    Shield_AttackOn_A.Duration = 0.3f;

    Shield_AttackOff_A.Content = "Mon_Shield/ATTACK/Attack_Off";
    Shield_AttackOff_A.Length = { 200,100 };
    Shield_AttackOff_A.Loop = false;
    Shield_AttackOff_A.Duration = 0.5f;

    // Parry
    Shield_Parry_A.Content = "Mon_Shield/PARRY/Parry";
    Shield_Parry_A.Length = { 200,100 };
    Shield_Parry_A.Loop = false;
    Shield_Parry_A.Duration = 1.5f;

    // Walk
    Shield_Walk_A.Content = "Mon_Shield/WALK/Walk";
    Shield_Walk_A.Length = { 200,100 };
    Shield_Walk_A.Loop = false;
    Shield_Walk_A.Duration = 1;

    // Death
    Shield_Execution_A.Content = "Mon_Shield/DEATH/Execution";
    Shield_Execution_A.Length = { 250,100 };
    Shield_Execution_A.Loop = false;
    Shield_Execution_A.Duration = 3;

    Shield_Death_A.Content = "Mon_Shield/DEATH/Death";
    Shield_Death_A.Length = { 200,100 };
    Shield_Death_A.Loop = false;
    Shield_Death_A.Duration = 2.5f;

    Shield_Sturn_A.Content = "Mon_Shield/DEATH/Sturn";
    Shield_Sturn_A.Length = { 200,100 };
    Shield_Sturn_A.Loop = false;
    Shield_Sturn_A.Duration = 2;



    // Collider
    Shield_Feet_Col.Content = "M_Col/FeetCol";
    Shield_Feet_Col.Length = { 30,10 };

    Shield_Hitbox_Col.Content = "M_Col/HitboxCol";
    Shield_Hitbox_Col.Length = { 30, 50 };

    Shield_Hit_Col.Content = "M_Col/HitCol";
    Shield_Hit_Col.Length = { 30, 50 };

    Shield_Attack_Col.Content = "M_Col/FeetCol";
    Shield_Attack_Col.Length = { -1, -1 };
    //Attack_Col_Length = { 30 , 50 };

    Shield_Alert_Col.Content = "M_Col/AlertCol";
    Shield_Alert_Col.Length = { 400, 50 };

    Shield_InRange_Col.Content = "M_Col/InRangeCol";
    Shield_InRange_Col.Length = { 150, 50 };

#pragma endregion

#pragma region LionHead [ Ani / Collider ]

    LionHead_Idle_A.Content = "Mon_LionHead/IDLE/Idle";
    LionHead_Idle_A.Length = { 140,180 };
    LionHead_Idle_A.Loop = true;
    LionHead_Idle_A.Duration = 1;

    LionHead_Walk_A.Content = "Mon_LionHead/WALK/Walk";
    LionHead_Walk_A.Length = { 140,180 };
    LionHead_Walk_A.Loop = false;
    LionHead_Walk_A.Duration = 1;

    LionHead_Walk_BackWard_A.Content = "Mon_LionHead/WALK/Walk_BackWard";
    LionHead_Walk_BackWard_A.Length = { 140,180 };
    LionHead_Walk_BackWard_A.Loop = false;
    LionHead_Walk_BackWard_A.Duration = 1;


    LionHead_Attack_A.Content = "Mon_LionHead/ATTACK/Attack";
    LionHead_Attack_A.Length = { 400,180 };
    LionHead_Attack_A.Loop = false;
    LionHead_Attack_A.Duration = 1.3f;


    LionHead_Death_A.Content = "Mon_LionHead/DEATH/Death";
    LionHead_Death_A.Length = { 200,180 };
    LionHead_Death_A.Loop = false;
    LionHead_Death_A.Duration = 3;



    LionHead_Feet_Col.Content = "M_Col/FeetCol";
    LionHead_Feet_Col.Length = { 30,10 };

    LionHead_Hitbox_Col.Content = "M_Col/HitboxCol";
    LionHead_Hitbox_Col.Length = { 60, 130 };


    LionHead_Alert_Col.Content = "M_Col/AlertCol";
    LionHead_Alert_Col.Length = { 500, 130 };

    LionHead_InRange_Col.Content = "M_Col/InRangeCol";
    LionHead_InRange_Col.Length = { 250, 130 };

#pragma endregion 

#pragma region Foil [ Ani / Collider ]

    Foil_Idle_A.Content = "Mon_Foil/IDLE/Idle";
    Foil_Idle_A.Length = { 180,120 };
    Foil_Idle_A.Loop = true;
    Foil_Idle_A.Duration = 1;

    Foil_Appear_Attack_A.Content = "Mon_Foil/ATTACK/Appear_Attack";
    Foil_Appear_Attack_A.Length = { 140,120 };
    Foil_Appear_Attack_A.Loop = false;
    Foil_Appear_Attack_A.Duration = 1;

    Foil_Attack_To_Idle_A.Content = "Mon_Foil/ATTACK/Attack_To_Idle";
    Foil_Attack_To_Idle_A.Length = { 180,120 };
    Foil_Attack_To_Idle_A.Loop = false;
    Foil_Attack_To_Idle_A.Duration = 1.5f;


    Foil_Hurt_A.Content = "Mon_Foil/HURT/Hurt";
    Foil_Hurt_A.Length = { 180,120 };
    Foil_Hurt_A.Loop = false;
    Foil_Hurt_A.Duration = 1.3f;


    Foil_Parry_A.Content = "Mon_Foil/PARRY/Parry";
    Foil_Parry_A.Length = { 180,130 };
    Foil_Parry_A.Loop = false;
    Foil_Parry_A.Duration = 1;


    Foil_Death_A.Content = "Mon_Foil/DEATH/Death";
    Foil_Death_A.Length = { 180,120 };
    Foil_Death_A.Loop = false;
    Foil_Death_A.Duration = 2;



    Foil_Hitbox_Col.Content = "M_Col/HitboxCol";
    Foil_Hitbox_Col.Length = { 130, 100 };

    Foil_Alert_Col.Content = "M_Col/AlertCol";
    Foil_Alert_Col.Length = { 500, 100 };

    Foil_InRange_Col.Content = "M_Col/InRangeCol";
    Foil_InRange_Col.Length = { 200, 100 };


#pragma endregion 
    // Effect
    Shield_Effect_A.Content = "Mon_Shield/ShieldEffect";
    Shield_Effect_A.Length = { 100,100 };
    Shield_Effect_A.Loop = false;
    Shield_Effect_A.Duration = 0.4f;

    Spark_Eff1_A.Content = "HITEFFECT/SparkRevision1";
    Spark_Eff1_A.Length = { 200,100 };
    Spark_Eff1_A.Loop = false;
    Spark_Eff1_A.Duration = 0.3f;

    Spark_Eff2_A.Content = "HITEFFECT/SparkRevision2";
    Spark_Eff2_A.Length = { 200,100 };
    Spark_Eff2_A.Loop = false;
    Spark_Eff2_A.Duration = 0.3f;

    Spark_Eff3_A.Content = "HITEFFECT/SparkRevision3";
    Spark_Eff3_A.Length = { 200,100 };
    Spark_Eff3_A.Loop = false;
    Spark_Eff3_A.Duration = 0.3f;

    Effect_Idle_A.Content = "HITEFFECT/Effect_Idle";
    Effect_Idle_A.Length = { DEFAULTSIZE, DEFAULTSIZE };
    Effect_Idle_A.Loop = true;
    Effect_Idle_A.Duration = 1;

    Boss_Name = { "침묵의 비탄 파수꾼", {"Blasphemous" , 40} , {173,155,57} ,{680 , 640} };

    HP_Bar.Content = "HP_BAR/Mon_Hp_Bar";
    HP_Bar.Length = { 34 , 4 };

    HP_Remain.Content = "HP_BAR/Mon_HP";
    HP_Remain.Length = { 2 , 2 };



    Boss_HP_Bar.Content = "HP_BAR/Boss_HP";
    Boss_HP_Bar.Length = { 346 , 30 };

    Boss_HP_Remain.Content = "HP_BAR/Boss_HP_Remain";
    Boss_HP_Remain.Length = { 2 , 6 };


    full_HP = 0;
    Hp = 0;
    soul = 0;


    // SCENE에서 계속 바꿀꺼임
    M_Effect_Anim = Effect_Idle_A;
    M_Anim = Elder_Idle_A;
    Elder_Effect_Anim[0] = Effect_Idle_A;
    Elder_Effect_Anim[1] = Effect_Idle_A;
    Elder_Effect_Anim[2] = Effect_Idle_A;
    Elder_Effect_Anim[3] = Effect_Idle_A;
    Elder_Effect_Anim[4] = Effect_Idle_A;
    Elder_Effect_Anim[5] = Effect_Idle_A;
    Elder_Effect_Anim[6] = Effect_Idle_A;
    Elder_Effect_Anim[7] = Effect_Idle_A;
}

namespace
{

}



void AMonster::DrawHpBar()
{
    GetPercentage();

    HP_Bar.Location = M_Anim.Location;

    if (MONSTER_TYPE_CHK(MONSTER_TYPE::SHIELD_MON))
    {
        HP_Bar.Location[1] = M_Anim.Location[1] + 25;
    }
    else if (MONSTER_TYPE_CHK(MONSTER_TYPE::LIONHEAD))
    {
        HP_Bar.Location[1] = M_Anim.Location[1] + 75;
    }

    else if (MONSTER_TYPE_CHK(MONSTER_TYPE::FOIL_MON))
    {
        HP_Bar.Location[1] = M_Anim.Location[1] + 40;
    }


    HP_Remain.Location[0] = HP_Bar.Location[0] - HP_Bar.Length[0] / 2 + 1;
    HP_Remain.Location[1] = HP_Bar.Location[1];


    HP_Remain.Length = { HP_Gauge , 2 };


    if (Hp > 0)
    {
        HP_Bar.Draw();
        HP_Remain.Draw();
    }
}

void AMonster::DrawBossHpBar()
{
    //GetPercentage();

    HP_Bar.Location = M_Anim.Location;

    if (MONSTER_TYPE_CHK(MONSTER_TYPE::ELDER))
    {
        HP_Bar.Location[1] = M_Anim.Location[1] - 50;
    }

    HP_Remain.Location[0] = HP_Bar.Location[0] - HP_Bar.Length[0] / 2 + 1;
    HP_Remain.Location[1] = HP_Bar.Location[1];

    if (Hp > 0)
    {
        HP_Bar.Draw();
        HP_Remain.Draw();
    }
}


bool AMonster::CHK_PlayerAttacking()
{
    if (M_Effect_Anim.Content == "HITEFFECT/SparkRevision1" || M_Effect_Anim.Content == "HITEFFECT/SparkRevision2"
        || M_Effect_Anim.Content == "HITEFFECT/SparkRevision3" || M_Effect_Anim.Content == "Mon_Shield/HITEFFECT/ShieldEffect")
        return true;
    else
        return false;
}

void AMonster::Elder_BEAM_Logic()
{
    for (int i = 0; i < 8; i++)
    {
        if (!Elder_Effect_Anim[i].Loop)
        {
            if (Elder_Effect_Anim[i].Content == "Mon_Elder/BEAM/BEAM")
            {
                if (Elder_Effect_Anim[i].End)
                {
                    Elder_E_Swap(Effect_Idle_A, i);
                }
            }
        }
    }


    if(BeamStart)
    Elder_Effect_Anim[0].Location[0] = M_Anim.Location[0] + (60 * LeftRight);

    for (int i = 0; i < GetNowScene()->noninter_Cols.Floor_Col.size(); i++)
    {
        if (Elder_Effect_Anim[beam_index].Location[0]    <= GetNowScene()->noninter_Cols.Floor_Col[i].Location[0] + GetNowScene()->noninter_Cols.Floor_Col[i].Length[0] / 2
            && Elder_Effect_Anim[beam_index].Location[0] >= GetNowScene()->noninter_Cols.Floor_Col[i].Location[0] - GetNowScene()->noninter_Cols.Floor_Col[i].Length[0] / 2)
            Elder_Effect_Anim[beam_index].Location[1] = GetNowScene()->noninter_Cols.Floor_Col[i].Location[1] + (Elder_Effect_Anim[beam_index].Length[1] + GetNowScene()->noninter_Cols.Floor_Col[i].Length[1]) / 2;
    }


    if (BeamStart)
        beam_cool += 1 * TIME;

    if (beam_cool >= BEAM_COOL && beam_index <= BEAM_COUNT)
    {
        ++beam_index;
        nextBeam = true;
        beam_cool = 0;
    }
    if (nextBeam)
    {
        Elder_E_Swap(Elder_Beam_A, beam_index);
        nextBeam = false;
    }

 
    for (int i = 1; i < 8; i++)
    {
        Elder_Effect_Anim[i].Location[0] = Elder_Effect_Anim[i-1].Location[0] + (50 * LeftRight);
    }

    for (int i = 0; i < 8; i++)
    {
        if (BeamStart)
        {
            Elder_Effect_Anim[i].Draw();
        }
    }

    if (BeamStart && Elder_Effect_Anim[7].Content == "Mon_Elder/BEAM/BEAM")
    {
        if (Elder_Effect_Anim[7].End)
        {
            beam_index = 0;
            beam_cool = 0;
            BeamStart = false;
        }
    }
}



void AMonster::Start()
{
    GetTickCount64();
}

//SetActorTransform(M_Anim);
//M_Anim.Location[1] = non_Inter.Floor_Col[i].Location[1] + (M_Anim.Length[1] + non_Inter.Floor_Col[i].Length[1]) / 2; // 땅위


void AMonster::DrawCollider()
{

    if (MONSTER_TYPE_CHK(MONSTER_TYPE::ELDER))
    {
        Elder_Feet_Col.Location[0] = M_Anim.Location[0];
        Elder_Feet_Col.Location[1] = M_Anim.Location[1] - M_Anim.Length[1] / 2;

        Elder_Hitbox_Col.Location[0] = M_Anim.Location[0] - (20 * LeftRight);
        Elder_Hitbox_Col.Location[1] = M_Anim.Location[1] - 90;

        Elder_Hit_Col.Location[0] = M_Anim.Location[0] - (20 * LeftRight);
        Elder_Hit_Col.Location[1] = M_Anim.Location[1] - 130;

        Elder_Attack_Col.Location[0] = M_Anim.Location[0] + (40 * LeftRight);
        Elder_Attack_Col.Location[1] = M_Anim.Location[1] - 80;
        

        //BeamCol이랑 이펙트 좌자작 나오게 + 공격이후 다시 리셋
        if (BeamStart )
        {
            Beam_Col.Location = Elder_Effect_Anim[beam_index].Location;
            Beam_Col.Location[1] = Elder_Effect_Anim[beam_index].Location[1] - 20;
        }


        if (Release)
        {
            Elder_Feet_Col.Draw();
            Elder_Hitbox_Col.Draw();
            Elder_Hit_Col.Draw();
            Elder_Attack_Col.Draw();
            Beam_Col.Draw();
        }

    }

    else if (MONSTER_TYPE_CHK(MONSTER_TYPE::SHIELD_MON))
    {
        Shield_Feet_Col.Location[0] = M_Anim.Location[0];
        Shield_Feet_Col.Location[1] = M_Anim.Location[1] - M_Anim.Length[1] / 2;


        Shield_Hitbox_Col.Location[0] = M_Anim.Location[0] - (10 * LeftRight);
        Shield_Hitbox_Col.Location[1] = M_Anim.Location[1] - 20;

        Shield_Hit_Col.Location[0] = M_Anim.Location[0] + (25 * LeftRight);
        Shield_Hit_Col.Location[1] = M_Anim.Location[1] - 20;

        Shield_Attack_Col.Location[0] = M_Anim.Location[0] + (50 * LeftRight);
        Shield_Attack_Col.Location[1] = M_Anim.Location[1] - 20;

        Shield_Alert_Col.Location[0] = M_Anim.Location[0];
        Shield_Alert_Col.Location[1] = M_Anim.Location[1] - 20;

        Shield_InRange_Col.Location[0] = M_Anim.Location[0];
        Shield_InRange_Col.Location[1] = M_Anim.Location[1] - 20;


        if (Release)
        {
            Shield_Alert_Col.Draw();
            Shield_InRange_Col.Draw();
            Shield_Hitbox_Col.Draw();
            Shield_Hit_Col.Draw(); // 나중에 늘리던가

            if (isAttack_Activate)
            {
                Shield_Attack_Col.Draw();
            }

            Shield_Feet_Col.Draw();
        }
    }

    else if (MONSTER_TYPE_CHK(MONSTER_TYPE::LIONHEAD))
    {
        LionHead_Feet_Col.Location[0] = M_Anim.Location[0];
        LionHead_Feet_Col.Location[1] = M_Anim.Location[1] - M_Anim.Length[1] / 2;


        LionHead_Hitbox_Col.Location[0] = M_Anim.Location[0] - 10;
        LionHead_Hitbox_Col.Location[1] = M_Anim.Location[1] - 30;


        LionHead_Alert_Col.Location[0] = M_Anim.Location[0];
        LionHead_Alert_Col.Location[1] = M_Anim.Location[1] - 30;

        LionHead_InRange_Col.Location[0] = M_Anim.Location[0];
        LionHead_InRange_Col.Location[1] = M_Anim.Location[1] - 30;


        if (Release)
        {
            LionHead_Alert_Col.Draw();
            LionHead_InRange_Col.Draw();
            LionHead_Hitbox_Col.Draw();

            LionHead_Feet_Col.Draw();
        }
    }

    else if (MONSTER_TYPE_CHK(MONSTER_TYPE::FOIL_MON))
    {
        Foil_Hitbox_Col.Location[0] = M_Anim.Location[0];
        Foil_Hitbox_Col.Location[1] = M_Anim.Location[1] - 15;

        Foil_Alert_Col.Location[0] = M_Anim.Location[0];
        Foil_Alert_Col.Location[1] = M_Anim.Location[1] - 15;

        Foil_InRange_Col.Location[0] = M_Anim.Location[0];
        Foil_InRange_Col.Location[1] = M_Anim.Location[1] - 15;

        if (Release)
        {
            Foil_Alert_Col.Draw();
            Foil_InRange_Col.Draw();
            Foil_Hitbox_Col.Draw();
        }
    }
}


void AMonster::Update()
{
    DrawCollider(); // TEST용 몬스터 뒤쪽에 COllider 그림

    if (Input::Get::Key::Press(VK_F5)) // 없앨거
    {
        GameStart = true;
    }

    M_Effect_Anim.Location = M_Anim.Location;

   
    if (!M_Effect_Anim.Loop)
    {
        if (M_Effect_Anim.Content == "HITEFFECT/SparkRevision1")
        {
            if (M_Effect_Anim.End)
                E_Swap(Effect_Idle_A);
        }
        if (M_Effect_Anim.Content == "HITEFFECT/SparkRevision2")
        {
            if (M_Effect_Anim.End)
                E_Swap(Effect_Idle_A);
        }
        if (M_Effect_Anim.Content == "HITEFFECT/SparkRevision3")
        {
            if (M_Effect_Anim.End)
                E_Swap(Effect_Idle_A);
        }

        if (M_Effect_Anim.Content == "Mon_Shield/ShieldEffect")
        {
            M_Effect_Anim.Location[0] = Shield_Hit_Col.Location[0] - 10;
            M_Effect_Anim.Location[1] = Shield_Hit_Col.Location[1] + 10;

            if (M_Effect_Anim.End)
                E_Swap(Effect_Idle_A);
        }
    }




    //printf("M_EFF.content : %s \n", M_Effect_Anim.Content);

    if (MONSTER_TYPE_CHK(MONSTER_TYPE::ELDER))
    {
        GetBossPercentage();
        if (PLAYER_XPOS >= -406 && PLAYER_XPOS <= 406)
        {
            Boss_HP_Bar.Location[0] = PLAYER_XPOS;
        }

        Boss_HP_Bar.Location[1] = PLAYER_YPOS - 80;

        Boss_HP_Remain.Location[0] = Boss_HP_Bar.Location[0] - Boss_HP_Bar.Length[0] / 2 + 30;
        Boss_HP_Remain.Location[1] = Boss_HP_Bar.Location[1] - 2;

        Boss_HP_Remain.Length = { HP_Gauge , 6 };

        // 보스 보는 방향
        ChkDirection();

        // 애니메이션 FSM
        {
            if (!M_Anim.Loop) // 루프 애니메이션이 아니면
            {
                if (ELDER_TYPE_CHK(ELDER_ANI_TYPE::ATTACK))
                {
                    if (M_Anim.Playback >=  1 && M_Anim.Playback <=  1.1f)
                    {
                        BeamStart = true;
                    }
                    if (M_Anim.End)
                    {
                        isElderAttacked = true;
                        isAttackEnd = true;
                        Swap(Elder_Idle_A);
                    }
       
                }

                if (ELDER_TYPE_CHK(ELDER_ANI_TYPE::JUMP) && M_Anim.Content == "Mon_Elder/JUMP/JumpOn" && M_Anim.End)
                {
                    isRisingUp = true;
                }

                else if (ELDER_TYPE_CHK(ELDER_ANI_TYPE::JUMP) && M_Anim.Content == "Mon_Elder/JUMP/JumpOff" && M_Anim.End)
                {
                    isJumped = true;
                    isElderAttacked = false;
                    elder_Pattern = 1;
                }

                if (ELDER_TYPE_CHK(ELDER_ANI_TYPE::DEATH) && M_Anim.Content == "Mon_Elder/DEATH/Death1" && M_Anim.End)
                {

                    Swap(Elder_Death2_A);
                }
                if (ELDER_TYPE_CHK(ELDER_ANI_TYPE::DEATH) && M_Anim.Content == "Mon_Elder/DEATH/Death2" && M_Anim.End)
                {
                    M_Anim.RGBA[0] = 1;
                    GameManager->BS->SetPlayerOriginal();
                    isDead = true;
                }
            }
            else  // 루프 애니메이션 일 경우
            {
                if ((JumpingPos_Y || FallingPos_Y) && !isGrounded && Elder_JumpOn_A.End && Elder_JumpOff_A.End)
                {
                    Swap(Elder_Jumping_A);
                }
                else
                    Swap(Elder_Idle_A);
            }
        }

        if (!isDeathAnimEnd)
        {
            //패턴
            {
                // 시작시 점프하면서 내려오게 만들고
                // 그 애니메이션이 끝나면 elder_pattern -> 1로
                // if(!isJumped && )

                if (elder_Pattern == 1 && !isElderAttacked )
                {
                    Swap(Elder_Attack_A);

                    if (!BeamStart)
                        elder_Pattern = 2;
                }

                else if (elder_Pattern == 2 && isAttackEnd && !BeamStart) // [&& 이펙트 사라졌으면] 추가
                {
                    Swap(Elder_JumpOn_A);
                    isAttackEnd = false;
                    //이펙트 =true;
                }
            }

          

            // 점프 로직
            Elder_Jump();

            // 보스 Location XY
            {
                // 점프중일때 X 선형보간
                if (!isGrounded)
                {
                    if (M_Anim.Location[0] < linearX) // 보스 X위치가 플레이어 보다 왼쪽에 있을때
                    {
                        M_Anim.Location[0] += (linearX - M_Anim.Location[0]) * 2.5f * TIME; // 선형보간? 같이 X이동
                    }

                    else if (M_Anim.Location[0] >= linearX) // 보스 X위치가 플레이어 보다 오른쪽에 있을때
                    {
                        M_Anim.Location[0] += (linearX - M_Anim.Location[0]) * 2.5f * TIME; // 선형보간? 같이 X이동
                    }
                }

                // 점프시 
                M_Anim.Location[1] = StartPos_Y + (JumpingPos_Y + FallingPos_Y);
            }

            if (BeamStart)
            {
                Elder_BEAM_Logic();
            }

            if (Hp <= 0 && Hp > -800)
            {
                M_Anim.RGBA[0] = 0;
                GameManager->BS->SetPlayerRed();
                isDeathAnimEnd = true;
                Swap(Elder_Death1_A);
                Hp = -1000;
            }
        }
    }

    else if (MONSTER_TYPE_CHK(MONSTER_TYPE::SHIELD_MON))
    {
        if (isStartExe)
        {
            Swap(Shield_Execution_A);
            isStartExe = false;
        }

        // 애니메이션 FSM
        {
            if (!M_Anim.Loop) // 루프 애니메이션이 아니면
            {
                if (SHIELD_TYPE_CHK(SHIELD_ANI_TYPE::WALK) && M_Anim.End)
                {
                    isWalkEnd = true;
                    Swap(Shield_Idle_A);
                }

                if (SHIELD_TYPE_CHK(SHIELD_ANI_TYPE::ATTACK) && M_Anim.Content == "Mon_Shield/ATTACK/Attack_On" && M_Anim.End)
                {
                    if (!isParry)
                    {
                        isAttackOff = true;
                        isAttack_Activate = true;
                        Swap(Shield_AttackOff_A);
                    }
                    else
                    {
                        isAttacking = false;
                        Swap(Shield_Parry_A);
                    }
                }

                else if (SHIELD_TYPE_CHK(SHIELD_ANI_TYPE::ATTACK) && M_Anim.Content == "Mon_Shield/ATTACK/Attack_Off" && M_Anim.End)
                {
                    isAttacking = false;
                    Swap(Shield_Idle_A);
                }

                //Parry
                if (SHIELD_TYPE_CHK(SHIELD_ANI_TYPE::PARRY))
                {
                    isParry = true;
                }
                if (SHIELD_TYPE_CHK(SHIELD_ANI_TYPE::PARRY) && M_Anim.End)
                {
                    isParry = false;
                    Swap(Shield_Idle_A);
                }


                //Death

                if (SHIELD_TYPE_CHK(SHIELD_ANI_TYPE::DEATH) && M_Anim.Content == "Mon_Shield/DEATH/Sturn")
                {
                    isExecutionOn = true;
                    if (M_Anim.End)
                    {
                        Hp = 1;
                        isExecutionOn = false;
                        isSturn = false;
                        isParry = false;
                        Swap(Shield_Idle_A);
                    }
                }

                else if (SHIELD_TYPE_CHK(SHIELD_ANI_TYPE::DEATH) && M_Anim.Content == "Mon_Shield/DEATH/Death" && M_Anim.End)
                {
                    isDead = true;
                    isDeathAnimEnd = false;
                    Swap(Shield_Idle_A);
                }


                else if (SHIELD_TYPE_CHK(SHIELD_ANI_TYPE::DEATH) && M_Anim.Content == "Mon_Shield/DEATH/Execution")
                {
                    if (M_Anim.Location[0] < GameManager->BS->GetPlayerLocation()[0])
                    {
                        LeftRight = -1;
                    }
                    else if (M_Anim.Location[0] >= GameManager->BS->GetPlayerLocation()[0])
                    {
                        LeftRight = 1;
                    }
                    if (M_Anim.End)
                        isDead = true;

                }


            }
            else  // 루프 애니메이션 일 경우
            {
                //if (walkSpdTemp)
                //{
                //    Swap(Shield_Walk_A);
                //}
                if (!walkSpd_Temp && !isAttacking && !isParry && !isDeathAnimEnd)
                    Swap(Shield_Idle_A);
            }
        }

        if (!isDeathAnimEnd)
        {
            ChkDirection();

            if (!SHIELD_TYPE_CHK(SHIELD_ANI_TYPE::IDLE) && !SHIELD_TYPE_CHK(SHIELD_ANI_TYPE::ATTACK)) // -> 나중에 ATTACK 까지
            {
                if (!isPlayerExe)
                {
                    if (FindPlayer(Shield_Alert_Col))
                    {
                        if (FindPlayer(Shield_InRange_Col))
                        {
                            isAttacking = true;
                            isAttackOn = true;
                        }
                        DirCheck();
                        walkCount_Temp = 0;
                    }
                }
            }

            if (SHIELD_TYPE_CHK(SHIELD_ANI_TYPE::IDLE) && !isParry)
            {
                attackCool += 1 * TIME;
            }


            if (!isParry)
                Attack(Shield_Walk_A);
            else
            {
                isAttacking = false;
            }
            Walk(Shield_Feet_Col, Shield_Walk_A, walkSpd, walkCount);

            if (isParry)
            {
                if (Hp <= 0 && Hp > -800)
                {
                    isSturn = true;
                    Swap(Shield_Sturn_A);
                    Hp = -1000;
                }
            }
            else
            {
                if (Hp <= 0 && Hp > -800)
                {
                    isDeathAnimEnd = true;
                    Swap(Shield_Death_A);
                    Hp = -1000;
                }
            }

        }
        //printf("Hp : %d \n", Hp);
        DrawHpBar();
    }

    else if (MONSTER_TYPE_CHK(MONSTER_TYPE::LIONHEAD))
    {
        if (!M_Anim.Loop)
        {
            if (LIONHEAD_TYPE_CHK(LIONHEAD_ANI_TYPE::WALK) && M_Anim.End)
            {
                isWalkEnd = true;
                Swap(LionHead_Idle_A);
            }
            else if (LIONHEAD_TYPE_CHK(LIONHEAD_ANI_TYPE::ATTACK))
            {
                if (M_Anim.End)
                {
                    isAttacking = false;
                    Swap(LionHead_Idle_A);
                }
            }

            else  if (LIONHEAD_TYPE_CHK(LIONHEAD_ANI_TYPE::DEATH) && M_Anim.End)
            {
                isDead = true;
                Swap(LionHead_Idle_A);
            }

        }
        else
        {
            if (!walkSpd_Temp && !isAttacking && !isDeathAnimEnd)
                Swap(LionHead_Idle_A);
        }

        if (!isDeathAnimEnd)
        {
            ChkDirection();

            // 공격
            if (LIONHEAD_TYPE_CHK(LIONHEAD_ANI_TYPE::IDLE))
            {
                attackCool += 1 * TIME;
            }

            if (FindPlayer(LionHead_Alert_Col))
            {
                if (FindPlayer(LionHead_InRange_Col) && LIONHEAD_TYPE_CHK(LIONHEAD_ANI_TYPE::WALK))
                {
                    isAttacking = true;
                    isAttackOn = true;
                }
                DirCheck();
                walkCount_Temp = 0;
            }


            if (Hp <= 0 && Hp > -800)
            {
                isDeathAnimEnd = true;
                Swap(LionHead_Death_A);
                Hp = -1000;
            }

            // 걷기
            if (!LIONHEAD_TYPE_CHK(LIONHEAD_ANI_TYPE::ATTACK))
                Walk(LionHead_Feet_Col, LionHead_Walk_A, walkSpd, walkCount);

            Attack(LionHead_Walk_A);
        }
        DrawHpBar();

        //printf("M_Anim.Location : %.lf \n", M_Anim.Location[1]);
    }

    else if (MONSTER_TYPE_CHK(MONSTER_TYPE::FOIL_MON))
    {
        if (!M_Anim.Loop)
        {
            //attack
            if (FOIL_TYPE_CHK(FOIL_ANI_TYPE::ATTACK) && M_Anim.Content == "Mon_Foil/ATTACK/Appear_Attack")
            {

                if (M_Anim.Playback > 0.7f && M_Anim.Playback <= M_Anim.Duration)
                {
                    if (M_Anim.Angle[1] == 180.0f)
                    {
                        M_Anim.Location[0] += 800 * -1 * TIME;
                    }
                    else
                    {
                        M_Anim.Location[0] += 800 * 1 * TIME;
                    }
                }
                if (M_Anim.End)
                {
                    Swap(Foil_Attack_To_Idle_A);
                }
            }
            else if (FOIL_TYPE_CHK(FOIL_ANI_TYPE::ATTACK) && M_Anim.Content == "Mon_Foil/ATTACK/Attack_To_Idle")
            {
                if (M_Anim.End)
                {
                    isAttacking = false;
                    Swap(Foil_Idle_A);
                }
            }

            // HURT
            else if (FOIL_TYPE_CHK(FOIL_ANI_TYPE::HURT) && M_Anim.End)
            {
                Swap(Foil_Idle_A);
            }

            // parry
            else if (FOIL_TYPE_CHK(FOIL_ANI_TYPE::PARRY))
            {
                isParry = true;

                if (M_Anim.End)
                {
                    isParry = false;
                    Swap(Foil_Idle_A);
                }
            }


            //death
            else if (FOIL_TYPE_CHK(FOIL_ANI_TYPE::DEATH) && M_Anim.End)
            {
                isDead = true;
                Swap(Foil_Idle_A);
            }
        }
        else
        {
            //idle
            if (!isAttacking && !isDeathAnimEnd)
                Swap(Foil_Idle_A);
        }

        if (!isDeathAnimEnd)
        {
            if (!isAttacking)
                ChkDirection();

            // 공격
            if (FOIL_TYPE_CHK(FOIL_ANI_TYPE::IDLE) && isFoilFound)
                attackCool += 1 * TIME;

            if (FindPlayer(Foil_Alert_Col))
                isFoilFound = true;

            if (Hp <= 0 && Hp > -800)
            {
                isDeathAnimEnd = true;
                Swap(Foil_Death_A);
                Hp = -1000;
            }

            Foil_Attack();

        }
        if (MONSTER_TYPE_CHK(MONSTER_TYPE::FOIL_MON))
        {
            if (!FOIL_TYPE_CHK(FOIL_ANI_TYPE::IDLE))
                DrawHpBar();
        }
    }

    if (MONSTER_TYPE_CHK(MONSTER_TYPE::FOIL_MON))
    {
        if (!FOIL_TYPE_CHK(FOIL_ANI_TYPE::IDLE))
            M_Anim.Draw();
    }
    else
    {
        M_Anim.Draw();
    }
    M_Effect_Anim.Draw();
}

void AMonster::Foil_Attack()
{
    if (attackCool >= 3 && isFoilFound)
    {
        int rnd = rand() % 2;

        if (rnd)
        {
            M_Anim.Location[0] = GameManager->BS->GetPlayerLocation()[0] + 200 * 1;

        }
        else
        {
            M_Anim.Location[0] = GameManager->BS->GetPlayerLocation()[0] + 200 * -1;
        }

        M_Anim.Location[1] = GameManager->BS->GetPlayerLocation()[1] + 10 * -1;

        isAttacking = true;
        isAttackOn = true;
        DirCheck();

        attackCool = 0;
    }

    if (isAttackOn)
    {
        DirCheck();
        ChkDirection();
        Swap(Foil_Appear_Attack_A);
        isAttackOn = false;
    }
}


void AMonster::Attack(Animation& walk_A)
{
    if (attackCool >= 2)
    {
        WalkSetUp(walk_A);
        attackCool = 0;
    }

    if (MONSTER_TYPE_CHK(MONSTER_TYPE::SHIELD_MON))
    {
        if (isAttackOn)
        {
            Swap(Shield_AttackOn_A);
            isAttackOn = false;
        }

        if (isAttackOff)
        {
            isAttack_Activate = false;
            Swap(Shield_AttackOff_A);
            isAttackOff = false;
        }
    }

    else if (MONSTER_TYPE_CHK(MONSTER_TYPE::LIONHEAD))
    {
        if (isAttackOn)
        {
            Swap(LionHead_Attack_A);
            isAttackOn = false;
        }
    }
}

bool AMonster::FindPlayer(Image& InRangeCol)
{
    if (PR_Col_Chk(PLAYER_XPOS, PLAYER_YPOS, InRangeCol, InRangeCol.Angle[2]))
        return true;
    else
        return false;
}


void AMonster::WalkSetUp(Animation& walk_A)
{
    LeftRight *= -1;
    isWalkEnd = false;
    walkSpd_Temp = walkSpd;
    Swap(walk_A);

    walkCount_Temp = 1;
    walkCool = 0;
}

void AMonster::Walk(Image& feet_Col, Animation& walk_A, int& walkSpd, int& walkCount)
{
    if (isAttacking)
    {
        isGrounded = false;
        walkSpd_Temp = 0;
    }

    else
    {
        for (int i = 0; i < non_Inter.Floor_Col.size(); i++)
        {
            if (RR_Col_Chk(feet_Col, feet_Col.Angle[2], non_Inter.Floor_Col[i], non_Inter.Floor_Col[i].Angle[2])) // 땅에 있으면
            {
                isGrounded = true;
                FloorIndex = i;
                gravTime = 0;
                FallingPos_Y = 0;
            }
        }
    }

    if (isGrounded)
    {
        // 땅안쪽에 있으면
        if ((feet_Col.Location[0] - feet_Col.Length[0] / 2) + 5 <= (non_Inter.Floor_Col[FloorIndex].Location[0] + non_Inter.Floor_Col[FloorIndex].Length[0] / 2)     // 땅의 오른쪽끝
            && (feet_Col.Location[0] + feet_Col.Length[0] / 2) - 5 >= (non_Inter.Floor_Col[FloorIndex].Location[0] - non_Inter.Floor_Col[FloorIndex].Length[0] / 2)) // 땅의 왼쪽끝
        {
            if (isWalkEnd)
            {
                if (walkCount_Temp < walkCount && walkSpd_Temp)
                {
                    Swap(walk_A);

                    ++walkCount_Temp;
                    isWalkEnd = false;
                }
                else
                {
                    walkSpd_Temp = 0;
                    walkCool += 1 * TIME;
                }
            }

            if (walkCool >= 2)
            {
                WalkSetUp(walk_A);
            }
        }
        else
        {
            if (!walkCool)
                isWalkEnd = true;

            if (isWalkEnd)
            {
                walkSpd_Temp = 0;
                walkCool += 1 * TIME;
            }

            if (walkCool >= 2)
            {
                WalkSetUp(walk_A);
            }
        }

        M_Anim.Location[0] += LeftRight * walkSpd_Temp * TIME;
        M_Anim.Location[1] = non_Inter.Floor_Col[FloorIndex].Location[1] + (non_Inter.Floor_Col[FloorIndex].Length[1] + M_Anim.Length[1]) / 2; // 바닥에 서있게 하기
    }

    //else // 혹시 떨어지면
    //{
    //    FallingPos_Y = -(gravTime * gravTime - 0 * gravTime);
    //    gravTime += 10 * TIME;
    //}
}

void AMonster::End()
{
    M_Anim.Location = { 0,0 };
}

#pragma region Elder_Patterns


void AMonster::DirCheck()
{
    if (M_Anim.Location[0] < GameManager->BS->GetPlayerLocation()[0])
    {
        LeftRight = 1;
    }
    else if (M_Anim.Location[0] >= GameManager->BS->GetPlayerLocation()[0])
    {
        LeftRight = -1;
    }
} // ForceInline??

void AMonster::Jump_Setup()
{
    StartPos_Y = M_Anim.Location[1];
    JumpingPos_Y = 0;
    FallingPos_Y = 0;

    jumpingTime = 0;
    gravTime = 0;

    jumpPower = 40;     // 점프할때만 점프파워 초기화
}

void AMonster::Elder_Jump()
{
    // 최대높이에 도달함과 동시에 Boss가 올라가는 상태면 
    if (jumpingTime >= jumpPower / 2 && isRisingUp)
    {
        isRisingUp = false;
    }

    // 점프로 올라가는 상태
    if (isRisingUp)
    {
        isGrounded = false;

        flying(jumpPower, 35); // 일정 속도로 이차함수를 통해 중력받기
        DirCheck();            // 플레이어 Boss위치로부터 좌우구분
        linearX = PLAYER_XPOS; // 플레이어까지 보간되도록
        Swap(Elder_Jumping_A);
    }
    else
    {
        for (int i = 0; i < non_Inter.Floor_Col.size(); i++)
        {
            // Feet_Col_바닥과 Floor 충돌체크
            if (PR_Col_Chk(Elder_Feet_Col.Location[0], Elder_Feet_Col.Location[1] + Elder_Feet_Col.Length[1] / 2, non_Inter.Floor_Col[i], non_Inter.Floor_Col[i].Angle[2]))
            {
                isGrounded = true;
                Jump_Setup();

                if (isJumped)
                {
                    E_JumpCool += 1 * TIME;
                    if (E_JumpCool >= 1)
                    {
                      
                        E_JumpCool = 0;
                        isJumped = false;
                        //이펙트 =false;
                    }
                }
            }
        }

        if (!isGrounded)
        {
            if (M_Anim.Location[1] - PLAYER_YPOS <= 200)
            {
                Swap(Elder_JumpOff_A);
            }
            else if (M_Anim.Location[1] - PLAYER_YPOS >= 450)
            {
                linearX = PLAYER_XPOS;
            }

            DirCheck();

            FallingPos_Y = -(gravTime * gravTime - 0 * gravTime);
            gravTime += 35 * TIME;
        }
    }
}

void AMonster::Elder_Attack()
{

}

void AMonster::DeadLogic(Animation Death_Anim)
{
    Swap(Death_Anim);
}

void AMonster::ADebugCollider()
{
    Release = false;
}

void AMonster::ADrawCollider()
{
    Release = true;
}

#pragma endregion




void AMonster::E_Swap(Animation anim) // 애니메이션 스왑할때
{
    if (M_Effect_Anim.Content == anim.Content) return;

    M_Effect_Anim.Content = anim.Content;
    M_Effect_Anim.Length = anim.Length;
    M_Effect_Anim.Playback = 0.0f;
    M_Effect_Anim.End = false;
    M_Effect_Anim.Loop = anim.Loop;
    M_Effect_Anim.Duration = anim.Duration;
}

void AMonster::Elder_E_Swap(Animation anim , int index)
{
    if (Elder_Effect_Anim[index].Content == anim.Content) return;

    Elder_Effect_Anim[index].Content = anim.Content;
    Elder_Effect_Anim[index].Length = anim.Length;
    Elder_Effect_Anim[index].Playback = 0.0f;
    Elder_Effect_Anim[index].End = false;
    Elder_Effect_Anim[index].Loop = anim.Loop;
    Elder_Effect_Anim[index].Duration = anim.Duration;
}


void AMonster::Swap(Animation anim) // 애니메이션 스왑할때
{
    if (M_Anim.Content == anim.Content) return;

    M_Anim.Content = anim.Content;
    M_Anim.Length = anim.Length;
    M_Anim.Playback = 0.0f;
    M_Anim.End = false;
    M_Anim.Loop = anim.Loop;
    M_Anim.Duration = anim.Duration;

    SetNowAnim(*this, M_Anim);
}


