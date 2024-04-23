#include "stdafx.h"
#include "BattleSystem.h"

#define GetNowScene()                 GameManager->GetNowScene()
#define FMonsNowScene              GameManager->GetNowScene()->Monsters
#define P_Content                  Player->P_Anim.Content

#define Player_Anim_Start          Player->P_Anim.Playback > 0 && Player->P_Anim.Playback <= Player->P_Anim.Duration * 0.2f
#define Player_Anim_Update         Player->P_Anim.Playback > 0.5f && Player->P_Anim.Playback <= Player->P_Anim.Duration * 0.6f
#define Player_Anim_End            Player->P_Anim.Playback > 0.8f && Player->P_Anim.Playback <= Player->P_Anim.Duration * 0.9f

#define Mon_Anim_Start             mon.M_Anim.Playback > 0 && mon.M_Anim.Playback <= mon.M_Anim.Duration * 0.2f
#define Mon_Anim_End               mon.M_Anim.Playback > 0 && mon.M_Anim.Playback >= mon.M_Anim.Duration * 0.8f

#define Mon_Elem_Anim_Update       elem.second->M_Anim.Playback > 0.6f &&  elem.second->M_Anim.Playback <= elem.second->M_Anim.Duration * 0.7f 
#define Mon_Elem_Anim_End          elem.second->M_Anim.Playback >= elem.second->M_Anim.Duration * 0.8f 

void BattleSystem::Start()
{
	Player = new APlayer;
	Player->Start();

	Boss = new AMonster;

	if (ExistMonstersAtScene(FMonsNowScene))
	{
		for (auto const& elem : FMonsNowScene)
			elem.second->Start();
	}

	Pried_A.Content = "Pried/Pried_Normal/Pried";
	Pried_A.Length = { DEFAULTSIZE , DEFAULTSIZE + 50 };
	Pried_A.Loop = true;
	Pried_A.Duration = 2.3f;

	Pried_Idle_A.Content = "Pried/Pried_none";
	Pried_Idle_A.Length = { DEFAULTSIZE , DEFAULTSIZE + 50 };
	Pried_Idle_A.Loop = true;
	Pried_Idle_A.Duration = 2.3f;

	Guilt_Idle_A.Content = "GuiltSystem/Guilt_BlinkFxs";
	Guilt_Idle_A.Length = { DEFAULTSIZE , DEFAULTSIZE + 10 };
	Guilt_Idle_A.Loop = true;
	Guilt_Idle_A.Duration = 1;

	Guilt_Get_A.Content = "GuiltSystem/Guilt_DropVanish";
	Guilt_Get_A.Length = { DEFAULTSIZE , DEFAULTSIZE + 100 };
	Guilt_Get_A.Loop = false;
	Guilt_Get_A.Duration = 1;


	Object_Anim = Pried_Idle_A;
}

void BattleSystem::Update()
{


	if (GameManager->Scene_Num == 3)
	{
		if (Player->isPraied)
		{
			Swap(Pried_A);
		}
		Object_Anim.Location = { 86.5, -35.8 };
		Object_Anim.Draw();
	}


	if (GameManager->Scene_Num == 4)
	{
		if (Player->isGuilt)
		{
			if (Input::Get::Key::Down('E') && !isGetGuilt)
			{
				isKB_E = true;
				Swap(Guilt_Get_A);
			}
			if(!isKB_E)
			{
				Swap(Guilt_Idle_A);
				Object_Anim.Location = Player->DeadLocation;
			}

			if (!isGetGuilt)
				Object_Anim.Draw();
		}
	}


	if (!Object_Anim.Loop)
	{
		if (Object_Anim.Content == "GuiltSystem/Guilt_DropVanish" && Object_Anim.End)
		{
			Player->linear_Soul = Player->soul;
			Player->GetSoul(static_cast<int>(Player->tempsoul));
			Player->isachieving = true;

			isGetGuilt = true;
			Swap(Guilt_Idle_A);
		}
	}
#pragma region Update실행
	// 몬스터 Update
	if (ExistMonstersAtScene(FMonsNowScene))
	{
		for (auto const& elem : FMonsNowScene)
			elem.second->Update();
	}
	// Player Update
	Player->Update();


#pragma endregion 

	// 다음씬 넘어갈시 초기화값들 설정
	if (Player->isWarped)
		ChangeScene_Setup();


	DeathLogic();

	if (ExistMonstersAtScene(FMonsNowScene)) // 현재 씬에 몬스터가 있고
		BattleSys();




	//printf("P_Anim.TYPE = %s \n ", Player->P_Anim.Content);


	if (Input::Get::Key::Down(0x34)) // 콜라이더 지울때 4번
		DebugColliders();
	else if (Input::Get::Key::Down(0x35))  // 콜라이더 킬때 5번
		DrawColliders();

	//printf("Player->isParryAttack : %d \n", Player->isParryAttack);
}

