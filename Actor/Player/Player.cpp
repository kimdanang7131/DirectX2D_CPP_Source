#include "stdafx.h"
#include "Player.h"
#include "Component/InputComponent.h"
#include <io.h>

using namespace Collision;

#pragma region Define문 

#define GetNowScene()          GameManager->GetNowScene()

#define non_Inter              GetNowScene()->noninter_Cols
#define     Inter              GetNowScene()->inter_Cols


#define PlayerOnRightCollision non_Inter.Floor_Col[right_index].Location[1] + (P_Anim.Length[1] + non_Inter.Floor_Col[right_index].Length[1]) / 2
#define Feet_Bottom            Feet_Col.Location[1]  - Feet_Col.Length[1] / 2
#define TIME                   Time::Get::Delta()
#define RIGHT                  LeftRight ==  1
#define LEFT                   LeftRight == -1

#define M_PI 3.14159265358979323846

#define STOP         !isSliding && !isParryOn && !isAttacking && !isParryAttack  && !isCrouchAttack && !isPushBack && !P_TYPE_CHK(P_ANI_TYPE::GETHIT) && !isExecution && !isConsuming && !isPraying && !isAttackCombo && !isDeathAnimOn  && P_Anim.RGBA[0]!=0


#pragma endregion

APlayer::APlayer()
{
    InputComponent = new CInputComponent(this);

#pragma region Player 기타설정

    Feet_Col.Content = "P_Col/FeetCol";
    Feet_Col.Length = { 30,5 };

    Hitbox_Col.Content = "P_Col/HitboxCol";
    Hitbox_Col.Length = { 23,30 };

    Angle_Col.Content = "P_Col/AngleCol";
    Angle_Col.Length = { 7,12 };

    Wall_Col.Content = "P_Col/WallCol";
    Wall_Col.Length = { 5,15 };

    Attack_Col.Content = "P_Col/AttackCol";
    Attack_Col.Length = { 30,30 };

#pragma endregion 

#pragma region 기본 상태
    Idle_A.Content = "PLAYER/IDLE/Idle";
    Idle_A.Length = { DEFAULTSIZE, DEFAULTSIZE };
    Idle_A.Loop = true;
    Idle_A.Duration = 0.8f;

    Effect_Idle_A.Content = "HITEFFECT/Effect_Idle";
    Effect_Idle_A.Length = { DEFAULTSIZE, DEFAULTSIZE };
    Effect_Idle_A.Loop = true;
    Effect_Idle_A.Duration = 1;


    UpWard_Attack_A.Content = "PLAYER/JUMP/JumpingUpwardAttack";
    UpWard_Attack_A.Length = { DEFAULTSIZE , DEFAULTSIZE };
    UpWard_Attack_A.Loop = false;
    UpWard_Attack_A.Duration = 0.5f;


    Upward_Eff_A.Content = "HITEFFECT/UpwardEffect";
    Upward_Eff_A.Length = { DEFAULTSIZE, DEFAULTSIZE + 50 };
    Upward_Eff_A.Loop = false;
    Upward_Eff_A.Duration = 0.5f;


#pragma endregion

#pragma region 달리기
    Running_A.Content = "PLAYER/RUN/Running";
    Running_A.Length = { DEFAULTSIZE , DEFAULTSIZE };
    Running_A.Loop = true;
    Running_A.Duration = 0.6f;

    // 왼오 달리기
    AxisData moveright[2];
    moveright[0] = { 'A' ,-1 ,&APlayer::MoveRight };
    moveright[1] = { 'D' , 1 ,&APlayer::MoveRight };
    InputComponent->BindAxis(moveright, 2);
#pragma endregion

#pragma region 슬라이딩

    Dodge_A.Content = "PLAYER/DODGE/Dodge";
    Dodge_A.Length = { DEFAULTSIZE + 40, DEFAULTSIZE };
    Dodge_A.Loop = false;
    Dodge_A.Duration = 0.6f;

    InputComponent->BindAction(VK_SHIFT, ActionType::PRESSED, &APlayer::Dodge);
#pragma endregion

#pragma region 점프
    Jump_A.Content = "PLAYER/JUMP/Jump";
    Jump_A.Length = { DEFAULTSIZE , DEFAULTSIZE };
    Jump_A.Loop = false;
    Jump_A.Duration = 0.6f;

    Jumping_A.Content = "PLAYER/JUMP/Jumping";
    Jumping_A.Length = { DEFAULTSIZE , DEFAULTSIZE };
    Jumping_A.Loop = true;
    Jumping_A.Duration = 0.9f;

    Jump_Forward_A.Content = "PLAYER/JUMP/Jump_Forward";
    Jump_Forward_A.Length = { DEFAULTSIZE , DEFAULTSIZE };
    Jump_Forward_A.Loop = false;
    Jump_Forward_A.Duration = 0.8f;

    Jumping_Forward_A.Content = "PLAYER/JUMP/Jumping_Forward";
    Jumping_Forward_A.Length = { DEFAULTSIZE , DEFAULTSIZE };
    Jumping_Forward_A.Loop = true;
    Jumping_Forward_A.Duration = 0.9f;

    Jumping_Attack_A.Content = "PLAYER/JUMP/JumpingAttack";
    Jumping_Attack_A.Length = { DEFAULTSIZE + 40 , DEFAULTSIZE };
    Jumping_Attack_A.Loop = false;
    Jumping_Attack_A.Duration = 0.3f;

    Jumping_Upward_Attack_A.Content = "PLAYER/JUMP/JumpingUpwardAttack";
    Jumping_Upward_Attack_A.Length = { DEFAULTSIZE , DEFAULTSIZE };
    Jumping_Upward_Attack_A.Loop = false;
    Jumping_Upward_Attack_A.Duration = 0.5f;



    JumpingEff_A.Content = "HITEFFECT/JumpingEffect";
    JumpingEff_A.Length = { DEFAULTSIZE, DEFAULTSIZE };
    JumpingEff_A.Loop = false;
    JumpingEff_A.Duration = 0.4f;

    JumpingUpwardEff_A.Content = "HITEFFECT/UpwardEffect";
    JumpingUpwardEff_A.Length = { DEFAULTSIZE, DEFAULTSIZE + 50 };
    JumpingUpwardEff_A.Loop = false;
    JumpingUpwardEff_A.Duration = 0.4f;



    //점프키
    InputComponent->BindAction(VK_SPACE, ActionType::PRESSED, &APlayer::Jump);
#pragma endregion

#pragma region 벽매달
    Jump_Hanging_A.Content = "PLAYER/HANG/Jump_Hanging";
    Jump_Hanging_A.Length = { DEFAULTSIZE + 40, DEFAULTSIZE };
    Jump_Hanging_A.Loop = false;
    Jump_Hanging_A.Duration = 1;

    Hang_Ground_A.Content = "PLAYER/HANG/Hang_Ground";
    Hang_Ground_A.Length = { DEFAULTSIZE  , DEFAULTSIZE };
    Hang_Ground_A.Loop = false;
    Hang_Ground_A.Duration = 1;
#pragma endregion 

#pragma region 공격 
    Attack_A.Content = "PLAYER/ATTACK/hitcombo1";
    Attack_A.Length = { DEFAULTSIZE + 200, DEFAULTSIZE };
    Attack_A.Loop = false;
    Attack_A.Duration = 0.4f;

    Attack2_A.Content = "PLAYER/ATTACK/hitcombo2";
    Attack2_A.Length = { DEFAULTSIZE + 200, DEFAULTSIZE };
    Attack2_A.Loop = false;
    Attack2_A.Duration = 0.4f;

    Attack3_A.Content = "PLAYER/ATTACK/hitcombo3";
    Attack3_A.Length = { DEFAULTSIZE + 200, DEFAULTSIZE };
    Attack3_A.Loop = false;
    Attack3_A.Duration = 0.5f;

    SlashEff_A.Content = "HITEFFECT/SlashEffect1";
    SlashEff_A.Length = { 160, DEFAULTSIZE };
    SlashEff_A.Loop = false;
    SlashEff_A.Duration = 0.3f;

    SlashEff2_A.Content = "HITEFFECT/SlashEffect2";
    SlashEff2_A.Length = { 160, DEFAULTSIZE };
    SlashEff2_A.Loop = false;
    SlashEff2_A.Duration = 0.3f;

    SlashEff3_A.Content = "HITEFFECT/SlashEffect3";
    SlashEff3_A.Length = { 160, DEFAULTSIZE };
    SlashEff3_A.Loop = false;
    SlashEff3_A.Duration = 0.5f;
#pragma endregion 

#pragma region 사다리

    Laddering_A.Content = "PLAYER/LADDER/Laddering";
    Laddering_A.Length = { DEFAULTSIZE,DEFAULTSIZE };
    Laddering_A.Loop = true;
    Laddering_A.Duration = 0.7f;


    AxisData ladderUpDown[2];
    ladderUpDown[0] = { 'W' ,  1 ,&APlayer::LadderLogic };
    ladderUpDown[1] = { 'S' , -1 ,&APlayer::LadderLogic };
    InputComponent->BindAxis(ladderUpDown, 2);

    //Ladder_Sliding_A.Content = "LADDER/Laddering";
#pragma endregion 

#pragma region 앉기

    Crouching_A.Content = "PLAYER/CROUCH/Crouching";
    Crouching_A.Length = { DEFAULTSIZE + 20 ,DEFAULTSIZE };
    Crouching_A.Loop = true;
    Crouching_A.Duration = 0.5f;


    Crouching_Attack_A.Content = "PLAYER/CROUCH/Crouch_Attack";
    Crouching_Attack_A.Length = { DEFAULTSIZE  ,DEFAULTSIZE };
    Crouching_Attack_A.Loop = false;
    Crouching_Attack_A.Duration = 0.5f;

    Crouch_Eff_A.Content = "HITEFFECT/CrouchEffect";
    Crouch_Eff_A.Length = { DEFAULTSIZE + 10, DEFAULTSIZE - 50 };
    Crouch_Eff_A.Loop = false;
    Crouch_Eff_A.Duration = 0.5f;

#pragma endregion

#pragma region 패링

    Parry_A.Content = "PLAYER/PARRY/Parry";
    Parry_A.Length = { DEFAULTSIZE , DEFAULTSIZE };
    Parry_A.Loop = false;
    Parry_A.Duration = 0.4f;

    Parry_Attack_A.Content = "PLAYER/PARRY/ParryCounter";
    Parry_Attack_A.Length = { 300 , 110 };
    Parry_Attack_A.Loop = false;
    Parry_Attack_A.Duration = 1;


    Guard_Slide_A.Content = "PLAYER/PARRY/GuardSlide";
    Guard_Slide_A.Length = { 100, 100 };
    Guard_Slide_A.Loop = false;
    Guard_Slide_A.Duration = 0.5f;


    Guard_Eff_A.Content = "HITEFFECT/GuardEffect";
    Guard_Eff_A.Length = { 140 , 100 };
    Guard_Eff_A.Loop = false;
    Guard_Eff_A.Duration = 0.5f;

    InputComponent->BindAction('J', ActionType::PRESSED, &APlayer::Parry);


#pragma endregion 

#pragma region 맞았을때

    Hit_PushBack_A.Content = "PLAYER/GETHIT/push_back";
    Hit_PushBack_A.Length = { DEFAULTSIZE , DEFAULTSIZE };
    Hit_PushBack_A.Loop = false;
    Hit_PushBack_A.Duration = 0.6f;

#pragma endregion 

#pragma region 포션컨슘

    Potion_Drink_A.Content = "PLAYER/POTION/Health_Consume";
    Potion_Drink_A.Length = { DEFAULTSIZE , DEFAULTSIZE };
    Potion_Drink_A.Loop = false;
    Potion_Drink_A.Duration = 1.5f;

    Potion_Aura_A.Content = "HITEFFECT/Health_Aura";
    Potion_Aura_A.Length = { DEFAULTSIZE , DEFAULTSIZE + 50 };
    Potion_Aura_A.Loop = false;
    Potion_Aura_A.Duration = 1.5f;

#pragma endregion 

#pragma region 기도

    Pray_A.Content = "PLAYER/KNEEL/Kneel_Standup";
    Pray_A.Length = { DEFAULTSIZE , DEFAULTSIZE };
    Pray_A.Loop = false;
    Pray_A.Duration = 2.3f;




#pragma endregion

#pragma region 죽음

    Death_A.Content = "PLAYER/DEATH/Death";
    Death_A.Length = { DEFAULTSIZE + 30 , DEFAULTSIZE };
    Death_A.Loop = false;
    Death_A.Duration = 2.3f;

#pragma endregion 

    Getting_Up_A.Content = "PLAYER/GettingUp";
    Getting_Up_A.Length = { DEFAULTSIZE  , DEFAULTSIZE };
    Getting_Up_A.Loop = false;
    Getting_Up_A.Duration = 2.3f;

    Start_A.Content = "PLAYER/Start";
    Start_A.Length = { DEFAULTSIZE  , DEFAULTSIZE };
    Start_A.Loop = true;
    Start_A.Duration = 1;

    Player_HP.Content = "UI/PlayerHP";
    Player_HP.Length = { 300,60 };

    Player_HP_Remain.Content = "UI/PlayerHP_Remain";
    Player_HP_Remain.Length = { 2,6 };

    HP_Potion_Empty.Content = "UI/HP_Potion_Empty";
    HP_Potion_Empty.Length = { 14,22 };

    HP_Potion_Full.Content = "UI/HP_Potion_Full";
    HP_Potion_Full.Length = { 14,22 };

    PlayerSoul.Content = "UI/PlayerSoul";
    PlayerSoul.Length = { 87, 46 };

    KB_E.Content = "UI/E";
    KB_E.Length = { 17,18 };

    KB_F.Content = "UI/F";
    KB_F.Length = { 17,18 };


    Text_Soul_Amount = { "  0", {"Blasphemous" , 30} , {173,155,57} ,{1175,60} };



    full_HP = 200;
    Hp = 200;

    Health_Bottles = 5;
    max_Bottles = 5;


    soul = 0;
    attkDmg = 50;
    attkcom3_Dmg = 100;
    Jumping_Attk_Dmg = 50;
    Crouch_Attk_Dmg = 50;
    Parry_Counter_Dmg = 150;

    P_Anim = Start_A;           //  현재 애니메이션 설정
    P_Effect_Anim = Effect_Idle_A;
    SetActorTransform(P_Anim); // 현재 애니메이션 location 설정    
}

