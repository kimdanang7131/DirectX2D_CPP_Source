#pragma once
#include "Scene/Scene.h"
#include "Actor/Player/Player.h"
#include "Actor/AI/AI.h"

#define Floor       noninter_Cols.Floor_Col
#define Wall        noninter_Cols.Wall_Col
#define Hang        noninter_Cols.Hang_Col
#define Floor_Down  noninter_Cols.Floor_Down_Col

#define Warp        inter_Cols.Warp_Col
#define Ladder      inter_Cols.Ladder_Col

class Scene3 : public Scene
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

	// ¼öÁ¤
	Image Layer[4];
	Image Floor_Images[1];
	Image Wall_Images[2];
	Image Floor_Down_Images[1];
	Image Warp_Images[1];
	Image Alter;
};
