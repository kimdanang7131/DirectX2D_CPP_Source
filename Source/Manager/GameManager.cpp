#include "stdafx.h"
#include "GameManager.h"
#include <Windows.h>

#define Player_Ypos 80
#define Player()    BS->GetNowPlayer()
#define Boss()	    BS->GetNowBoss()

EGameManager::EGameManager()
{
	Scenes.try_emplace("Scene1", new Scene1);
	Scenes.try_emplace("Scene2", new Scene2);
	Scenes.try_emplace("Scene3", new Scene3);
	Scenes.try_emplace("Scene4", new Scene4);
	Scenes.try_emplace("MapEditor", new MapEditor);
	Now = "Scene1";
}

EGameManager::~EGameManager()
{
	for (auto scene : Scenes) delete scene.second;
}

void EGameManager::Init()
{
	hwnd = FindWindow("Window", "Game");

	GetNowScene()->Start();
	if (Now != "MapEditor")
	{
		BS = new BattleSystem();
		BS->Start();

		Background = GetNowScene()->Background;   // 카메라 크기 때문에
		BeforePlayer = GetNowScene()->BeforePlayer; // Player를 그리고나서 그려야되기 때문에

		// 
		//Pre_playerP = { -379,-56 + Player_Ypos }; -> Lerp카메라 만들자


		Pre_cameraPos = { Scenes.at(Now)->Scenes_StartPos[0], (Scenes.at(Now)->Scenes_StartPos[1] + Player_Ypos) }; // parrallax용
		Camera.Length = { 720,360 };
	}
}

void EGameManager::ChangeScene(std::string SceneName)
{
	Scenes.at(Now)->End();

	Now = SceneName;
	Scenes.at(Now)->Start();

	if (Now != "MapEditor")
	{
		Scenes.at(Now)->isParrallax_On = false;
		Scenes.at(Now)->Start();

		Background = Scenes.at(SceneName)->Background;   // 카메라 크기 때문에
		BeforePlayer = Scenes.at(SceneName)->BeforePlayer; // Player를 그리고나서 그려야되기 때문에
		BS->SetLocation(Scenes.at(SceneName)->Scenes_StartPos);
		isSceneChanged = true;
	}
}

//void EGameManager::DeleteActor(AActor* actor)
//{
//	std::list<AActor*>::iterator elem = std::find(Actors.begin(), Actors.end(), actor);
//	if (elem != Actors.end()) Actors.erase(elem);
//}

vector<2> EGameManager::GetCameraMovement() // 카메라 무빙
{
	vector<2> movement = Camera.Location - Pre_cameraPos;
	Pre_cameraPos = Camera.Location;
	//if (movement[0] == 0 && movement[1] == 0) return;

	return movement;
}

float EGameManager::GetPercentage()
{
	Player().HP_Gauge = (430 * ((Player().Hp * 100) / (float)Player().full_HP) / 100);
	return Player().HP_Gauge;
}

float EGameManager::GetBossPercentage()
{

	Boss().HP_Gauge = (64 * ((Boss().Hp * 100) / (float)Boss().full_HP) / 100);
	return Boss().HP_Gauge;
}

void EGameManager::DrawPlayerHpBar()
{
	GetPercentage();

	Player().Player_HP.Location[0] = Camera.Location[0] - Camera.Length[0] / 2 + 150;
	Player().Player_HP.Location[1] = Camera.Location[1] + Camera.Length[1] / 2 - 30;

	Player().Player_HP_Remain.Location[0] = Player().Player_HP.Location[0] - Player().Player_HP.Length[0] / 2 + 78;
	Player().Player_HP_Remain.Location[1] = Player().Player_HP.Location[1] + 3;


	Player().Player_HP_Remain.Length = { Player().HP_Gauge , 6 };


	Player().Player_HP_Remain.Draw();
	Player().Player_HP.Draw();

	//if (Player().Hp > 0)
	//{
	//	Player().Player_HP_Remain.Draw();
	//	Player().Player_HP.Draw();
	//}
}

void EGameManager::DrawPlayerPotions()
{
	for (int i = 0; i < Player().Health_Bottles; i++)
	{
		Player().HP_Potion_Full.Location[0] = Player().Player_HP_Remain.Location[0] + i * snap_Potions + 10;
		Player().HP_Potion_Full.Location[1] = Player().Player_HP_Remain.Location[1] - 20;
		Player().HP_Potion_Full.Draw();
	}

	for (int i = 0; i < Player().max_Bottles - Player().Health_Bottles; i++)
	{
		Player().HP_Potion_Empty.Location[0] = Player().Player_HP_Remain.Location[0] + (Player().max_Bottles * snap_Potions + 10) + ((i + 1) * snap_Potions * -1);
		Player().HP_Potion_Empty.Location[1] = Player().Player_HP_Remain.Location[1] - 20;
		Player().HP_Potion_Empty.Draw();
	}
}

