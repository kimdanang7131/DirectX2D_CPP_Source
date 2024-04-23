#pragma once
#include "Actor/AI/AI.h"

#define TIME       Time::Get::Delta()
#define RIGHT      LeftRight ==  1
#define LEFT       LeftRight == -1

class AMonster : public AAI
{

public:
	AMonster();
	virtual ~AMonster() = default;

	virtual void Start()  override;
	virtual void Update() override;
	virtual void End()    override;

	void SetLocation(vector<2> newLocation)
	{
		M_Anim.Location = newLocation;
	}

private: // 아마 Monster 공용
	int   walkSpd_Temp = 0;


	int   walkCount_Temp = 1; // 1 2 3 4 디버그용

	float walkCool = 0;
	int   FloorIndex = 0;
	bool isGrounded = false;
	bool isWalkEnd = true;
	float attackCool = 0;

	// 블퍼전용 공격 bool들
	bool isAttacking = false;
	bool isAttackOn = false;
	bool isAttackOff = false;
	bool isAttack_Activate = false;


	bool isPlayerInRange = false;

public:
	bool isPlayerParried = false;
	bool isParry = false;

	int   LeftRight = -1; // 보스 오른쪽 보고있음 -> 여러마리 생성할때 보는 방향
	int   walkCount = 4;
	int   walkSpd = 60;
	bool isDead = false;
	bool isDeathAnimEnd = false;
	bool isSturn = false;
	bool isExecutionOn = false;
	bool isStartExe = false;
	bool isPlayerExe = false;
	bool isPlayerAttacking = false;


	void Walk(Image& feet_Col, Animation& walk_A, int& walkSpd, int& walkCount);
	void WalkSetUp(Animation& walk_A);

	void Attack(Animation& walk_A);
	bool FindPlayer(Image& InRangeCol);


	Image HP_Bar;
	Image HP_Remain;

	Image Boss_HP_Bar;
	Image Boss_HP_Remain;

	Rendering::Text::Component Boss_Name;

#pragma region Foil_mon 애니메이션 / Collider

	Animation Foil_Idle_A;

	Animation Foil_Appear_Attack_A;
	Animation Foil_Attack_To_Idle_A;

	Animation Foil_Hurt_A;

	Animation Foil_Parry_A;

	Animation Foil_Death_A;

	Image Foil_Hitbox_Col;
	Image Foil_Alert_Col;
	Image Foil_InRange_Col;

#pragma endregion

#pragma region LionHead_mon 애니메이션 / Collider
	Animation LionHead_Idle_A;

	Animation LionHead_Walk_A;
	Animation LionHead_Walk_BackWard_A;

	Animation LionHead_Attack_A;

	Animation LionHead_Death_A;

	Image LionHead_Feet_Col;
	Image LionHead_Hitbox_Col;
	Image LionHead_Alert_Col;
	Image LionHead_InRange_Col;

	void Foil_Attack();

	bool isFoilFound = false;

#pragma endregion

#pragma region Shield_mon 애니메이션 / Collider
	Animation Shield_Idle_A;

	Animation Shield_AttackOn_A;
	Animation Shield_AttackOff_A;
	Animation Shield_Parry_A;

	Animation Shield_Walk_A;

	Animation Shield_Execution_A;
	Animation Shield_Death_A;
	Animation Shield_Sturn_A;

	Animation Shield_Effect_A;



public:
	Image Shield_Feet_Col;
	Image Shield_Hitbox_Col;
	Image Shield_Hit_Col;
	Image Shield_Attack_Col;
	Image Shield_Alert_Col;
	Image Shield_InRange_Col;

# pragma endregion

#pragma region Elder 애니메이션들
public:
	Animation Elder_Idle_A;

	Animation Elder_JumpOn_A;
	Animation Elder_Jumping_A;
	Animation Elder_JumpOff_A;

	Animation Elder_Attack_A;

	Animation Elder_Death1_A;
	Animation Elder_Death2_A;


	Animation Shield_Eff_A;

	Animation Spark_Eff1_A;
	Animation Spark_Eff2_A;
	Animation Spark_Eff3_A;
	Animation Effect_Idle_A;


	Animation Elder_Effect_Anim[8];
	Animation Elder_Beam_A;

public:
	Image Elder_Feet_Col;
	Image Elder_Hitbox_Col;
	Image Elder_Hit_Col;
	Image Elder_Attack_Col;
#pragma endregion 

#pragma region Elder 변수들
public:
	float StartPos_Y = 0;
	bool BeamStart = false;

private: //Elder 점프 전용 나중에 정리
	bool isRisingUp = false;

	float FallingPos_Y = 0;
	float JumpingPos_Y = 0;

	float jumpingTime = 0;
	float jumpPower = 20;
	float gravTime = 0;

	float linearX = 0; // 플레이어 위치 저장용


	bool GameStart = true; // 지울거


private: // Elder 애니메이션 체크 전용
	bool isAttackEnd = false;
	bool isJumped = false;

	// Elder 쿨타임
	float E_attackCool = 0;
	float E_JumpCool = 0;
#pragma endregion

#pragma region Elder_Patterns
private:
	int elder_Pattern = 1;

	void Elder_Jump();
	void Elder_Attack();
	void Jump_Setup();
	void DirCheck();


#pragma endregion

public: // 일단 public 나중에 BS만들고나서 고치기
	void Swap(Animation anim);

private: // 나중에 Collider Draw 없애는 기능
	void DrawCollider();

	// 몬스터 방향 항상 바꾸게
	__forceinline void ChkDirection()
	{
		if (LEFT)
			M_Anim.Angle[1] = 180.0f;
		else if (RIGHT)
			M_Anim.Angle[1] = 0.0f;
	}

	void DeadLogic(Animation Death_Anim);

public:
	int full_HP = 0;
	float HP_Gauge = 0;
	virtual void ADebugCollider() override;
	virtual void ADrawCollider() override;

	void E_Swap(Animation anim);
	void Elder_E_Swap(Animation anim , int index);

	Image Beam_Col;

	void DrawHpBar();

	void DrawBossHpBar();

	bool CHK_PlayerAttacking();


	float GetBossPercentage()
	{
		HP_Gauge = (572 * ((Hp * 100) / (float)full_HP) / 100);
		return HP_Gauge;
	}

	// Jump Logic
	__forceinline void flying(float jP, float jp_Spd)
	{
		JumpingPos_Y = -(jumpingTime * jumpingTime - jP * jumpingTime);
		jumpingTime += jp_Spd * TIME;
	}


	__forceinline float GetPercentage()
	{
		HP_Gauge = (64 * ((Hp * 100) / (float)full_HP) / 100);
		return HP_Gauge;
	}
    float beam_cool = 0;
	void Elder_BEAM_Logic();
	int beam_index = 0;
	bool nextBeam = true;

	bool isElderAttacked = false;

};

