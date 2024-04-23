#pragma once
#include "Engine/Rendering.h"
#include "CollisionManager/Collision.h"


class Scene abstract
{
	friend class EGameManager;
public :
	virtual void Start()  abstract;
	virtual bool Update() abstract;
	virtual void End()    abstract;

	virtual void DebugCollider() abstract;
	virtual void DrawCollider() abstract;

	Collisions::NonInterative noninter_Cols;
	Collisions::Interactive      inter_Cols;

	std::map<std::string, AMonster*> Monsters; // 몬스터 BattleSys로 가져가기 위해 + Scene에서 몬스터 위치설정
    vector<2> Scenes_StartPos;                 // 플레이어 시작지점 (Warp 할때마다)

	bool isParrallax_On;
	bool Release = true;

protected :

	vector<2> parallaxAmount;

	Image Background;
	Image BeforePlayer;

	int   layer_Size = 0;


};