namespace
{

}


void APlayer::ChangeScene_Setup()
{
    if (isReviving)
    {
        P_Anim.Location = Revive_Location;
        angle_index = 0;
        right_index = 0;
        SetActorTransform(P_Anim); // parrallax때문에 무조건 해줘야됨

        //Animation Revive  이후
        full_HP = 200;
        Hp = 200;
        Health_Bottles = 5;
        max_Bottles = 5;
        soul = 0;
        isPushBack = false;

        isAtBossStage = false;
        isReviving = false;
    }
    else
    {
        P_Anim.Location = GetNowScene()->Scenes_StartPos;
        angle_index = 0;
        right_index = 0;
        SetActorTransform(P_Anim); // parrallax때문에 무조건 해줘야됨
    }
}
void APlayer::Start() // 문 들어갈때 SetActor로 문들어간 위치 저장 하면 될듯
{
    ChangeScene_Setup();
}

void APlayer::Jump_Setup()
{
    StartPos_Y = P_Anim.Location[1];
    JumpingPos_Y = 0;
    FallingPos_Y = 0;

    jumpingTime = 0;
    gravTime = 0;

    jumpPower = 17;     // 점프할때만 점프파워 초기화

    isFalling = false; // 떨어지는중 false
}
void APlayer::Jump() // 정리 후 아래로
{
    if (isGrounded || isOnLadder && !P_TYPE_CHK(P_ANI_TYPE::DEATH))
    {
        Jump_Setup();
        isRisingUp = true;
        isGrounded = false; // 점프했으니 Grounded = false;

        isOnLadder = false; // 사다리에서 점프가능

        // 점프 루트
        if (Direction[0])
        {
            Swap(Jump_Forward_A);
        }
        else if (!Direction[0])
        {
            Swap(Jump_A);
        }
    }
}

