#pragma once
#include "Scene/Scene.h"
#include "Actor/Player/Player.h"
#include "Actor/AI/MONSTER/Monster.h"

#define Floor       noninter_Cols.Floor_Col
#define Wall        noninter_Cols.Wall_Col
#define Hang        noninter_Cols.Hang_Col
#define Floor_Down  noninter_Cols.Floor_Down_Col

#define Warp        inter_Cols.Warp_Col
#define Ladder      inter_Cols.Ladder_Col

class Scene4 : public Scene
{
public:
	virtual void Start()  override;
	virtual bool Update() override;
	virtual void End()    override;

	virtual void DebugCollider() override;
	virtual void DrawCollider() override;

private:
	Sound::Sound BGM;
	Rendering::Text::Component Text;

	Image Layer[5];
	Image Floor_Images[5];
	Image  Wall_Images[2];

	//Image Warp_Images[1];

};

