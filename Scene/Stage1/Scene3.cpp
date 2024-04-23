#include "stdafx.h"
#include "Scene/Stage1/Scene3.h"

// 수정
#define B_WIDTH  5200 / 3
#define B_HEIGHT 1400 / 3

void Scene3::Start()
{
#pragma region Collision초기화
    Floor.clear();
    Wall.clear();
    Warp.clear();
    Ladder.clear();
    Hang.clear();
    Floor_Down.clear();

#pragma endregion

#pragma region BGM / AI등록 / Text
    //BGM  = { "BGM", 1.0f, true };
    // 
    //BGM.Play();

    //for (int i = 0; i < 3; ++i)
    //{
    //    AI[i] = new AAI;
    //    AI[i]->Start();
    //    AI[i]->Anim.Location[0] +=  i * 200;
    //}
    // 
    // Text = { "Scene2", { "HS겨울눈꽃체2.0" , 50 }, { 255, 255, 255 }, { 100, 50 } };
#pragma endregion

//수정
#pragma region Layers
    Background   = { "SCENE3/AfterPlayer" ,   { B_WIDTH  , B_HEIGHT } };
    Layer[0]     = { "SCENE3/BackLayer1"  ,   { B_WIDTH  , B_HEIGHT } };
    Layer[1]     = { "SCENE3/BackLayer2"  ,   { B_WIDTH  , B_HEIGHT } };
    Layer[2]     = { "SCENE3/BackLayer3"  ,   { B_WIDTH  , B_HEIGHT } };
    Layer[3]     = { "SCENE3/BackLayer4"  ,   { B_WIDTH  , B_HEIGHT } };
    BeforePlayer = { "SCENE3/BeforePlayer",   { B_WIDTH  , B_HEIGHT } };


    layer_Size = sizeof(Layer) / sizeof(Image); // 플레이어 시작위치

    Layer[0].Location = { -30 ,10 };
    Layer[1].Location = { -90, 10 };
    Layer[2].Location = { -70, 30 };
    Layer[3].Location = { -70, 30 };


#pragma endregion 

//수정
#pragma region Floor_Cols -> for 왜 안됨?
      Floor_Images[0] = { "Col/Floor" , { 1740.0, 101.2 } , { 0.0f , 0.0f , 0.0 } , { 0.0, -170.0 }, 1.0f };

      Floor.push_back(Floor_Images[0]);
#pragma endregion

#pragma region Warp_Cols
      Warp_Images[0] = { "Col/Warp" , { 30.4, 140.0 } , { 0.0f , 0.0f , 0.0 } , { 773.1, -44.8 }, 1.0f };

    //Warp.push_back(Warp_Images[1]);
    Warp.push_back(Warp_Images[0]);
#pragma endregion 

#pragma region Wall_Cols
    Wall_Images[0] = { "Col/Wall" , { 57.2, 380.0 } , { 0.0f , 0.0f , 0.0 } , { -801.9, 49.1 }, 1.0f };
    Wall_Images[1] = { "Col/Wall" , { 57.2, 380.0 } , { 0.0f , 0.0f , 0.0 } , { 810.9, 49.1 }, 1.0f };

    Wall.push_back(Wall_Images[0]);
    Wall.push_back(Wall_Images[1]);

#pragma endregion 
    //수정
    Alter = { "Building/Penintent_Alter" , { 122.0, 230.0 } , { 0.0f , 0.0f , 0.0 } , { 504.5, 0.0 }, 1.0f };
    Scenes_StartPos = { -719 , -69 }; // 플레이어 시작위치
}


bool Scene3::Update()
{
    for (int i = layer_Size - 1; i >= 0; i--)
    {
        Layer[i].Draw();
    }
    
    Background.Draw();
    Alter.Draw();
    if (Release)
    {
        for (int i = 0; i < Floor.size(); i++)
        {
            Floor[i].Draw();
        }

        for (int i = 0; i < Wall.size(); i++)
        {
            Wall[i].Draw();
        }

        for (int i = 0; i < Warp.size(); i++)
        {
            Warp[i].Draw();
        }

        for (int i = 0; i < Ladder.size(); i++)
        {
            Ladder[i].Draw();
        }

        for (int i = 0; i < Hang.size(); i++)
        {
            Hang[i].Draw();
        }

        for (int i = 0; i < Floor_Down.size(); i++)
        {
            Floor_Down[i].Draw();
        }
    }


#pragma region Parrallax(시차 원근법)
    if (isParrallax_On)
    {
        parallaxAmount = GameManager->GetCameraMovement();

        // 곱하는게 적을수록 멀어서 잘 안움직이는 느낌
        Layer[0].Location[0] += parallaxAmount[0] * 0.08f;
        Layer[0].Location[1] += parallaxAmount[1] * 0;

        Layer[1].Location[0] += parallaxAmount[0] * 0.25f;
        Layer[1].Location[1] += parallaxAmount[1] * 0;

        Layer[2].Location[0] += parallaxAmount[0] * 0.3f;
        Layer[2].Location[1] += parallaxAmount[1] * 0.3f;

        Layer[3].Location[0] += parallaxAmount[0] * 0.4f;
        Layer[3].Location[1] += parallaxAmount[1] * 0.2f;
    }
#pragma endregion  


#pragma region 텍스트 / AI
    //Text.Draw();
    //for (int i = 0; i < 3; ++i)
    //    if (AI[i]) AI[i]->Update();
#pragma endregion
    return true;
}

void Scene3::DebugCollider()
{
    Release = false;
}
void Scene3::DrawCollider()
{
    Release = true;
}

void Scene3::End()
{
    //for (int i = 0; i < 3; ++i)
    //    if (AI[i]) delete AI[i];
}