void APlayer::Jump_Down_Setup()
{
    StartPos_Y = P_Anim.Location[1];
    JumpingPos_Y = 0;
    FallingPos_Y = 0;

    jumpingTime = 0;
    gravTime = 0;

    jumpPower = 0; // 아래 점프므로 초기화

    isRisingUp = false;  // 점프 시작중 true
    isFalling = false; // 떨어지는중 false
    isGrounded = false; // 점프했으니 Grounded = false;
    isCrouching = false; // 안해도 되지만 혹시 모르니 false

    isOnJumpDownCol = true; // 직각일때만 아래 점프 할 수 있게 Check -> 직각일때만 JumpDown()함수가 실행되므로 무조건 true됨
}
void APlayer::JumpDown()
{
    Jump_Down_Setup();
}

void APlayer::Flight_Spd_Setup()
{
    P_Anim.Location[0] += Direction[0] * (220 + Dodge_Spd) * TIME;
    P_Anim.Location[1] = StartPos_Y + (JumpingPos_Y + FallingPos_Y);
}

void APlayer::HangLogic_SetUp()
{
    StartPos_Y = P_Anim.Location[1];
    JumpingPos_Y = 0;
    FallingPos_Y = 0;

    jumpingTime = 0;
    gravTime = 0;

    Direction[0] = 0;
    LeftRight = 0;

    isFalling = true;
    isHanging = false;
}


void APlayer::Dodge_After_Setup()
{
    // 슬라이딩 하고 초기화
    isSliding = false;
    Dodge_Spd = 0;

    Direction[0] = 0;
    LeftRight = 0;
    // 키입력 시작
}

void APlayer::Dodge()
{
    if (LeftRight && isGrounded)
    {
        isSliding = true;
        Dodge_Spd = 100;
        Swap(Dodge_A);
    }
}

// 정리해야됨
void APlayer::Attack()
{
    if (Input::Get::Key::Down('K') && !P_TYPE_CHK(P_ANI_TYPE::JUMP) && !P_TYPE_CHK(P_ANI_TYPE::DODGE) && !P_TYPE_CHK(P_ANI_TYPE::CROUCH) && !P_TYPE_CHK(P_ANI_TYPE::GETHIT) && !P_TYPE_CHK(P_ANI_TYPE::DEATH) && P_Anim.RGBA[0] != 0) // 더 추가
    {
        if (!isAttackCombo)
        {

            if (!isButtonInputed)
            {
                GameManager->BS->isAttackEffectOn = false;
                isButtonInputed = true;
            }
            Direction[0] = 0;
            LeftRight = 0;
            isAttacking = true;
            E_Swap(Effect_Idle_A);
            E_Swap(SlashEff_A);
            Swap(Attack_A);
        }
    }
}

void APlayer::LadderLogic(float axis)
{
    if (isOnLadder)
    {
        Swap(Laddering_A);

        if (axis > 0.0f)
        {
            StartPos_Y += axis * 100 * TIME;
        }
        else if (axis < 0.0f)
        {
            StartPos_Y += axis * 100 * TIME;
        }
        else if (!axis)
        {
            return;
        }
    }
}

void APlayer::Crouch()
{
    if (Input::Get::Key::Press('S') && isGrounded && !isOnLadder && P_Anim.RGBA[0] != 0)
    {
        isCrouching = true;

        if (Input::Get::Key::Down(VK_SPACE) && isCrouching)
        {
            isGrounded = false;
            Jump();
        }

        if (Input::Get::Key::Down('K'))
        {
            isCrouchAttack = true;
            E_Swap(Crouch_Eff_A);
            Swap(Crouching_Attack_A);
        }
    }
    else
        isCrouching = false;
}


void APlayer::HangOnLedge()
{
    if (isHangOn)
    {
        Swap(Jump_Hanging_A);
    }
}