//map.count(key) != 0 -> 요소 수 가져옴

bool BattleSystem::ExistMonstersAtScene(std::map<std::string, AMonster*>& mons)
{
	if (mons.size())
		return true;
	else
		return false;
}



bool BattleSystem::FindMonsterAtScene(std::string monName)
{
	if (FMonsNowScene.find(monName) != FMonsNowScene.end())
		return true;

	else
		return false;
}

void BattleSystem::ChangeScene_Setup()
{
	Release_Temp = Player->GetColliderRelease();

	if (ExistMonstersAtScene(FMonsNowScene))
	{
		FMonsNowScene.clear();
	}

	if (Player->isDead)
	{
		Player->End();
		GameManager->Scene_Num = 3;
		GameManager->ChangeScene("Scene3");

		Player->isWarped = false;
		Player->isDead = false;
		Player->isReviving = true;
		Player->GameStart = true;
	}
	else
	{
		Player->End();
		GameManager->ChangeScene("Scene" + std::to_string(++(GameManager->Scene_Num)));
	}

	if (ExistMonstersAtScene(FMonsNowScene))
	{
		for (auto const& elem : FMonsNowScene)
			elem.second->Start();
	}

	Player->Start();
	Player->isWarped = false;
	if (Release_Temp)
		DrawColliders();
	else
		DebugColliders();
}


void BattleSystem::DebugColliders()
{
	Player->ADebugCollider();

	if (ExistMonstersAtScene(FMonsNowScene))
	{
		for (auto const& elem : FMonsNowScene)
			elem.second->ADebugCollider();
	}

	GameManager->GetNowScene()->DebugCollider();
}

