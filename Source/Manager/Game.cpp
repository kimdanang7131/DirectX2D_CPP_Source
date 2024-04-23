#include "stdafx.h"
#include "Game.h"

void Game::Start()
{
    srand(static_cast<unsigned>(GetTickCount64()));
    GameManager;
    GameManager->Init();
}

bool Game::Update()
{
    if (GameManager->GetNowScene()->Update())
    {
        GameManager->Update();

        return true;
    }
    {
        return false;
    }
}

void Game::End()
{ GameManager->DeleteGameManager();  }

Engine::Game* Engine::Init()
{ return new ::Game; }