void APlayer::HangLogic()
{
    if (!isGrounded)
    {
        for (int i = 0; i < non_Inter.Hang_Col.size(); i++)
        {
            if (RR_Col_Chk(Wall_Col, Wall_Col.Angle[2], non_Inter.Hang_Col[i], non_Inter.Hang_Col[i].Angle[2]))
            {
                HangIndex = i;
                for (int j = 0; j < non_Inter.Floor_Col.size(); j++)
                {
                    if (RR_Col_Chk(non_Inter.Hang_Col[HangIndex], non_Inter.Hang_Col[HangIndex].Angle[2], non_Inter.Floor_Col[j], non_Inter.Floor_Col[j].Angle[2]))
                    {
                        HFIndex = j;

                        if (P_Anim.Location[0] < non_Inter.Floor_Col[HFIndex].Location[0]) // 플레이어가 Floor보다 왼쪽에 있을때
                        {
                            if (RIGHT)
                            {
                                isHangOn = true;
                                isHanging = true;

                                isFalling = false;
                                gravTime = 0;
                                FallingPos_Y = 0;
                            }

                        }
                        else // 플레이어가 Floor보다 오른쪽에 있을때
                        {
                            if (LEFT)
                            {
                                isHangOn = true;
                                isHanging = true;

                                isFalling = false;
                                gravTime = 0;
                                FallingPos_Y = 0;
                            }
                        }
                    }
                }
            }
        }

        if (isHanging)
        {
            if (P_Anim.Location[0] < non_Inter.Floor_Col[HFIndex].Location[0]) // 플레이어가 오른쪽으로 뛰거나 떨어졌을때
            {
                P_Anim.Location[0] = non_Inter.Floor_Col[HFIndex].Location[0] - (non_Inter.Floor_Col[HFIndex].Length[0] / 2);
                P_Anim.Location[1] = non_Inter.Floor_Col[HFIndex].Location[1] - 5;
                StartPos_Y = P_Anim.Location[1];
            }
            else // 플레이어가 왼쪽으로 뛰거나 떨어졌을때
            {
                P_Anim.Location[0] = non_Inter.Floor_Col[HFIndex].Location[0] + (non_Inter.Floor_Col[HFIndex].Length[0] / 2);
                P_Anim.Location[1] = non_Inter.Floor_Col[HFIndex].Location[1] - 5;
                StartPos_Y = P_Anim.Location[1];
            }

            if (Input::Get::Key::Down('W') && !isHangOn)
            {
                HangLogic_SetUp();
                isFalling = false;
                isHangOnGround = true;
                Swap(Hang_Ground_A);
            }
            else if (Input::Get::Key::Down('S') && !isHangOn)
            {
                HangLogic_SetUp();

                Swap(Idle_A);
            }
        }
    }
}

void APlayer::Parry()
{
    if (!P_TYPE_CHK(P_ANI_TYPE::JUMP) && !P_TYPE_CHK(P_ANI_TYPE::DODGE) && !P_TYPE_CHK(P_ANI_TYPE::CROUCH) && !P_TYPE_CHK(P_ANI_TYPE::DEATH) && P_Anim.RGBA[0] != 0) // 더 추가
    {
        Direction[0] = 0;
        LeftRight = 0;
        isParryOn = true;
        Swap(Parry_A);
    }
}

void APlayer::ParryAttack()
{
    Swap(Parry_Attack_A);
}