void BattleSystem::BattleSys()
{
	for (auto const& elem : FMonsNowScene) // 씬에 있는 몬스터를 전부 찾아서
	{
		if (elem.second->MONSTER_TYPE_CHK(MONSTER_TYPE::SHIELD_MON))   // 찾은 몬스터가 쉴드몬일때
		{
			if (elem.second->SHIELD_TYPE_CHK(SHIELD_ANI_TYPE::ATTACK) && elem.second->M_Anim.Content == "Mon_Shield/ATTACK/Attack_On"
				&& Mon_Elem_Anim_End)  // 찾은 몬스터가 공격중일때
			{
				CHK_MON_DIRECTION(*elem.second);

				if (P_Content == "PLAYER/PARRY/Parry" && Player->RR_Col_Chk(Player->Wall_Col, 0, elem.second->Shield_InRange_Col, 0))              // 플레이어가 공격중일때 패링하면
				{
					Player->isParryAttack = true;
					elem.second->Swap(elem.second->Shield_Parry_A);
				}
				else if (Mon_Elem_Anim_End && Player->RR_Col_Chk(Player->Hitbox_Col, 0, elem.second->Shield_InRange_Col, 0)
					&& elem.second->M_Anim.Content == "Mon_Shield/ATTACK/Attack_On" && !Player->isDecreasedHp && !Player->isSliding && !Player->isExecution)
				{
					Player->isDecreasedHp = true;
					Player->GetHit();

					if (Player->isDecreasedHp)
					{
						Player->Hp -= elem.second->attkDmg;
					}
				}
			}
			if (elem.second->SHIELD_TYPE_CHK(SHIELD_ANI_TYPE::PARRY) && Player->P_TYPE_CHK(P_ANI_TYPE::IDLE))
			{
				if (Input::Get::Key::Down('K'))
				{
					Player->ParryAttack();

				}

				else if (elem.second->SHIELD_TYPE_CHK(SHIELD_ANI_TYPE::PARRY) && elem.second->M_Anim.Playback >= elem.second->M_Anim.Duration * 0.9f)
				{
					Player->isParryAttack = false;
				}
			}

			if (CHK_PlayerAttack())
			{
				if ((Player->P_Anim.Angle[1] == elem.second->M_Anim.Angle[1]))
				{
					if (Player->RR_Col_Chk(Player->Attack_Col, 0, elem.second->Shield_Hitbox_Col, 0))
						GetPlayerAttackTypeDmg(*elem.second, Player->P_Anim.Content);
				}

				else if ((Player->P_Anim.Angle[1] != elem.second->M_Anim.Angle[1]))
				{

					if (Player->isParryAttack && Player->RR_Col_Chk(Player->Attack_Col, 0, elem.second->Shield_Hit_Col, 0)) // 패링시 공격 안닿는것 방지
						GetPlayerAttackTypeDmg(*elem.second, Player->P_Anim.Content);

					else if (Player->RR_Col_Chk(Player->Attack_Col, 0, elem.second->Shield_Hit_Col, 0))
					{
						elem.second->E_Swap(elem.second->Shield_Effect_A);
					}
				}
			}
		}

		else if (elem.second->MONSTER_TYPE_CHK(MONSTER_TYPE::LIONHEAD))
		{
			CHK_MON_DIRECTION(*elem.second);

			if (P_Content == "PLAYER/PARRY/Parry" && Player->RR_Col_Chk(Player->Wall_Col, 0, elem.second->LionHead_InRange_Col, 0)
				&& elem.second->LIONHEAD_TYPE_CHK(LIONHEAD_ANI_TYPE::ATTACK) && Mon_Elem_Anim_Update)
			{
				Player->isGuardSlide = true;
			}

			else if (elem.second->LIONHEAD_TYPE_CHK(LIONHEAD_ANI_TYPE::ATTACK) && Mon_Elem_Anim_Update
				&& Player->RR_Col_Chk(Player->Hitbox_Col, 0, elem.second->LionHead_InRange_Col, 0) && !Player->isDecreasedHp && !Player->isParryOn
				&& !Player->isSliding && !Player->isExecution)
			{
				Player->isDecreasedHp = true;
				Player->GetHit();

				if (Player->isDecreasedHp)
				{
					Player->Hp -= elem.second->attkDmg;
				}
			}

			if (CHK_PlayerAttack())
			{
				if ((Player->P_Anim.Angle[1] == elem.second->M_Anim.Angle[1]))
				{
					if (Player->RR_Col_Chk(Player->Attack_Col, 0, elem.second->LionHead_Hitbox_Col, 0))
						GetPlayerAttackTypeDmg(*elem.second, Player->P_Anim.Content);
				}

				else if ((Player->P_Anim.Angle[1] != elem.second->M_Anim.Angle[1]))
				{
					if (Player->RR_Col_Chk(Player->Attack_Col, 0, elem.second->LionHead_Hitbox_Col, 0))
						GetPlayerAttackTypeDmg(*elem.second, Player->P_Anim.Content);
				}
			}
		}

		else if (elem.second->MONSTER_TYPE_CHK(MONSTER_TYPE::FOIL_MON))
		{
			if (elem.second->FOIL_TYPE_CHK(FOIL_ANI_TYPE::ATTACK) && elem.second->M_Anim.Content == "Mon_Foil/ATTACK/Appear_Attack"
				&& Mon_Elem_Anim_End)  // 찾은 몬스터가 공격중일때
			{
				CHK_MON_DIRECTION(*elem.second);

				if (P_Content == "PLAYER/PARRY/Parry" && Player->RR_Col_Chk(Player->Wall_Col, 0, elem.second->Foil_InRange_Col, 0))              // 플레이어가 공격중일때 패링하면
				{
					Player->isParryAttack = true;
					elem.second->Swap(elem.second->Foil_Parry_A);
				}
				else if (Mon_Elem_Anim_End && Player->RR_Col_Chk(Player->Hitbox_Col, 0, elem.second->Foil_InRange_Col, 0)
					&& elem.second->M_Anim.Content == "Mon_Foil/ATTACK/Appear_Attack" && !Player->isDecreasedHp
					&& !Player->isSliding && !Player->isExecution)
				{
					Player->isDecreasedHp = true;
					Player->GetHit();

					if (Player->isDecreasedHp)
					{
						Player->Hp -= elem.second->attkDmg;
					}
				}
			}
			if (elem.second->FOIL_TYPE_CHK(FOIL_ANI_TYPE::PARRY) && Player->P_TYPE_CHK(P_ANI_TYPE::IDLE))
			{
				if (Input::Get::Key::Down('K'))
				{
					Player->ParryAttack();
				}

				else if (elem.second->FOIL_TYPE_CHK(FOIL_ANI_TYPE::PARRY) && elem.second->M_Anim.Playback >= elem.second->M_Anim.Duration * 0.9f)
				{
					Player->isParryAttack = false;
				}
			}

			if (CHK_PlayerAttack())
			{
				if ((Player->P_Anim.Angle[1] == elem.second->M_Anim.Angle[1]))
				{
					if (!elem.second->FOIL_TYPE_CHK(FOIL_ANI_TYPE::IDLE) || elem.second->M_Anim.Content == "Mon_Foil/ATTACK/Attack_To_Idle")
					{
						if (Player->RR_Col_Chk(Player->Attack_Col, 0, elem.second->Foil_Hitbox_Col, 0))
							GetPlayerAttackTypeDmg(*elem.second, Player->P_Anim.Content);
					}
				}

				else if ((Player->P_Anim.Angle[1] != elem.second->M_Anim.Angle[1]))
				{
					if (!elem.second->FOIL_TYPE_CHK(FOIL_ANI_TYPE::IDLE) || elem.second->M_Anim.Content == "Mon_Foil/ATTACK/Attack_To_Idle")
					{
						if (Player->isParryAttack && Player->RR_Col_Chk(Player->Attack_Col, 0, elem.second->Foil_Hitbox_Col, 0)) // 패링시 공격 안닿는것 방지
							GetPlayerAttackTypeDmg(*elem.second, Player->P_Anim.Content);
					}
				}
			}
		}

		else if (elem.second->MONSTER_TYPE_CHK(MONSTER_TYPE::ELDER))
		{
			SetNowBoss(elem.second);
			CHK_MON_DIRECTION(*elem.second);

			if (elem.second->ELDER_TYPE_CHK(ELDER_ANI_TYPE::JUMP) && Mon_Elem_Anim_Update
				&& Player->RR_Col_Chk(Player->Hitbox_Col, 0, elem.second->Elder_Hit_Col, 0)  && !Player->isDecreasedHp
				&& !Player->isSliding && !Player->isExecution && !Player->isPushBack)
			{
				Player->isConsuming = false;
				Player->isDecreasedHp = true;


				if (Player->Hp > elem.second->attkDmg)
				{
					if (Player->isDecreasedHp)
					{
						Player->Hp -= elem.second->attkDmg;
					}

					Player->GetHit();
				}
				else if(Player->Hp <= elem.second->attkDmg)
				{
					if (Player->isDecreasedHp)
					{
						Player->Hp -= elem.second->attkDmg;
					}
					Player->Dead();
				}
			}

			else if (elem.second->ELDER_TYPE_CHK(ELDER_ANI_TYPE::ATTACK) && Mon_Elem_Anim_Update
				&& Player->RR_Col_Chk(Player->Hitbox_Col, 0, elem.second->Elder_Attack_Col, 0) && !Player->isDecreasedHp
				&& !Player->isSliding && !Player->isExecution && !Player->isPushBack)
			{
				Player->isConsuming = false;
				Player->isDecreasedHp = true;



				if (Player->Hp > elem.second->attkDmg)
				{
					if (Player->isDecreasedHp)
					{
						Player->Hp -= elem.second->attkDmg;
					}
					Player->GetHit();
				}
				else if (Player->Hp <= elem.second->attkDmg)
				{
					if (Player->isDecreasedHp)
					{
						Player->Hp -= elem.second->attkDmg;
					}
					Player->Dead();
				}
			}

			else if (elem.second->BeamStart && Player->RR_Col_Chk(Player->Hitbox_Col, 0, elem.second->Beam_Col, 0) && !Player->isDecreasedHp
				&& !Player->isSliding && !Player->isExecution && !Player->isPushBack  )
			{
				Player->isConsuming = false;
				Player->isDecreasedHp = true;

				if (Player->Hp > elem.second->attkDmg)
				{
					if (Player->isDecreasedHp)
					{
						Player->Hp -= elem.second->attkDmg;
					}
					Player->GetHit();
				}
				else if (Player->Hp <= elem.second->attkDmg)
				{
					if (Player->isDecreasedHp)
					{
						Player->Hp -= elem.second->attkDmg;
					}
					Player->Dead();
				}
			}


			if (CHK_PlayerAttack())
			{
				if ((Player->P_Anim.Angle[1] == elem.second->M_Anim.Angle[1]))
				{
					if (Player->RR_Col_Chk(Player->Attack_Col, 0, elem.second->Elder_Hitbox_Col, 0))
						GetPlayerAttackTypeDmg(*elem.second, Player->P_Anim.Content);
				}
				else if ((Player->P_Anim.Angle[1] != elem.second->M_Anim.Angle[1]))
				{
					if (Player->RR_Col_Chk(Player->Attack_Col, 0, elem.second->Elder_Hitbox_Col, 0))
						GetPlayerAttackTypeDmg(*elem.second, Player->P_Anim.Content);
				}
			}

			if (elem.second->M_Anim.RGBA[0] == 0)
			{
				isRendering = true;
			}
		}
	}
}

