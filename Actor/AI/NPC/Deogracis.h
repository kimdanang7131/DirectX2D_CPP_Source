#pragma once
#include "Actor/AI/AI.h"

class Deogracis : public AAI
{
public:
	Deogracis();
	virtual ~Deogracis() = default;

	virtual void Start() override;
	virtual void Update() override;
	virtual void End() override;

private:

public:
	Animation Anim;
	vector<2> location = { 0 , 0 };
	bool bSucessed = true;
};