void APlayer::Update()
{
    SetActorTransform(P_Anim);
    SetEffectLocation();


    //printf(" [ X: %.lf , Y : %.lf ] \n", P_Anim.Location[0], P_Anim.Location[1]);  //-> Scene추가할때마다 시작위치 확인용

    if (!isGettingUp)
    {
        KB_F.Location = P_Anim.Location;
        KB_F.Location[1] = P_Anim.Location[1] + 30;

        KB_F.Draw();
    }

    if (Input::Get::Key::Down('F') && !isGettingUp)
    {

        Swap(Getting_Up_A);
        isGettingUp = true;
    }

#pragma region 애니메이션 FSM
    //if (P_Effect_Anim.Loop)
    //{
    //    Swap(Effect_Idle_A);
    //}
    // 애니메이션 스왑 -> 정리
    if (!P_Anim.Loop) // 루프 애니메이션이 아니면
    {
        if (Hp <= 0 && Hp > -800)
        {
            isDeathAnimOn = true;
            Swap(Death_A);
            Hp = -1000;
        }

        if (P_Anim.Content == "PLAYER/GettingUp" && P_Anim.End)
        {
            Swap(Idle_A);
            GameStart = true;
        }

#pragma region Dodge

        if (P_TYPE_CHK(P_ANI_TYPE::DODGE) && P_Anim.End)
        {
            Dodge_After_Setup();
            Swap(Idle_A);
        }
        else if (P_TYPE_CHK(P_ANI_TYPE::DODGE) && !isGrounded && isFalling && FallingPos_Y < -3)
        {
            Dodge_After_Setup();
            Swap(Idle_A);
        }
#pragma endregion


#pragma region Jump
        if (P_TYPE_CHK(P_ANI_TYPE::JUMP) && P_Anim.Content == "PLAYER/JUMP/Jump" && P_Anim.End)
        {
            Swap(Idle_A);
        }
        if (P_TYPE_CHK(P_ANI_TYPE::JUMP) && P_Anim.Content == "PLAYER/JUMP/Jump_Forward" && P_Anim.End)
        {
            Swap(Idle_A);
        }
        else if (P_TYPE_CHK(P_ANI_TYPE::JUMP) && isGrounded)
        {
            isJumpUpwardAttack = false;
            isJumpingAttack = false;         
            E_Swap(Effect_Idle_A);
            Swap(Idle_A);
        }

        if(P_Anim.Content == "PLAYER/JUMP/JumpingUpwardAttack"  && P_Anim.End)
        {
            GameManager->BS->isAttackEffectOn = false;
            isJumpUpwardAttack = false;

            Swap(Idle_A);
            E_Swap(Effect_Idle_A);
        }
        if (P_Anim.Content == "PLAYER/JUMP/JumpingAttack" && P_Anim.End)
        {
            GameManager->BS->isAttackEffectOn = false;
            isJumpingAttack = false;
            Swap(Idle_A);
            E_Swap(Effect_Idle_A);
        }


#pragma endregion

#pragma region Hang
        if (P_TYPE_CHK(P_ANI_TYPE::HANG) && P_Anim.Content == "PLAYER/HANG/Jump_Hanging" && P_Anim.End)
        {
            isHangOn = false;
            isHanging = true;
        }

        else if (P_TYPE_CHK(P_ANI_TYPE::HANG) && P_Anim.Content == "PLAYER/HANG/Hang_Ground")
        {
            if (Feet_Bottom >= non_Inter.Floor_Col[HFIndex].Location[1] + non_Inter.Floor_Col[HFIndex].Length[1] / 2 || P_Anim.End)
            {
                isHangOnGround = false;
                Jump_Setup();
                isFalling = true;
                Swap(Idle_A);
            }
            else
            {
                P_Anim.Location[1] += 110 * TIME;
            }
        }
#pragma endregion

#pragma region Parry
        else if (P_TYPE_CHK(P_ANI_TYPE::PARRY) && P_Anim.Content == "PLAYER/PARRY/Parry")
        {
            if (P_Anim.End)
            {
                isParryOn = false;
                Swap(Idle_A);
            }
            if (isParryAttack)
            {
                isParryOn = false;
            }
            if (isGuardSlide)
            {
                Swap(Guard_Slide_A);
                E_Swap(Guard_Eff_A);
            }
        }

        else if ((P_TYPE_CHK(P_ANI_TYPE::PARRY) && P_Anim.Content == "PLAYER/PARRY/ParryCounter" && P_Anim.End))
        {
            isParryOn = false;
            isParryAttack = false;

            isAttackCombo = false;
            isAttacking = false;

            isPushBack = false;
            GameManager->BS->isAttackEffectOn = false;


            Swap(Idle_A);
        }

        else if ((P_TYPE_CHK(P_ANI_TYPE::PARRY) && P_Anim.Content == "PLAYER/PARRY/GuardSlide"))
        {
            //printf("a\n");
            if (GameManager->BS->Mon_LeftRight == 1)
                P_Anim.Location[0] -= 300 * 1 * TIME;
            else if (GameManager->BS->Mon_LeftRight == -1)
                P_Anim.Location[0] -= 300 * -1 * TIME;

            if (P_Anim.End)
            {
                isParryOn = false;
                isGuardSlide = false;
                Swap(Idle_A);
                E_Swap(Effect_Idle_A);
            }
        }
#pragma endregion

#pragma region Attack
        if ((P_TYPE_CHK(P_ANI_TYPE::ATTACK) && P_Anim.Content == "PLAYER/ATTACK/hitcombo1"))
        {

            if (isButtonInputed)
            {
                if (Input::Get::Key::Down('K'))
                {
                    GameManager->BS->isAttackEffectOn = false;
                    isAttackCombo = true;
                    isButtonInputed = false;
                }
            }


            if (P_Anim.End && isAttackCombo)
            {
                isAttackCombo = false;
                isButtonInputed = true;
                Swap(Attack2_A);
            }
            else if (P_Anim.End && !isAttackCombo)
            {
                GameManager->BS->isAttackEffectOn = false;

                isAttacking = false;
                Swap(Idle_A);
            }
        }
        else if ((P_TYPE_CHK(P_ANI_TYPE::ATTACK) && P_Anim.Content == "PLAYER/ATTACK/hitcombo2"))
        {
            E_Swap(SlashEff2_A);

            if (isButtonInputed)
            {
                if (Input::Get::Key::Down('K'))
                {
                    GameManager->BS->isAttackEffectOn = false;
                    isAttackCombo = true;
                    isButtonInputed = false;
                }
            }

            if (P_Anim.End && isAttackCombo)
            {
                isAttackCombo = true;
                isButtonInputed = true;
                Swap(Attack3_A);
            }

            else if (P_Anim.End && !isAttackCombo)
            {
                GameManager->BS->isAttackEffectOn = false;

                isAttacking = false;
                Swap(Idle_A);
            }
        }

        else if ((P_TYPE_CHK(P_ANI_TYPE::ATTACK) && P_Anim.Content == "PLAYER/ATTACK/hitcombo3"))
        {
            E_Swap(SlashEff3_A);

            if (P_Anim.End)
            {
                GameManager->BS->isAttackEffectOn = false;
                isAttackCombo = false;
                isAttacking = false;
                isButtonInputed = false;
                Swap(Idle_A);
            }
        }
#pragma endregion

        if (P_TYPE_CHK(P_ANI_TYPE::DEATH) && P_Anim.End)
        {
            isDeathAnimOn = false;
            isDead = true;
            Dodge_After_Setup();

            //Gethit
            isParryOn = false;
            isParryAttack = false;

            isAttackCombo = false;
            isAttacking = false;

            isPushBack = false;


            isDecreasedHp = false;

            isSliding = false;
            isCrouchAttack = false;

            isConsuming = false;

            isGuilt = true;
            GameManager->BS->isGetGuilt = false;
            GameManager->BS->isKB_E = false;
            Swap(Idle_A);
            E_Swap(Idle_A);
        }
        if (P_TYPE_CHK(P_ANI_TYPE::KNEEL) && P_Anim.End)
        {
            Hp = (float)(full_HP);
            Health_Bottles = max_Bottles;
            isPraying = false;
            isPraied = true;
            Swap(Idle_A);
        }

        if (P_TYPE_CHK(P_ANI_TYPE::CROUCH) && P_Anim.End)
        {
            isCrouchAttack = false;
            E_Swap(Effect_Idle_A);
            Swap(Idle_A);
        }

        if ((P_TYPE_CHK(P_ANI_TYPE::GETHIT)))
        {
            if (GameManager->BS->Mon_LeftRight == 1)
                P_Anim.Location[0] -= 100 * 1 * TIME;
            else if (GameManager->BS->Mon_LeftRight == -1)
                P_Anim.Location[0] -= 100 * -1 * TIME;

            if (P_Anim.End)
            {
                Dodge_After_Setup();
                isParryOn = false;
                isParryAttack = false;

                isAttackCombo = false;
                isAttacking = false;

                isPushBack = false;


                isDecreasedHp = false;

                isSliding = false;
                isCrouchAttack = false;

                isConsuming = false;

                isHangOn = false;
                isHanging = false;
                Swap(Idle_A);
                E_Swap(Idle_A);
            }
        }

        if ((P_TYPE_CHK(P_ANI_TYPE::POTION)))
        {
            if (!isDecreasedHp)
            {
                if (Hp <= full_HP)
                {
                    if (Hp <= linear_HP + 50 && Hp <= full_HP)
                        Hp += Linear(50, 0, 0.8f) * TIME;
                }
            }

            if (P_Anim.End)
            {
                isDecreasedHp = false;
                isConsuming = false;
                Swap(Idle_A);
                E_Swap(Effect_Idle_A);
            }
        }
    }

    else  // 루프 애니메이션 일 경우
    {
        // RUN
        if (Direction[0] && isGrounded && !isRisingUp)
            Swap(Running_A);

        // JUMP
        else if (!Direction[0] && isFalling && !isGrounded)
        {
            Swap(Jumping_A);
        }
        else if (Direction[0] && isFalling && !isGrounded)
        {
            Swap(Jumping_Forward_A);
        }

        else if (isCrouching)
        {
            Swap(Crouching_A);
        }
        else if (isOnLadder)
        {
            Swap(Laddering_A);
        }
        else if (!isGettingUp)
        {
            Swap(Start_A);
        }

        else
            Swap(Idle_A);
    }
#pragma endregion
    if (GameStart)
    {
        GetNowScene()->isParrallax_On = true;
        // Inter_Col
        // 
        // Warpd
        for (int i = 0; i < Inter.Warp_Col.size(); i++)
        {
            if (RR_Col_Chk(Wall_Col, Wall_Col.Angle[2], Inter.Warp_Col[i], Inter.Warp_Col[i].Angle[2]))
            {
                isWarped = true;
                break;
            }
        }

        // Ladder
        for (int i = 0; i < Inter.Ladder_Col.size(); i++)
        {
            if (RR_Col_Chk(Feet_Col, Feet_Col.Angle[2], Inter.Ladder_Col[i], Inter.Ladder_Col[i].Angle[2]))
            {
                //for (int j = 0; j < non_Inter.Floor_Col.size(); j++)
                {
                    if (Feet_Col.Location[1] > Inter.Ladder_Col[i].Location[1])
                    {
                        if (Input::Get::Key::Down('S'))
                        {
                            isGrounded = false;
                            isFalling = false;

                            isOnLadder = true;
                        }
                    }
                    else if (Feet_Col.Location[1] < Inter.Ladder_Col[i].Location[1])
                    {
                        if (Input::Get::Key::Down('W'))
                        {
                            isGrounded = false;
                            isFalling = false;

                            isOnLadder = true;
                        }
                    }
                    if (isRisingUp || isFalling)
                    {
                        if (Input::Get::Key::Down('W'))
                        {
                            isGrounded = false;
                            isFalling = false;

                            isOnLadder = true;
                        }
                    }

                    if (isOnLadder)
                    {
                        P_Anim.Location[0] = Inter.Ladder_Col[i].Location[0];
                        P_Anim.Location[1] = StartPos_Y + (JumpingPos_Y + FallingPos_Y);
                        Direction[0] = 0;
                        LeftRight = 0;

                        if (Input::Get::Key::Press('W'))
                        {
                            if (Feet_Col.Location[1] > Inter.Ladder_Col[i].Location[1] + Inter.Ladder_Col[i].Length[1] / 2)
                            {
                                isOnLadder = false;
                                jumpPower = 0;
                            }
                        }
                        else if (Input::Get::Key::Press('S'))
                        {
                            if (Feet_Col.Location[1] < Inter.Ladder_Col[i].Location[1] - Inter.Ladder_Col[i].Length[1] / 2)
                            {
                                isOnLadder = false;
                                jumpPower = 0;

                            }
                        }
                    }

                }
            }
        }

        // non_Inter_Col
        //
        // Wall
        for (int i = 0; i < non_Inter.Wall_Col.size(); i++)
        {
            if (RR_Col_Chk(Wall_Col, Wall_Col.Angle[2], non_Inter.Wall_Col[i], non_Inter.Wall_Col[i].Angle[2]))
            {
                Direction[0] = 0;
                LeftRight = 0;
                speed = 0;
            }
        }

        //Hang


        if (isGrounded && Input::Get::Key::Press('W'))
        {
            if (Input::Get::Key::Down('K'))
            {
                isUpwardAttack = true;
                E_Swap(Upward_Eff_A);
                Swap(UpWard_Attack_A);
            }
        }

        if (STOP && isGrounded)
        {
            if (Input::Get::Key::Down('F') && Health_Bottles > 0)
            {
                Direction[0] = 0;
                LeftRight = 0;
                linear_HP = Hp;
                Swap(Potion_Drink_A);
                E_Swap(Potion_Aura_A);
                --Health_Bottles;
                isConsuming = true;
            }
        }


        if (GameManager->Scene_Num == 3)
        {
            if (P_Anim.Location[0] >= 59 && P_Anim.Location[0] <= 115)
            {
                KB_E.Location = { 88 , 40 };
                KB_E.Draw();

                if (STOP && isGrounded)
                {
                    if (Input::Get::Key::Down('E'))
                    {
                        // 부활시스템
                        Revive_Location = P_Anim.Location;
                        Revive_SceneNum = 3;
                        //
                        Direction[0] = 0;
                        LeftRight = 0;
                        isPraying = true;
                        Swap(Pray_A);
                    }
                }
            }
        }

        if (GameManager->Scene_Num == 4 && isGuilt && !GameManager->BS->isKB_E)
        {
            if (P_Anim.Location[0] >= DeadLocation[0] -50 && P_Anim.Location[0] <= DeadLocation[0] + 50)
            {
                KB_E.Location = DeadLocation;
                KB_E.Location[1] = DeadLocation[1] + 30;
                KB_E.Draw();
            }
        }

        if(isGrounded)
            isJumpAttacking = false;
        // printf("Hp : %.lf \n", Hp);

        HangLogic();
        HangOnLedge();

        Crouch(); // 앉기

        if (!isParryAttack && !isParryOn)
            Attack();

        if (isachieving)
            LinearSoul();

        // printf("linear: %d , achieve :%d \n", linear_Soul, achieveSoul);
        if (!isOnLadder) // 사다리에 있지 않을때만
            SlopeGravLogic(); // 경사 , 점프 , 중력

        // 이동속도
        if (!isGrounded && !isOnLadder && !isHanging && !isHangOnGround) // Flight상태이거나 매달린 상태가 아닐때
            Flight_Spd_Setup();


        if (STOP)
            InputComponent->Update();

        if (Hp <= 0 && Hp > -800)
        {
            Dead();
        }

        if (isDead)
        {
            isWarped = true;
        }

        if (P_Anim.RGBA[0] == 0)
        {
            LeftRight = 0;
            Direction[0] = 0;
        }

        //printf("P_Anim : %s , isDead : %d , isFalling : %d \n", P_Anim.Content, isDead, isFalling);
    }

    if (!isExecution)
        P_Anim.Draw();


    if (isAttacking || isJumpingAttack || isJumpUpwardAttack || isCrouchAttack || isGuardSlide || isConsuming)
    {
        P_Effect_Anim.Draw();
    }



    DrawCollider();

    //printf("Hp  : %d \n", Hp);


}
void APlayer::Dead()
{
    DeadLocation = P_Anim.Location;
    LeftRight = 0;
    Direction[0] = 0;

    tempsoul = soul;

    isDeathAnimOn = true;
    Swap(Death_A);
    Hp = -1000;
}
void APlayer::LinearSoul()
{
    soul += Linear(achieveSoul, 0, 0.8f) * TIME;
    if (soul >= linear_Soul + achieveSoul)
    {
        achieveSoul = 0;
        linear_Soul = 0;
        isachieving = false;
    }
}