bool BattleSystem::CHK_PlayerAttack()
{
	if (P_Content == "PLAYER/PARRY/ParryCounter" || P_Content == "PLAYER/ATTACK/hitcombo3"
		|| P_Content == "PLAYER/ATTACK/hitcombo1" || P_Content == "PLAYER/ATTACK/hitcombo2"
		|| P_Content == "PLAYER/CROUCH/Crouch_Attack" || P_Content == "PLAYER/JUMP/JumpingAttack" || P_Content == "PLAYER/JUMP/JumpingUpwardAttack")
		return true;
	else
		return false;
}

void BattleSystem::GetPlayerAttackTypeDmg(AMonster& mon, std::string content)
{
	if (P_Content == "PLAYER/PARRY/ParryCounter" && Player_Anim_Update && !isAttackEffectOn)
	{
		if (!isAttackEffectOn)
		{
			mon.Hp -= Player->Parry_Counter_Dmg;
			mon.E_Swap(mon.Spark_Eff1_A);
			isAttackEffectOn = true;
		}
	}

	else if (P_Content == "PLAYER/ATTACK/hitcombo1" || P_Content == "PLAYER/ATTACK/hitcombo2" || P_Content == "PLAYER/CROUCH/Crouch_Attack"
		|| P_Content == "PLAYER/JUMP/JumpingAttack" || P_Content == "PLAYER/JUMP/JumpingUpwardAttack"
		&& Player_Anim_Start && !isAttackEffectOn)
	{
		if (!isAttackEffectOn)
		{
			mon.Hp -= Player->attkDmg;
			mon.E_Swap(mon.Spark_Eff1_A);
			isAttackEffectOn = true;
		}
	}

	else if ((P_Content == "PLAYER/ATTACK/hitcombo3") && Player_Anim_Start && !isAttackEffectOn)
	{
		if (!isAttackEffectOn)
		{
			mon.Hp -= Player->attkDmg;
			mon.E_Swap(mon.Spark_Eff3_A);
			isAttackEffectOn = true;
		}
	}
}

