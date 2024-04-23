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

	std::map<std::string, AMonster*> Monsters; // ���� BattleSys�� �������� ���� + Scene���� ���� ��ġ����
    vector<2> Scenes_StartPos;                 // �÷��̾� �������� (Warp �Ҷ�����)

	bool isParrallax_On;
	bool Release = true;

protected :

	vector<2> parallaxAmount;

	Image Background;
	Image BeforePlayer;

	int   layer_Size = 0;


};