void APlayer::SlopeGravLogic()
{
    if (isFalling || isRisingUp)
    {
        if (Input::Get::Key::Press('W'))
        {
            if (Input::Get::Key::Down('K'))
            {
                if (!isJumpAttacking)
                {
                    E_Swap(JumpingUpwardEff_A);
                    Swap(Jumping_Upward_Attack_A);
                    isJumpUpwardAttack = true;
                    isJumpAttacking = true;
                }
            }
        }
        else
        {
            if (Input::Get::Key::Down('K'))
            {
                if (!isJumpAttacking)
                {
                    E_Swap(JumpingEff_A);
                    Swap(Jumping_Attack_A);
                    isJumpingAttack = true;
                    isJumpAttacking = true;
                }
            }
        }
    }

    if (jumpingTime >= jumpPower / 2 && isRisingUp) // 최대 높이이상이면 else로 && 점프중이면
    {
        isRisingUp = false;
    }

    if (isRisingUp)
    {
        flying(jumpPower);
    }
    else
    {
        if (!isHangOnGround)
        {
            for (int i = 0; i < non_Inter.Floor_Col.size(); i++)
            {
                // Feet_Col RectAngle과  Floor 충돌체크
                if (RR_Col_Chk(Angle_Col, Angle_Col.Angle[2], non_Inter.Floor_Col[i], non_Inter.Floor_Col[i].Angle[2]))
                {
                    if (non_Inter.Floor_Col[i].Angle[2] && !isRightAngle)
                    {
                        angle_index = i;     // 콜라이더 발견시 인덱스
                        isCollider = true;   // 콜라이더 있음을 체크
                    }
                }
                // Feet_Col_바닥과 Floor 충돌체크
                if (PR_Col_Chk(Feet_Col.Location[0], Feet_Bottom, non_Inter.Floor_Col[i], non_Inter.Floor_Col[i].Angle[2]))
                {
                    isGrounded = true;
                    if (!non_Inter.Floor_Col[i].Angle[2]) // 직각 Floor 밟았을때
                    {
                        right_index = i; // 직각 Floor 콜라이더 인덱스
                        isSlopeToRight = true;   // 직각 Floor에 올라서다
                    }
                }
            }
        }

        if ((!isRightAngle && !isCollider && !isSlopeToRight) || isOnJumpDownCol) // 일단 직각일때만 떨어지게 만듬 -> isGrounded 유일한 false구간
        {
            isGrounded = false;
        }

        if (isGrounded)
        {
            isFalling = false;
            speed = 220 + Dodge_Spd;                           // 속도 + Dodge 속도 
            angle = non_Inter.Floor_Col[angle_index].Angle[2]; // 각도 -> Collider 탐지기가 찾은

            horizontal = std::cos(angle * static_cast<float>(M_PI) / 180.0f); // 수평
            vertical = std::sin(angle * static_cast<float>(M_PI) / 180.0f); // 수직 


            if (non_Inter.Floor_Col[angle_index].Angle[2] > 0)     //  ↗  이런 [ 경사 ] 일때
            {
                P_Anim.Location[0] += LeftRight * horizontal * speed * TIME; // X , Y 에 각각 스피드를 줌
                P_Anim.Location[1] += LeftRight * vertical * speed * TIME; // X , Y 에 각각 스피드를 줌

                if (RIGHT)        //  ↗ Right Top 으로 가는중  
                {
                    if (isSlopeToRight)
                    {
                        if (Feet_Bottom >= non_Inter.Floor_Col[right_index].Location[1] + non_Inter.Floor_Col[right_index].Length[1] / 2) // Feet_Bottom이 right Collider.Location[1]과 같거나 커지면
                        {
                            P_Anim.Location[1] = PlayerOnRightCollision;
                            angle_index = right_index;
                        }
                    }
                }

                else if (LEFT) // ↙ Left Bottom 으로 가는중
                {
                    if (isSlopeToRight)
                    {
                        if (Feet_Bottom <= non_Inter.Floor_Col[right_index].Location[1] + non_Inter.Floor_Col[right_index].Length[1] / 2) // Feet_Bottom이 right Collider.Location[1]과 같거나 작아지면
                        {
                            P_Anim.Location[1] = PlayerOnRightCollision;
                            angle_index = right_index;
                        }
                    }
                }
            }

            if (non_Inter.Floor_Col[angle_index].Angle[2] < 0) // ↘ 이런 [ 경사 ] 일때
            {
                P_Anim.Location[0] += LeftRight * horizontal * speed * TIME; // X , Y 에 각각 스피드를 줌
                P_Anim.Location[1] += LeftRight * vertical * speed * TIME; // X , Y 에 각각 스피드를 줌

                if (RIGHT)        //  ↘ Right Bottom 으로 가는중  
                {
                    if (isSlopeToRight)
                    {
                        if (Feet_Bottom <= non_Inter.Floor_Col[right_index].Location[1] + non_Inter.Floor_Col[right_index].Length[1] / 2) // Feet_Bottom이 right Collider.Location[1]과 같거나 커지면
                        {
                            P_Anim.Location[1] = PlayerOnRightCollision;
                            angle_index = right_index;
                        }
                    }
                }

                else if (LEFT) // ↖ Left Top으로 가는중
                {
                    if (isSlopeToRight)
                    {
                        if (Feet_Bottom >= non_Inter.Floor_Col[right_index].Location[1] + non_Inter.Floor_Col[right_index].Length[1] / 2) // Feet_Bottom이 right Collider.Location[1]과 같거나 작아지면
                        {
                            P_Anim.Location[1] = PlayerOnRightCollision;
                            angle_index = right_index;
                        }
                    }
                }
            }

            if (non_Inter.Floor_Col[angle_index].Angle[2] == 0)  // 직각일때
            {
                if ((Feet_Col.Location[0] >= non_Inter.Floor_Col[right_index].Location[0] - non_Inter.Floor_Col[right_index].Length[0] / 2
                    && Feet_Col.Location[0] <= non_Inter.Floor_Col[right_index].Location[0] + non_Inter.Floor_Col[right_index].Length[0] / 2))
                {
                    isRightAngle = true;
                    isCollider = false;
                    P_Anim.Location[0] += LeftRight * speed * TIME; // X , Y 에 각각 스피드를 줌
                    P_Anim.Location[1] = PlayerOnRightCollision;
                    //printf("index : %d \n", right_index);
                    //printf("Anim.Location[0] : %.lf , LeftRight : %d \n", Anim.Location[0], LeftRight);
                }
                else
                {
                    isRightAngle = false;  // 직각 Floor 위에 있으면 true
                    isSlopeToRight = false;
                }

                for (int i = 0; i < non_Inter.Floor_Down_Col.size(); i++)
                {
                    if (PR_Col_Chk(Feet_Col.Location[0], Feet_Bottom, non_Inter.Floor_Down_Col[i], non_Inter.Floor_Down_Col[i].Angle[2]))
                    {
                        if (Input::Get::Key::Press('S') && Input::Get::Key::Down(VK_SPACE))
                        {
                            JumpDown();
                        }
                    }
                }
            }

            Jump_Setup(); // 초기화
        }

        else // if(!isGrounded)
        {
            if (!isHanging)
            {
                isFalling = true;
                FallingPos_Y = -(gravTime * gravTime - 0 * gravTime);
                gravTime += 15 * TIME;

                if (FallingPos_Y < -30) // ㅋㅋ
                {
                    isOnJumpDownCol = false;
                }
            }
        }
    }
}

