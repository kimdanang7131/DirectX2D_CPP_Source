#pragma once
#include "Actor/Actor.h"

#define DEFAULTSIZE   100
#define TIME          Time::Get::Delta()


class APlayer : public AActor
{
public:
	APlayer();
	virtual ~APlayer() = default;

	virtual void Start()  override;
	virtual void Update() override;
	virtual void End()    override;

public: // ★ GameManager에게 플레이어 Location 값 보내줘서 카메라 앵글 맞춤

	void SetLocation(vector<2> newLocation)
	{
		P_Anim.Location = newLocation;
		StartPos_Y = newLocation[1];
	}

private: // 애니메이션

	//Animation P_Anim; // 본체

	Animation Idle_A;
	Animation Running_A;


	Animation Attack_A;
	Animation Attack2_A;
	Animation Attack3_A;

	// Effect
	Animation SlashEff_A;
	Animation SlashEff2_A;
	Animation SlashEff3_A;

	Animation JumpingUpwardEff_A;
	Animation JumpingEff_A;
	Animation Crouch_Eff_A;

	Animation Upward_Eff_A;
	Animation Effect_Idle_A;

	Animation Dodge_A;

	Animation Jump_A;
	Animation Jumping_A;

	Animation Jump_Forward_A;
	Animation Jumping_Forward_A;

	Animation Jumping_Attack_A;
	Animation Jumping_Upward_Attack_A;

	Animation Jump_Hanging_A;
	Animation Hang_Ground_A;

	Animation Crouching_A;
	Animation Crouching_Attack_A;


	Animation UpWard_Attack_A;
	Animation Laddering_A;

	Animation Parry_A;
	Animation Parry_Attack_A;

	Animation Hit_PushBack_A;
	Animation Pray_A;


	Animation Potion_Drink_A;
	Animation Getting_Up_A;
	Animation Death_A;
	Animation Start_A;
public:
	Animation Guard_Eff_A;
	Animation Guard_Slide_A;
	Animation Potion_Aura_A;




	// 플레이어 콜라이더
	Image KB_F;
	Image KB_E;
	Image Player_HP;
public: //Battle로 보내기
	Image Hitbox_Col;
	Image Attack_Col;
	Image Feet_Col;
	Image Wall_Col;
	Image Angle_Col;

public:
	bool isSliding = false;  // 슬라이딩 안한 상태
	bool isGrounded = false; // 첫 시작시 중력받고있으면 false -> 유용하게 많이쓰임

	bool isFalling = false;   // 떨어지기 시작하면 Animation  2가지로 나뉘게 체크 + true 하면 첫 시작시 화면 켜지기도 전에 이미 떨어지고 있어어 오류남
	bool isOnLadder = false;   // 사다리에 있는 중인지 체크
	bool isCrouching = false;   // 앉아있는지 체크
	bool isOnJumpDownCol = false;   // 아래점프 Collider 위에 있는지 체크
	bool isHanging = false;   // 벽매달 중인지 체크
	bool isHangOn = false;
	bool isHangOnGround = false;
	bool isAttackCombo = false;
	bool isAttacking = false;  // 공격중에 못움직이게

	bool isJumpingAttack = false;
	bool isJumpUpwardAttack = false;
	bool isCrouchAttack = false;
	bool isUpwardAttack = false;
	bool isParryOn = false;
	bool isParryAttack = false;
	bool isPushBack = false;
	bool isButtonInputed = false;
	bool isGuardSlide = false;
	bool isConsuming = false;
	bool isPraying = false;
	bool isPraied = false;
	bool isDead = false;
	bool isReviving = false;
	bool isJumpAttacking = false;
	bool isGettingUp = false;
	bool GameStart = false; // ST와 같이 씀 , F5를 눌러야 게임시작 -> F로 변경해야됨 

	bool isDeathAnimOn = false;
	vector<2> Revive_Location;
	int Revive_SceneNum = 3;

public: // 애니메이션 함수

	void E_Swap(Animation anim);

private: // 플레이어 동작들
	void MoveRight(float axis);	  // 왼오
	void Attack();                // 공격
	void Dodge();                 // 슬라이딩
	void Crouch();                // 웅크리기
	void Jump();                  // 점프
	void JumpDown();              // 다운점프

	void Parry();


	void SlopeGravLogic();        // 중력 핵심 앙꼬들 , 다운점프여부 , 경사이동
	void HangOnLedge();             // 벽매달
	void LadderLogic(float axis); // 사다리

	//정리
	void HangLogic();

public:
	void ParryAttack();
private: // 동작에 관한 클래스
	class CInputComponent* InputComponent;

private: // 게임 설정
	float ST = 0; // 5초후 시작

	int  angle_index = 0; // SCENE 넘어갈때마다 초기화 해줘야됨 
	int  right_index = 0; // SCENE 넘어갈때마다 초기화 해줘야됨 

private: // 플레이어 기본설정
	vector<2> Direction = { 0, 0 };