void BattleSystem::DeathLogic()
{
	for (auto it = FMonsNowScene.begin(); it != FMonsNowScene.end();)
	{
		if (it->second->isSturn && it->second->isExecutionOn)
		{
			if (Input::Get::Key::Down('Y'))
			{
				Player->isExecution = true;
				isExecution = true;
				it->second->isPlayerExe = true;
				temp_pos = it->second->M_Anim.Location;
				it->second->isStartExe = true;
				it->second->isSturn = false;

			}
		}

		if (it->second->isDead)
		{
			if (isExecution)
			{
				it->second->isPlayerExe = false;
				Player->SetLocation(temp_pos);
				isExecution = false;
				Player->isExecution = false;
			}

			if (it->second->MONSTER_TYPE_CHK(MONSTER_TYPE::ELDER))
			{
				isRendering = false;
			}

			Player->linear_Soul = Player->soul;
			Player->isachieving = true;
			Player->GetSoul(it->second->soul);
			FMonsNowScene.erase(it++->first);
		}
		else
		{
			++it;
		}
	}
}

void BattleSystem::CHK_MON_DIRECTION(AMonster& mon)
{
	if (mon.M_Anim.Angle[1] == 180.0f)
	{
		Mon_LeftRight = 1;
	}
	else
	{
		Mon_LeftRight = -1;
	}
}


