#pragma once
#include "Engine/Game.h"

class Game : public Engine::Game
{
	virtual void Start()  override;
	virtual bool Update() override;
	virtual void End()    override;
};