void EGameManager::DrawPlayerSoul()
{
	Player().PlayerSoul.Location[0] = Camera.Location[0] + Camera.Length[0] / 2 - 50;
	Player().PlayerSoul.Location[1] = Camera.Location[1] + Camera.Length[1] / 2 - 30;
	Player().PlayerSoul.Draw();

	space = "  ";

	const char* text_soul = (space.append(std::to_string(static_cast<int>(Player().soul)))).c_str();



	GetClientRect(hwnd, &rt);

	if (Input::Get::Key::Press(0x12))
	{
		isAlt = true;

		if (Input::Get::Key::Down(0x0D) && isAlt)
		{
			windowed *= -1;
		}
		if (Input::Get::Key::Up(0x0D))
		{
			isAlt = false;
		}
	}

	if (windowed == 1)
	{
		Player().Text_Soul_Amount.Location = { rt.right - 100, rt.top + 60 };
		Player().Text_Soul_Amount.Font.Size = 30;
	}

	if (windowed == -1)
	{
		Player().Text_Soul_Amount.Location = { rt.right - 152, rt.top + 90 };
		Player().Text_Soul_Amount.Font.Size = 50;
	}

	//printf("windowed : %d \n", windowed);
	//Player().Text_Soul_Amount.Location = { rt.right - 150, rt.top + 60 };
	//printf("rt.right : %.lf \n", Player().PlayerSoul.Location[0]);

	Player().Text_Soul_Amount.str = text_soul;
	Player().Text_Soul_Amount.Draw();
}

void EGameManager::BossHpBar()
{
	if (Scene_Num == 4)
	{
		if (Boss().Hp > 0)
		{


			if (!Player().isAtBossStage)
			{
				if (Player().GetActorLocation()[0] >= -406)
				{
					Player().isAtBossStage = true;
				}
			}

			if (Player().isAtBossStage)
			{
				Boss().Boss_HP_Remain.Draw();
				Boss().Boss_HP_Bar.Draw();

				Boss().Boss_Name.Location = { 680, 650 };
				Boss().Boss_Name.Draw();
			}
		}
	}
}

void EGameManager::Update()
{
	if (Now != "MapEditor")
	{
		BS->Update();

		Camera.Set();

		//고쳐야됨
		playerLocation = BS->GetPlayerLocation();
		Camera.Location = playerLocation;

		Camera.Location[1] = playerLocation[1] + Player_Ypos;

		if (!BS->isRendering)
			BeforePlayer.Draw();


		vector<2> const min[2]
		{
			playerLocation - BS->GetPlayerScale() / 2,
			Background.Location - Background.Length / 2 ,
		};

		vector<2> const max[2]
		{
			playerLocation + BS->GetPlayerScale() / 2,
			Background.Location + Background.Length / 2 ,
		};


		if (min[0][0] <= min[1][0]) BS->SetLocation(playerLocation + vector<2>(3, 0));
		if (min[0][1] <= min[1][1]) BS->SetLocation(playerLocation + vector<2>(0, 3));
		if (max[0][0] >= max[1][0]) BS->SetLocation(playerLocation - vector<2>(3, 0));
		//if (max[0][1] >= max[1][1]) Player->SetLocation(playerLocation - vector<2>(0, 3));


		if (playerLocation[0] <= min[1][0] + Camera.Length[0] / 2)       Camera.Location[0] = min[1][0] + Camera.Length[0] / 2;
		if (playerLocation[1] <= min[1][1] + Camera.Length[1] / 2 - 80)  Camera.Location[1] = min[1][1] + Camera.Length[1] / 2;
		if (playerLocation[0] >= max[1][0] - Camera.Length[0] / 2)       Camera.Location[0] = max[1][0] - Camera.Length[0] / 2;
		if (playerLocation[1] >= max[1][1] - Camera.Length[1] / 2 - 80)  Camera.Location[1] = max[1][1] - Camera.Length[1] / 2;


		if (Player().P_Anim.RGBA[0] != 0)
		{
			DrawPlayerHpBar();
			DrawPlayerPotions();
			DrawPlayerSoul();

			BossHpBar();
		}


		if (isSceneChanged) // 씬 전환시 Parrallax 때문에
		{
			Pre_cameraPos = { Camera.Location }; // parrallax용
			isSceneChanged = false;
		}

	}
}