void BattleSystem::DrawColliders()
{
	Player->ADrawCollider();

	if (ExistMonstersAtScene(FMonsNowScene))
	{
		for (auto const& elem : FMonsNowScene)
			elem.second->ADrawCollider();
	}

	GameManager->GetNowScene()->DrawCollider();
}

vector<2> BattleSystem::GetPlayerLocation()
{
	return Player->GetActorLocation();
}
vector<2> BattleSystem::GetPlayerScale()
{
	return Player->GetActorScale();
}
void BattleSystem::SetLocation(vector<2> newLocation)
{
	Player->SetLocation(newLocation);
}

APlayer& BattleSystem::GetNowPlayer()
{
	return *Player;
}

AMonster& BattleSystem::GetNowBoss()
{
	return *Boss;
}

void BattleSystem::SetNowBoss(AMonster* boss)
{
	Boss = boss;
}

void BattleSystem::SetPlayerRed()
{
	Player->P_Anim.RGBA[0] = 0;
}

void BattleSystem::SetPlayerOriginal()
{
	Player->P_Anim.RGBA[0] = 1;
}

void BattleSystem::Swap(Animation anim) // 애니메이션 스왑할때
{
	if (Object_Anim.Content == anim.Content) return;

	Object_Anim.Content = anim.Content;
	Object_Anim.Length = anim.Length;
	Object_Anim.Playback = 0.0f;
	Object_Anim.End = false;
	Object_Anim.Loop = anim.Loop;
	Object_Anim.Duration = anim.Duration;
}

//MONSTER_TYPE BattleSystem::FindMonster(std::vector<class AMonster*> Monsters , MONSTER_TYPE M_TYPE)
//{
//	MONSTER_TYPE Mon_Type;
//	for (auto const& elem : FMonsNowScene)
//	{
//		if(M_TYPE == elem.second->M_Anim.)
//	}
//	
//	switch (M_TYPE)
//	{
//	   case MONSTER_TYPE::ELDER:
//		   return MONSTER_TYPE::ELDER;
//		   break;
//	   case MONSTER_TYPE::LIONHEAD:
//		   return MONSTER_TYPE::LIONHEAD;
//		   break;
//	   case MONSTER_TYPE::SHIELD_MON:
//		   return MONSTER_TYPE::SHIELD_MON;
//		   break;
//	   case MONSTER_TYPE::FOIL_MON:
//		   return MONSTER_TYPE::FOIL_MON;
//		   break;
//	default:
//		break;
//	}
//}