	float Dodge_Spd = 0;     // 슬라이딩 스피드
	int  LeftRight = 0;     // 왼오 방향



private: // JumpLogic 변수 
	float jumpPower = 0;  // ★ 점프파워 -> 높을수록 높이뜀?
	float jumping_Spd = 23; // ★ 점프속도 -> 높을수록 점프속도 빨라짐 
	float jumpingTime = 0;  // Delta =  100fps 컴퓨터는 (진동수를 Delta값에 넣어서) 1초에 100번 진동 -> (100 * 1/100)  * (내가 넣을값) = 1초에 (내가 넣을값) 출력

	float gravTime = 0; // 중력 시작시 사용

	// ★★★ 점프 Anim.Location[1]에 넣어줄 값들
	float JumpingPos_Y = 0; // 올라갈때 Y pos ( 올라갈때 이 값이 증가 )
	float FallingPos_Y = 0; // 떨어질때 Y pos ( 내려갈때 이 값이 증가 )
	float StartPos_Y = 0; // Player 점프하고 땅에 닿을때마다 Y위치 초기화 해줄 변수
	// ★★★

	bool isRisingUp = false; // 올라가는 중인지 체크 -> false면 바로 grav타임 증가하면서 중력 0부터 떨어짐          ★★

	// 내 경사진곳에서의 움직임의 핵심 앙꼬 삼총사
	bool isCollider = false; // Angle_Col 충돌체크 + 방향 꺾일때마다 콜라이더 있는지 체크( 직각은 체크 못함 )       ★★★
	bool isRightAngle = true;  //  Feet_Col 충돌체크 + 밟은 콜라이더가 직각일때만 체크 첫 시작시 직각Angle이므로 true ★★★
	bool isSlopeToRight = false; // 경사진곳에서 직각인 콜라이더를 밟았을때의 로직 체크
	// // // //

	float horizontal = 0; // Floor각도에서 받아온 X
	float vertical = 0; // Floor각도에서 받아온 Y
	float angle = 0; // Floor 각도 ( isCollider -> Angle_Col에서 체크 )
	float speed = 0; // Grounded에서의 속도


private: // HangLogic 변수
	int HangIndex = 0;   // 어떤 인덱스의 벽매달을 했는지 인덱스 넣기
	int HFIndex = 0;   // 벽매달 인덱스에 있는 Floor 인덱스 찾기 위하여

private: // 콜라이더 위치

	int Xcol_Feet = 15;
	int Ycol_Feet = -35;

	int Xcol_Head = 15;
	int Ycol_Head = 35;

	int Xcol_Hitbox = 17;
	int Ycol_Hitbox = -10;


	int effect_X = 8;
	int effect_Y = -19;

private: // Collider 함수
	void    DrawCollider();          // Collider 그리기
	void    TransparentCollider();   // Collider 투명화
	void    Col_DefaultSetting();    // 애니메이션 바뀔때 기본세팅

private: // Define용 함수

	__forceinline void flying(float jP) // Jump Logic
	{
		JumpingPos_Y = -(jumpingTime * jumpingTime - jP * jumpingTime);
		jumpingTime += jumping_Spd * TIME;
	}


	// 잠깐 만들어놓을것
	void ChangeScene_Setup(); // 씬 바뀔때마다 초기화 할 값들
	void Jump_Setup();        // 점프      하기 위한 초기화 값들 
	void Jump_Down_Setup();   // 점프 다운 하기 위한 초기화 값들
	void Dodge_After_Setup(); // 슬라이딩 이후 초기화
	void Flight_Spd_Setup();  // isGrounded가 아닐때 움직임 속도
	void HangLogic_SetUp();   // 벽매달에서 떨어지거나 올라갈때 초기화 값들

	//
	void SetEffectLocation();

public: // BS에서 디버그용
	virtual void ADebugCollider() override;
	virtual void ADrawCollider() override;
	int GetColliderRelease() const;

	void GetHit();
	void Swap(Animation anim);

	int full_HP = 0;
	float Hp;
	float HP_Gauge = 0;

	float soul;
	int Health_Bottles;
	int max_Bottles;

	int temp_Lose_Soul = 0;

	int attkcom3_Dmg = 30;
	int Jumping_Attk_Dmg = 30;
	int Crouch_Attk_Dmg = 30;
	int Parry_Counter_Dmg = 100;
	bool isAttackRange = false;
	bool isExecution = false;

	bool isGuilt = false;
	vector<2> DeadLocation;
	float tempsoul = 0;

	bool isAtBossStage = false;

	__forceinline void GetSoul(int soul)
	{
		achieveSoul = soul;
	}

	__forceinline void LoseSoul(int soul)
	{
		temp_Lose_Soul = soul;
		this->temp_Lose_Soul = 0;
	}

	__forceinline float Linear(int end, int start, float amount)
	{
		return (end - start) * amount + start;
	}

	float linear_HP = 0;
	Image Player_HP_Remain;

	Image HP_Potion_Full;
	Image HP_Potion_Empty;
	Image PlayerSoul;
	Rendering::Text::Component Text_Soul_Amount;


	void Dead();


	void LinearSoul();
	int achieveSoul = 0;
	float linear_Soul = 0;
	float temp_Soul = 0;
	bool isachieving = false;
};

