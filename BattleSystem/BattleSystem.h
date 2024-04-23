#pragma once
#include "Actor/Actor.h"
#include "Actor/AI/MONSTER/Monster.h"

//enum class P_ANI_TYPE { IDLE, RUN, DODGE, JUMP, H_HANG, CROUCH, LADDER, };
//
//enum class MONSTER_TYPE { ELDER, LIONHEAD, SHIELD_MON, FOIL_MON };
//
//enum class ELDER_ANI_TYPE { };
//enum class LIONHEAD_ANI_TYPE { };
//enum class SHIELD_ANI_TYPE { };
//enum class FOIL_ANI_TYPE { };

class BattleSystem
{
private:
	class  APlayer* Player;
	class AMonster* Boss;

	void ChangeScene_Setup();
public:
	void Start();
	void Update();


	Animation Object_Anim;
	Animation Pried_A;
	Animation Pried_Idle_A;

	Animation Guilt_Idle_A;
	Animation Guilt_Get_A;

private: // 몬스터 찾기
	//MONSTER_TYPE FindMonster(std::vector<class AMonster*> Monsters, MONSTER_TYPE M_TYPE);
	bool FindMonsterAtScene(std::string monName);
	bool ExistMonstersAtScene(std::map<std::string, AMonster*>& mons);
	bool CHK_PlayerAttack();
	int size = 0;


private:
	void BattleSys();
	void GetPlayerAttackTypeDmg(AMonster& mon, std::string content);
	void DeathLogic();
	vector<2> temp_pos;
	bool isExecution = false;
	//bool isPlayerDead = false;

private:
	bool Release_Temp = false;
	void DebugColliders();
	void DrawColliders();



public: // GameManager Player 여기로 옮겨서 대신해줌
	vector<2> GetPlayerLocation();
	vector<2> GetPlayerScale();
	void SetLocation(vector<2> newLocation);
	APlayer& GetNowPlayer();

	AMonster& GetNowBoss();
	void SetNowBoss(AMonster* boss);

	void SetPlayerRed();
	void SetPlayerOriginal();

	bool MonGetHitted(AMonster& mon);
	int Mon_LeftRight = 0;
	bool isAttackEffectOn = false;

	void CHK_MON_DIRECTION(AMonster& mon);

	void Swap(Animation anim);

	bool isRendering = false;

	bool isGetGuilt = false;
	bool isKB_E = false;
};


