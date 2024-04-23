#include "stdafx.h"
#include "Scene/Stage1/Scene4.h"

 #define B_WIDTH  4600 / 3
 #define B_HEIGHT 1700 / 3

void Scene4::Start()
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

#pragma region Layers
    Background   = { "SCENE4/AfterPlayer" ,   { B_WIDTH  , B_HEIGHT } };
    Layer[0]     = { "SCENE4/BackLayer1"  ,   { B_WIDTH  , B_HEIGHT } };
    Layer[1]     = { "SCENE4/BackLayer2"  ,   { B_WIDTH  , B_HEIGHT } };
    Layer[2]     = { "SCENE4/BackLayer3"  ,   { B_WIDTH  , B_HEIGHT } };
    Layer[3]     = { "SCENE4/BackLayer4"  ,   { B_WIDTH  , B_HEIGHT } };
    Layer[4]     = { "SCENE4/BackLayer5"  ,   { B_WIDTH  , B_HEIGHT } };
    BeforePlayer = { "SCENE4/BeforePlayer",   { B_WIDTH  , B_HEIGHT } };

    Layer[0].Location = { - 70,-20 };
    Layer[1].Location = { - 90,-20 };
    Layer[2].Location = { -110,0 };
    Layer[3].Location = { -130,0 };
    Layer[4].Location = { -130,0 };

    layer_Size = sizeof(Layer) / sizeof(Image); // 플레이어 시작위치
#pragma endregion 

#pragma region Floor_Cols -> for 왜 안됨?
     Floor_Images[0] = { "Col/Floor" , { 485.6, 60.0 } , { 0.0f , 0.0f , 0.0 } , { -504.3, -199.3 }, 1.0f };
     Floor_Images[1] = { "Col/Floor" , { 505.2, 60.0 } , { 0.0f , 0.0f , 0.0 } , { 514.0, -199.3 }, 1.0f };
     Floor_Images[2] = { "Col/Floor" , { 307.3, 60.0 } , { 0.0f , 0.0f , 0.0 } , { 2.5, -164.4 }, 1.0f };
     Floor_Images[3] = { "Col/Floor" , { 130.8, 60.0 } , { 0.0f , 0.0f , -18.0 } , { 206.7, -183.0 }, 1.0f };
     Floor_Images[4] = { "Col/Floor" , { 133.0, 60.0 } , { 0.0f , 0.0f , 17.0 } , { -202.0, -182.3 }, 1.0f };



    Floor.push_back(Floor_Images[0]);
    Floor.push_back(Floor_Images[1]);
    Floor.push_back(Floor_Images[2]);
    Floor.push_back(Floor_Images[3]);
    Floor.push_back(Floor_Images[4]);

#pragma endregion

#pragma region Wall_Cols
    Wall_Images[0] = { "Col/Wall" , { 69.5, 465.9 } , { 0.0f , 0.0f , 0.0 } , { -680.0, 50.3 }, 1.0f };
    Wall_Images[1] = { "Col/Wall" , { 69.5, 465.9 } , { 0.0f , 0.0f , 0.0 } , { 693.2, 50.3 }, 1.0f };

    Wall.push_back(Wall_Images[0]);
    Wall.push_back(Wall_Images[1]);


#pragma endregion

#pragma region AMonster
    AMonster* E1 = new AMonster;
    E1->M_Anim = E1->Elder_Idle_A;
    E1->SetLocation({ 84,20 });

    E1->Hp = 1000;
    E1->full_HP = 1000;
    E1->soul = 2000;
    E1->attkDmg = 70;
    // 둘중 하나
    E1->StartPos_Y = 20;

    Monsters.insert({ "Elder" , E1 });
#pragma endregion 

    Scenes_StartPos = { -611,-119 }; // 플레이어 시작위치
}


bool Scene4::Update()
{
    if (!GameManager->BS->isRendering)
    {
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
    }


#pragma region Parrallax(시차 원근법)
    if (isParrallax_On)
    {
        parallaxAmount = GameManager->GetCameraMovement();

        // 곱하는게 적을수록 멀어서 잘 안움직이는 느낌
        Layer[0].Location[0] += parallaxAmount[0] * 0.16f;
        Layer[0].Location[1] += parallaxAmount[1] * 0;

        Layer[1].Location[0] += parallaxAmount[0] * 0.18f;
        Layer[1].Location[1] += parallaxAmount[1] * 0;

        Layer[2].Location[0] += parallaxAmount[0] * 0.2f;
        Layer[2].Location[1] += parallaxAmount[1] * 0;

        Layer[3].Location[0] += parallaxAmount[0] * 0.3f;
        Layer[3].Location[1] += parallaxAmount[1] * 0;

        Layer[4].Location[0] += parallaxAmount[0] * 0.35f;
        Layer[4].Location[1] += parallaxAmount[1] * 0;
    }


#pragma endregion  


#pragma region 텍스트 / AI
    //Text.Draw();
    //for (int i = 0; i < 3; ++i)
    //    if (AI[i]) AI[i]->Update();
#pragma endregion
    return true;
}

void Scene4::DebugCollider()
{
    Release = false;
}
void Scene4::DrawCollider()
{
    Release = true;
}

void Scene4::End()
{
    //for (int i = 0; i < 3; ++i)
    //    if (AI[i]) delete AI[i];
}

