#pragma once
#include <map>
#include <string>
#include <algorithm>

//#include "Actor/Actor.h"
#include "BattleSystem/BattleSystem.h"

#define GameManager EGameManager::GetGameManager()

#define Animation Rendering::Animation::Component
#define Image     Rendering::Image::Component

#include "Scene/Stage1/Scene1.h"
#include "Scene/Stage1/Scene2.h"
#include "Scene/Stage1/Scene3.h"
#include "Scene/Stage1/Scene4.h"

#include "MapEditor/MapEditor.h"




class EGameManager final
{
private:
	std::map<std::string, class Scene*> Scenes;
	std::string Now = "";

	Image Background;
	Image BeforePlayer;

	RECT rt;
	HWND hwnd;
	int windowed = 1;
	bool isAlt = false;


	vector<2> Pre_PlayerPos;
	bool isSceneChanged = false;

private:
	EGameManager();
	~EGameManager();
public:
	int Scene_Num = 1;
	BattleSystem* BS;

	vector<2> playerLocation;
	vector<2> Pre_cameraPos;
	Rendering::Camera Camera;
	void Init();
	void ChangeScene(std::string SceneName);
	void Update();
	vector<2> GetCameraMovement(); // 카메라 움직임




public:
	static EGameManager* GetGameManager()
	{
		static EGameManager* manager = new EGameManager;
		return manager;
	}

	static void DeleteGameManager()
	{
		delete GetGameManager();
	}

public:


public:
	__forceinline Scene* GetNowScene() const
	{
		return Scenes.at(Now);
	}

	void DrawPlayerHpBar();
	void DrawPlayerPotions();
	void DrawPlayerSoul();

	void BossHpBar();

	float GetPercentage();
	float GetBossPercentage();

	int snap_Potions = 20;
	std::string space;
};






//vector<2> GetCameraLerp(APlayer* player)
//{
//	vector<2> movement = player->GetActorLocation() - Pre_PlayerPos;
//	Pre_PlayerPos = player->GetActorLocation();
//	//if (movement[0] == 0 && movement[1] == 0) return;

//	return movement;
//}