void APlayer::DrawCollider()
{
    {
        // 변환 위치
        //Head_Col.Location =   { Anim.Location[0]   + 1  * LeftRight , Anim.Location[1] + 15 }; //     머리 콜라이더 변환위치

        if (!P_Anim.Angle[1]) // 오른쪽방향 보고있음
        {
            Angle_Col.Location = { Feet_Col.Location[0]             , Feet_Col.Location[1] - 10 };
            Feet_Col.Location = { P_Anim.Location[0] + 1 * 1      , P_Anim.Location[1] - 50 }; //       발 콜라이더 변환위치
            Hitbox_Col.Location = { P_Anim.Location[0] + 1 * 1      , P_Anim.Location[1] - 20 }; // 히트박스 콜라이더 변환위치
            Attack_Col.Location = { P_Anim.Location[0] + 40 * 1      , P_Anim.Location[1] - 20 };

            if (!isSliding)
            {
                Wall_Col.Length = { 5, 15 };
                Wall_Col.Location = { P_Anim.Location[0] + 20 * 1 , P_Anim.Location[1] - 10 };
            }
            else
            {
                Wall_Col.Length = { 5,5 };
                Wall_Col.Location = { Feet_Col.Location[0] + 20 * 1 , Feet_Col.Location[1] };
            }
        }
        else                 // 왼쪽방향 보고있음
        {
            Angle_Col.Location = { Feet_Col.Location[0]             , Feet_Col.Location[1] - 10 };
            Feet_Col.Location = { P_Anim.Location[0] + 1 * -1     , P_Anim.Location[1] - 50 }; //       발 콜라이더 변환위치
            Hitbox_Col.Location = { P_Anim.Location[0] + 1 * -1     , P_Anim.Location[1] - 20 }; // 히트박스 콜라이더 변환위치
            Attack_Col.Location = { P_Anim.Location[0] + 40 * -1     , P_Anim.Location[1] - 20 };

            if (!isSliding)
            {
                Wall_Col.Length = { 5, 15 };
                Wall_Col.Location = { P_Anim.Location[0] + 20 * -1 , P_Anim.Location[1] - 10 };
            }
            else
            {
                Wall_Col.Length = { 5,5 };
                Wall_Col.Location = { Feet_Col.Location[0] + 20 * -1 , Feet_Col.Location[1] };
            }
        }

    }

    if (Release)
    {
        {
            Hitbox_Col.Draw();
            Attack_Col.Draw();
            Angle_Col.Draw();
            Wall_Col.Draw();
            Feet_Col.Draw();
        }
    }
}

