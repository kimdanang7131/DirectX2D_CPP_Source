#pragma once
#include "Actor/Actor.h"


class AAI : public AActor
{
public :
	AAI();
	virtual ~AAI() = default;

	virtual void Start() override;
	virtual void Update() override;
	virtual void End() override;

private :
	//void Behaivor(float radius);

public:
	Animation Anim;
	vector<2> location = { 0 , 0 };
	bool bSucessed = true;


	float Hp;
	int soul;

};

