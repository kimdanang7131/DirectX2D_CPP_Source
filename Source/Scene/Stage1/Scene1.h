#pragma once
#include "Scene/Scene.h"

#define Floor noninter_Cols.Floor_Col
#define Wall  noninter_Cols.Wall_Col


#define Warp     inter_Cols.Warp_Col

class Scene1 : public Scene
{
public :
	virtual void Start()  override;
	virtual bool Update() override;
	virtual void End()    override;

	virtual void DebugCollider() override;
	virtual void DrawCollider() override;
private :
	Sound::Sound BGM;
	Rendering::Text::Component Text;

	Image Layer[3];
	Image Floor_Images[5];
	Image Wall_Images[3];

	Image Warp_Images[1];
};