void APlayer::MoveRight(float axis)
{
    if (!isOnLadder && !isHanging)
    {
        Direction[0] = axis;

        if (axis > 0.0f)
        {
            LeftRight = 1;
            P_Anim.Angle[1] = 0.0f;
        }
        else if (axis < 0.0f)
        {
            LeftRight = -1;
            P_Anim.Angle[1] = 180.f;
        }
        else
        {
            LeftRight = 0;
            return;
        }
    }
}
void APlayer::GetHit()
{
    //isPushBack = true;
    //Swap(Hit_PushBack_A);
    if (Hp > 0)
    {
        isPushBack = true;
        Swap(Hit_PushBack_A);
    }
}
void APlayer::Swap(Animation anim) // 애니메이션 스왑할때
{
    if (P_Anim.Content == anim.Content) return;

    P_Anim.Content = anim.Content;
    P_Anim.Length = anim.Length;
    P_Anim.Playback = 0.0f;
    P_Anim.End = false;
    P_Anim.Loop = anim.Loop;
    P_Anim.Duration = anim.Duration;

    SetNowAnim(*this, P_Anim);
}

void APlayer::E_Swap(Animation anim) // 애니메이션 스왑할때
{
    if (P_Effect_Anim.Content == anim.Content) return;

    P_Effect_Anim.Content = anim.Content;
    P_Effect_Anim.Length = anim.Length;
    P_Effect_Anim.Playback = 0.0f;
    P_Effect_Anim.End = false;
    P_Effect_Anim.Loop = anim.Loop;
    P_Effect_Anim.Duration = anim.Duration;
}

void APlayer::End()
{
    if (isDead)
    {
        GameManager->Scene_Num = Revive_SceneNum;
    }
    GetNowScene()->isParrallax_On = false;
    P_Anim.Location = { 0,0 };
    SetActorTransform(P_Anim);
}

void APlayer::Col_DefaultSetting()
{
    //int Xcol_Feet = 15;
    //int Ycol_Feet = -35;

    //int Xcol_Head = 15;
    //int Ycol_Head = 35;

    //int Xcol_Hitbox = 17;
    //int Ycol_Hitbox = -10;
}

void APlayer::TransparentCollider()
{
    //Feet_Col.Draw();
    //Head_Col.Draw();
    //Hitbox_Col.Alpha -> 알파값 0으로
}

void APlayer::SetEffectLocation()
{
    if (LEFT)
    {
        P_Effect_Anim.Angle[1] = 180.0f;
        effect_X = 7 * -1;
    }
    else if (RIGHT)
    {
        effect_X = 7 * 1;
        P_Effect_Anim.Angle[1] = 0.0f;
    }
    if (isConsuming)
    {
        P_Effect_Anim.Location[0] = P_Anim.Location[0];
        P_Effect_Anim.Location[1] = P_Anim.Location[1] + 20;
    }
    else
    {
        P_Effect_Anim.Location[0] = P_Anim.Location[0] + effect_X;
        P_Effect_Anim.Location[1] = P_Anim.Location[1] + effect_Y;
    }
}

void APlayer::ADebugCollider()
{
    Release = false;
}

void APlayer::ADrawCollider()
{
    Release = true;
}

int APlayer::GetColliderRelease() const
{
    return Release;
}
