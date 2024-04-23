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

public: // �� GameManager���� �÷��̾� Location �� �����༭ ī�޶� �ޱ� ����

	void SetLocation(vector<2> newLocation)
	{
		P_Anim.Location = newLocation;
		StartPos_Y = newLocation[1];
	}

private: // �ִϸ��̼�

	//Animation P_Anim; // ��ü

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




	// �÷��̾� �ݶ��̴�
	Image KB_F;
	Image KB_E;
	Image Player_HP;
public: //Battle�� ������
	Image Hitbox_Col;
	Image Attack_Col;
	Image Feet_Col;
	Image Wall_Col;
	Image Angle_Col;

public:
	bool isSliding = false;  // �����̵� ���� ����
	bool isGrounded = false; // ù ���۽� �߷¹ް������� false -> �����ϰ� ���̾���

	bool isFalling = false;   // �������� �����ϸ� Animation  2������ ������ üũ + true �ϸ� ù ���۽� ȭ�� �����⵵ ���� �̹� �������� �־�� ������
	bool isOnLadder = false;   // ��ٸ��� �ִ� ������ üũ
	bool isCrouching = false;   // �ɾ��ִ��� üũ
	bool isOnJumpDownCol = false;   // �Ʒ����� Collider ���� �ִ��� üũ
	bool isHanging = false;   // ���Ŵ� ������ üũ
	bool isHangOn = false;
	bool isHangOnGround = false;
	bool isAttackCombo = false;
	bool isAttacking = false;  // �����߿� �������̰�

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
	bool GameStart = false; // ST�� ���� �� , F5�� ������ ���ӽ��� -> F�� �����ؾߵ� 

	bool isDeathAnimOn = false;
	vector<2> Revive_Location;
	int Revive_SceneNum = 3;

public: // �ִϸ��̼� �Լ�

	void E_Swap(Animation anim);

private: // �÷��̾� ���۵�
	void MoveRight(float axis);	  // �޿�
	void Attack();                // ����
	void Dodge();                 // �����̵�
	void Crouch();                // ��ũ����
	void Jump();                  // ����
	void JumpDown();              // �ٿ�����

	void Parry();


	void SlopeGravLogic();        // �߷� �ٽ� �Ӳ��� , �ٿ��������� , ����̵�
	void HangOnLedge();             // ���Ŵ�
	void LadderLogic(float axis); // ��ٸ�

	//����
	void HangLogic();

public:
	void ParryAttack();
private: // ���ۿ� ���� Ŭ����
	class CInputComponent* InputComponent;

private: // ���� ����
	float ST = 0; // 5���� ����

	int  angle_index = 0; // SCENE �Ѿ������ �ʱ�ȭ ����ߵ� 
	int  right_index = 0; // SCENE �Ѿ������ �ʱ�ȭ ����ߵ� 

private: // �÷��̾� �⺻����
	vector<2> Direction = { 0, 0 };

	float Dodge_Spd = 0;     // �����̵� ���ǵ�
	int  LeftRight = 0;     // �޿� ����



private: // JumpLogic ���� 
	float jumpPower = 0;  // �� �����Ŀ� -> �������� ���̶�?
	float jumping_Spd = 23; // �� �����ӵ� -> �������� �����ӵ� ������ 
	float jumpingTime = 0;  // Delta =  100fps ��ǻ�ʹ� (�������� Delta���� �־) 1�ʿ� 100�� ���� -> (100 * 1/100)  * (���� ������) = 1�ʿ� (���� ������) ���

	float gravTime = 0; // �߷� ���۽� ���

	// �ڡڡ� ���� Anim.Location[1]�� �־��� ����
	float JumpingPos_Y = 0; // �ö󰥶� Y pos ( �ö󰥶� �� ���� ���� )
	float FallingPos_Y = 0; // �������� Y pos ( �������� �� ���� ���� )
	float StartPos_Y = 0; // Player �����ϰ� ���� ���������� Y��ġ �ʱ�ȭ ���� ����
	// �ڡڡ�

	bool isRisingUp = false; // �ö󰡴� ������ üũ -> false�� �ٷ� gravŸ�� �����ϸ鼭 �߷� 0���� ������          �ڡ�

	// �� ������������� �������� �ٽ� �Ӳ� ���ѻ�
	bool isCollider = false; // Angle_Col �浹üũ + ���� ���϶����� �ݶ��̴� �ִ��� üũ( ������ üũ ���� )       �ڡڡ�
	bool isRightAngle = true;  //  Feet_Col �浹üũ + ���� �ݶ��̴��� �����϶��� üũ ù ���۽� ����Angle�̹Ƿ� true �ڡڡ�
	bool isSlopeToRight = false; // ����������� ������ �ݶ��̴��� ��������� ���� üũ
	// // // //

	float horizontal = 0; // Floor�������� �޾ƿ� X
	float vertical = 0; // Floor�������� �޾ƿ� Y
	float angle = 0; // Floor ���� ( isCollider -> Angle_Col���� üũ )
	float speed = 0; // Grounded������ �ӵ�


private: // HangLogic ����
	int HangIndex = 0;   // � �ε����� ���Ŵ��� �ߴ��� �ε��� �ֱ�
	int HFIndex = 0;   // ���Ŵ� �ε����� �ִ� Floor �ε��� ã�� ���Ͽ�

private: // �ݶ��̴� ��ġ

	int Xcol_Feet = 15;
	int Ycol_Feet = -35;

	int Xcol_Head = 15;
	int Ycol_Head = 35;

	int Xcol_Hitbox = 17;
	int Ycol_Hitbox = -10;


	int effect_X = 8;
	int effect_Y = -19;

private: // Collider �Լ�
	void    DrawCollider();          // Collider �׸���
	void    TransparentCollider();   // Collider ����ȭ
	void    Col_DefaultSetting();    // �ִϸ��̼� �ٲ� �⺻����

private: // Define�� �Լ�

	__forceinline void flying(float jP) // Jump Logic
	{
		JumpingPos_Y = -(jumpingTime * jumpingTime - jP * jumpingTime);
		jumpingTime += jumping_Spd * TIME;
	}


	// ��� ����������
	void ChangeScene_Setup(); // �� �ٲ𶧸��� �ʱ�ȭ �� ����
	void Jump_Setup();        // ����      �ϱ� ���� �ʱ�ȭ ���� 
	void Jump_Down_Setup();   // ���� �ٿ� �ϱ� ���� �ʱ�ȭ ����
	void Dodge_After_Setup(); // �����̵� ���� �ʱ�ȭ
	void Flight_Spd_Setup();  // isGrounded�� �ƴҶ� ������ �ӵ�
	void HangLogic_SetUp();   // ���Ŵ޿��� �������ų� �ö󰥶� �ʱ�ȭ ����

	//
	void SetEffectLocation();

public: // BS���� ����׿�
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

