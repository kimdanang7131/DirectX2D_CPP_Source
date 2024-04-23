#include "stdafx.h"
#include "Scene/Stage1/Scene1.h"

#define B_WIDTH  8000 / 3
#define B_HEIGHT 4280 / 3


void Scene1::Start()
{
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

    //Text = { "Scene1", { "HS겨울눈꽃체2.0" , 50 }, { 255, 255, 255 }, { 100, 50 } };
#pragma endregion

#pragma region Layers
    Background   = { "SCENE1/AfterPlayer" ,   { B_WIDTH  , B_HEIGHT }};
    Layer[0]     = { "SCENE1/BackLayer1"  ,   { B_WIDTH  , B_HEIGHT }};
    Layer[1]     = { "SCENE1/BackLayer2"  ,   { B_WIDTH  , B_HEIGHT }};
    Layer[2]     = { "SCENE1/BackLayer3"  ,   { B_WIDTH  , B_HEIGHT }};
    BeforePlayer = { "SCENE1/BeforePlayer",   { B_WIDTH  , B_HEIGHT }};


    Layer[0].Location = { 0,-20 };

    layer_Size = sizeof(Layer) / sizeof(Image);

#pragma endregion 

#pragma region Floor_Cols
    Floor_Images[0] = { "Col/Floor" , { 163.1 , 42.4 } , { 0.0f , 0.0f ,   0.0 }    , { -357.2, -115.3 }, 1.0f };
    Floor_Images[1] = { "Col/Floor" , { 106.7 , 42.4 } , { 0.0f , 0.0f ,   0.0 }    , { -887.8, -329.7 }, 1.0f };
    Floor_Images[2] = { "Col/Floor" , {  470 , 42.4 } , { 0.0f , 0.0f ,   0.0 }    , {  781.5, -544.9 }, 1.0f };
    Floor_Images[3] = { "Col/Floor" , { 1005.6, 42.4 } , { 0.0f , 0.0f , -27.3 }    , {  129.3, -331.6 }, 1.0f };
    Floor_Images[4] = { "Col/Floor" , { 495.0 , 42.4 } , { 0.0f , 0.0f ,  27.6 }    , { -627.6, -222.6 }, 1.0f };


    Floor.push_back(Floor_Images[0]);
    Floor.push_back(Floor_Images[1]);
    Floor.push_back(Floor_Images[2]);
    Floor.push_back(Floor_Images[3]);
    Floor.push_back(Floor_Images[4]);

    //for (int i = 0; i < Floor.size(); i++)
    //{
    //    Floor.push_back(Floor[i]);
    //}
#pragma endregion

#pragma region Wall_Cols
    Wall_Images[0] = { "Col/Wall" , { 100.0, 1060.0 } , { 0.0f , 0.0f , 0.0 } , { -980.0, 180.0 }, 1.0f };
    Wall_Images[1] = { "Col/Wall" , { 100.0, 1060.0 } , { 0.0f , 0.0f , 0.0 } , { 990.0, 190.0 }, 1.0f };
    Wall_Images[2] = { "Col/Wall" , { 70.0, 280.0 } , { 0.0f , 0.0f , 0.0 } , { 1000.0, -420.0 }, 1.0f };


    Wall.push_back(Wall_Images[0]);
    Wall.push_back(Wall_Images[1]);
    Wall.push_back(Wall_Images[2]);
#pragma endregion

    Warp_Images[0] = { "Col/Warp" , { 48.8, 88.1 } , { 0.0f , 0.0f , 0.0 } , { 957.8, -480.0 }, 1.0f };

    Warp.push_back(Warp_Images[0]);
Scenes_StartPos = { -358, -44 }; // 플레이어 시작위치
}


bool Scene1::Update()
{

    //if (GameManager->isSceneChanged)
    //{
    //    GameManager->ChangeScene("Scene2");
    //}
    for (int i = layer_Size - 1; i >= 0; i--)
    {
        Layer[i].Draw();
    }

    Background.Draw();



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
    }

#pragma region Parrallax(시차 원근법)
    if(isParrallax_On)
    {
        parallaxAmount = GameManager->GetCameraMovement();
        // 곱하는게 적을수록 멀어서 잘 안움직이는 느낌
        Layer[0].Location[0] += parallaxAmount[0] * 0.35f;
        Layer[0].Location[1] += parallaxAmount[1] * 0.2f;

        Layer[1].Location[0] += parallaxAmount[0] * 0.8f;
        Layer[1].Location[1] += parallaxAmount[1] * 0.7f;

        Layer[2].Location[0] += parallaxAmount[0] * 0.7f;
        Layer[2].Location[1] += parallaxAmount[1] * 0.65f;
    }
#pragma endregion  

#pragma region 텍스트 / AI
    // Text.Draw();
    // AI Update
    //for (int i = 0; i < 3; ++i)
    //    if (AI[i]) AI[i]->Update();
#pragma endregion 
    return true;
}

void Scene1::End()
{

    // AI End(0
    //for (int i = 0; i < 3; ++i)
    //    if (AI[i]) delete AI[i];
}

void Scene1::DebugCollider()
{
    Release = false;
}
void Scene1::DrawCollider()
{
    Release = true;
}

