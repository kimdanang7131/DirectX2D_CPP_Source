#include "stdafx.h"
#include "Scene/Stage1/Scene2.h"

#define B_WIDTH  6636 / 3
#define B_HEIGHT 1500 / 3

void Scene2::Start()
{
#pragma region CollisionÃÊ±âÈ­
    Floor.clear();
    Wall.clear();
    Warp.clear();
    Ladder.clear();
    Hang.clear();
    Floor_Down.clear();

#pragma endregion

#pragma region BGM / AIµî·Ï / Text
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
     Text = { "Scene2", { "HS°Ü¿ï´«²ÉÃ¼2.0" , 50 }, { 255, 255, 255 }, { 100, 50 } };
#pragma endregion

#pragma region Layers
    Background   = { "SCENE2/AfterPlayer" ,   { B_WIDTH  , B_HEIGHT } };
    Layer[0]     = { "SCENE2/BackLayer1"  ,   { B_WIDTH  , B_HEIGHT } };
    Layer[1]     = { "SCENE2/BackLayer2"  ,   { B_WIDTH  , B_HEIGHT } };
    Layer[2]     = { "SCENE2/BackLayer3"  ,   { B_WIDTH  , B_HEIGHT } };
    Layer[3]     = { "SCENE2/BackLayer4"  ,   { B_WIDTH  , B_HEIGHT } };
    Layer[4]     = { "SCENE2/BackLayer5"  ,   { B_WIDTH  , B_HEIGHT } };
    BeforePlayer = { "SCENE2/BeforePlayer",   { B_WIDTH  , B_HEIGHT } };

    Layer[0].Location = { -20 };
    Layer[1].Location = { -20 };
    Layer[2].Location = { -20 };

    Layer[3].Location = { -200 };
    Layer[4].Location = { -200 };

    layer_Size = sizeof(Layer) / sizeof(Image); // ÇÃ·¹ÀÌ¾î ½ÃÀÛÀ§Ä¡
#pragma endregion 

#pragma region Floor_Cols -> for ¿Ö ¾ÈµÊ?
    Floor_Images[0]  = { "Col/Floor" , { 468.7, 60.6 }  , { 0.0f , 0.0f , 0.0 } , { -867.4, -54.5 }, 1.0f };
    Floor_Images[1]  = { "Col/Floor" , { 173.4, 60.6 }  , { 0.0f , 0.0f , 0.0 } , { -582.9, 18.8 }, 1.0f };
    Floor_Images[2]  = { "Col/Floor" , { 250, 18.8 }  , { 0.0f , 0.0f , 0.0 } , { -398.6, 114.4 }, 1.0f };
    Floor_Images[3]  = { "Col/Floor" , { 555, 18.8 }  , { 0.0f , 0.0f , 0.0 } , { 366.9, 114.4 }, 1.0f };
    Floor_Images[4]  = { "Col/Floor" , { 154.1, 18.8 }  , { 0.0f , 0.0f , 0.0 } , { 766.9, 114.4 }, 1.0f };
    Floor_Images[5]  = { "Col/Floor" , { 108.8, 18.8 }  , { 0.0f , 0.0f , 0.0 } , { -146.0, 114.4 }, 1.0f };
    Floor_Images[6]  = { "Col/Floor" , { 655.5, 38.8 }  , { 0.0f , 0.0f , 0.0 } , { -94.4, -116.7 }, 1.0f };
    Floor_Images[7]  = { "Col/Floor" , { 655.5, 38.8 }  , { 0.0f , 0.0f , 0.0 } , { 767.8, -116.7 }, 1.0f };
    Floor_Images[8]  = { "Col/Floor" , { 174.3, 31.4 }  , { 0.0f , 0.0f , 0.0 } , { 394.4, -35.1 }, 1.0f };
    Floor_Images[9]  = { "Col/Floor" , { 80.8, 21.4 }   , { 0.0f , 0.0f , 0.0 } , { 596.4, 41.5 }, 1.0f };

  

   
    Floor.push_back(Floor_Images[0]);
    Floor.push_back(Floor_Images[1]);
    Floor.push_back(Floor_Images[2]);
    Floor.push_back(Floor_Images[3]);
    Floor.push_back(Floor_Images[4]);
    Floor.push_back(Floor_Images[5]);
    Floor.push_back(Floor_Images[6]);
    Floor.push_back(Floor_Images[7]);
    Floor.push_back(Floor_Images[8]);
    Floor.push_back(Floor_Images[9]);


    //for (int i = 0; i < 10; i++)
    //{
    //    Floor.push_back(Floor_Images[i]);
    //}
#pragma endregion

#pragma region Wall_Cols
    Wall_Images[0] = { "Col/Wall" , { 40.0, 300.0 } , { 0.0f , 0.0f , 0.0 } , { -1090.0, 100.0 }, 1.0f };
    Wall_Images[1] = { "Col/Wall" , { 28.3, 120.0 } , { 0.0f , 0.0f , 0.0 } , { -651.1, -16.9 }, 1.0f };
    Wall_Images[2] = { "Col/Wall" , { 40.0, 240.0 } , { 0.0f , 0.0f , 0.0 } , { -391.0, -3.8 }, 1.0f };
    Wall_Images[3] = { "Col/Wall" , { 40.0, 240.0 } , { 0.0f , 0.0f , 0.0 } , { 204.2, -3.8 }, 1.0f };
    Wall_Images[4] = { "Col/Wall" , { 40.0, 240.0 } , { 0.0f , 0.0f , 0.0 } , { 321.3, -3.8 }, 1.0f };
    Wall_Images[5] = { "Col/Wall" , { 40.0, 120.0 } , { 0.0f , 0.0f , 0.0 } , { 459.3, -85.8 }, 1.0f };
    Wall_Images[6] = { "Col/Wall" , { 70.0, 323.4 } , { 0.0f , 0.0f , 0.0 } , { 664.1, 101.3 }, 1.0f };
    Wall_Images[7] = { "Col/Wall" , { 40.0, 390.0 } , { 0.0f , 0.0f , 0.0 } , { 1040.0, 60.0 }, 1.0f };
    Wall_Images[8] = { "Col/Wall" , { 30.0, 167.6 } , { 0.0f , 0.0f , 0.0 } , { 1005.0, 171.2 }, 1.0f };
    Wall_Images[9] = { "Col/Wall" , { 40.8, 98.5 } , { 0.0f , 0.0f , 0.0 } , { -500.7, 69.6 }, 1.0f };

    //Wall.clear();
    Wall.push_back(Wall_Images[0]);
    Wall.push_back(Wall_Images[1]);
    Wall.push_back(Wall_Images[2]);
    Wall.push_back(Wall_Images[3]);
    Wall.push_back(Wall_Images[4]);
    Wall.push_back(Wall_Images[5]);
    Wall.push_back(Wall_Images[6]);
    Wall.push_back(Wall_Images[7]);
    Wall.push_back(Wall_Images[8]);
    Wall.push_back(Wall_Images[9]);

#pragma endregion

#pragma region Warp_Cols
    //Warp_Images[0] = { "Col/Warp" , { 40.0, 90.0 } , { 0.0f , 0.0f , 0.0 } , { -1052.1, 21.6 }, 1.0f };
    Warp_Images[0] = { "Col/Warp" , { 40.0, 90.0 } , { 0.0f , 0.0f , 0.0 } , { 1010.0, -50.0 }, 1.0f };

    //Warp.push_back(Warp_Images[1]);
    Warp.push_back(Warp_Images[0]);
#pragma endregion 

#pragma region Ladder_Cols

    Ladder_Images[0] = { "Col/Ladder" , { 25.5, 222 } , { 0.0f , 0.0f , 0.0 } , { -328.2, 14 }, 1.0f };
    Ladder_Images[1] = { "Col/Ladder" , { 25.5, 222 } , { 0.0f , 0.0f , 0.0 } , { 141.7, 14 }, 1.0f };

    Ladder.push_back(Ladder_Images[0]);
    Ladder.push_back(Ladder_Images[1]);
#pragma endregion 

#pragma region Hang_Cols

    Hang_Images[0] = { "Col/Hang_Col" , { 20.1, 10.0 } , { 0.0f , 0.0f , 0.0 } , { -194.4, 120.9 }, 1.0f };
    Hang_Images[1] = { "Col/Hang_Col" , { 20.1, 10.0 } , { 0.0f , 0.0f , 0.0 } , { -282.0, 120.9 }, 1.0f };
    Hang_Images[2] = { "Col/Hang_Col" , { 20.1, 10.0 } , { 0.0f , 0.0f , 0.0 } , { -100.5, 120.9 }, 1.0f };
    Hang_Images[3] = { "Col/Hang_Col" , { 20.1, 10.0 } , { 0.0f , 0.0f , 0.0 } , { 95.6, 120.9 }, 1.0f };
    Hang_Images[4] = { "Col/Hang_Col" , { 20.1, 10.0 } , { 0.0f , 0.0f , 0.0 } , { 563.6, 47.8 }, 1.0f };

    //RectAngle_Collisions[0] = { "Col/Hang_Col" , { 20.1, 10.0 } , { 0.0f , 0.0f , 0.0 } , { -194.4, 120.9 }, 1.0f };
    //RectAngle_Collisions[1] = { "Col/Hang_Col" , { 20.1, 10.0 } , { 0.0f , 0.0f , 0.0 } , { -282.0, 120.9 }, 1.0f };
    //RectAngle_Collisions[2] = { "Col/Hang_Col" , { 20.1, 10.0 } , { 0.0f , 0.0f , 0.0 } , { -100.5, 120.9 }, 1.0f };
    //RectAngle_Collisions[3] = { "Col/Hang_Col" , { 20.1, 10.0 } , { 0.0f , 0.0f , 0.0 } , { 95.6, 120.9 }, 1.0f };
    //RectAngle_Collisions[4] = { "Col/Hang_Col" , { 20.1, 10.0 } , { 0.0f , 0.0f , 0.0 } , { 563.6, 47.8 }, 1.0f };
    Hang.push_back(Hang_Images[0]);
    Hang.push_back(Hang_Images[1]);
    Hang.push_back(Hang_Images[2]);
    Hang.push_back(Hang_Images[3]);
    Hang.push_back(Hang_Images[4]);

#pragma endregion

#pragma region Floor_Down_Cols

    Floor_Down_Images[0] = { "Col/Floor_Down" , { 73.5, 23.0 } , { 0.0f , 0.0f , 0.0 } , { -312.6, 116.9 }, 1.0f };
    Floor_Down_Images[1] = { "Col/Floor_Down" , { 107.6, 23.0 } , { 0.0f , 0.0f , 0.0 } , { -146.2, 116.2 }, 1.0f };
    Floor_Down_Images[2] = { "Col/Floor_Down" , { 69.3, 23.0 } , { 0.0f , 0.0f , 0.0 } , { 591.4, 43.3 }, 1.0f };
    Floor_Down_Images[3] = { "Col/Floor_Down" , { 80, 25.4 } , { 0.0f , 0.0f , 0.0 } , { 125, 116.9 }, 1.0f };
    Floor_Down_Images[4] = { "Col/Floor_Down" , { 273.3, 25.4 } , { 0.0f , 0.0f , 0.0 } , { 490, 116.9 }, 1.0f };

    Floor_Down.push_back(Floor_Down_Images[0]);
    Floor_Down.push_back(Floor_Down_Images[1]);
    Floor_Down.push_back(Floor_Down_Images[2]);
    Floor_Down.push_back(Floor_Down_Images[3]);
    Floor_Down.push_back(Floor_Down_Images[4]);

#pragma endregion 

#pragma region AMonster

    AMonster* S1 = new AMonster;
    S1->M_Anim = S1->LionHead_Idle_A;
    S1->walkCount = 5;
    S1->walkSpd = 60;
    S1->SetLocation({ -150  , -30 });
    S1->Hp = 500;
    S1->full_HP = 500;
    S1->soul = 200;
    S1->attkDmg = 50;
    Monsters.insert({ "LionHead" , S1 });

    AMonster* S2 = new AMonster;
    S2->M_Anim = S2->Shield_Idle_A;
    S2->walkCount = 3;
    S2->walkSpd = 60;
    S2->SetLocation({ 271  ,174 });
    S2->Hp = 200;
    S2->full_HP = 200;
    S2->soul = 50;
    S2->attkDmg = 20;

    Monsters.insert({ "Shield1" , S2 });


    //¹Ì­k´Ù
    AMonster* S3 = new AMonster;
    S3->M_Anim = S3->Shield_Idle_A;
    S3->walkCount = 3;
    S3->walkSpd = 60;
    S3->SetLocation({ -809  , 26 });
    S3->Hp = 200;
    S3->full_HP =200;
    S3->soul = 50;
    S3->attkDmg = 20;

    Monsters.insert({ "Shield2" , S3 });

    AMonster* S4 = new AMonster;
    S4->M_Anim = S4->Foil_Idle_A;

    S4->SetLocation({ 270  ,180 });
    S4->Hp = 200;
    S4->full_HP = 200;
    S4->soul = 150;
    S4->attkDmg = 30;

    Monsters.insert({ "Foil" , S4 });

    //AMonster* S4 = new AMonster;
    //S4->M_Anim = S4->Shield_Idle_A;
    //S4->walkCount = 3;
    //S4->walkSpd = 60;
    ////S2->SetLocation({ -760  , 26 });
    //S4->SetLocation({ -760  , 26 });
    //S4->Hp = 250;
    //S4->soul = 50;
    //S4->attkDmg = 20;
    //Monsters.insert({ "Shield4" , S4 });
#pragma endregion 



    Scenes_StartPos = { -985,26 }; // ÇÃ·¹ÀÌ¾î ½ÃÀÛÀ§Ä¡
}


bool Scene2::Update()
{
    //if (Input::Get::Key::Down(VK_F12))
    //    GameManager->ChangeScene("Scene1");


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


#pragma region Parrallax(½ÃÂ÷ ¿ø±Ù¹ý)
    if (isParrallax_On)
    {
        parallaxAmount = GameManager->GetCameraMovement();

        // °öÇÏ´Â°Ô ÀûÀ»¼ö·Ï ¸Ö¾î¼­ Àß ¾È¿òÁ÷ÀÌ´Â ´À³¦
        Layer[0].Location[0] += parallaxAmount[0] * 0.15f;
        Layer[0].Location[1] += parallaxAmount[1] * 0;
                                                    
        Layer[1].Location[0] += parallaxAmount[0] * 0.3f;
        Layer[1].Location[1] += parallaxAmount[1] * 0;
                                                    
        Layer[2].Location[0] += parallaxAmount[0] * 0.4f;
        Layer[2].Location[1] += parallaxAmount[1] * 0;
                                                    
        Layer[3].Location[0] += parallaxAmount[0] * 0.5f;
        Layer[3].Location[1] += parallaxAmount[1] * 0.2f;

        Layer[4].Location[0] += parallaxAmount[0] * 0.55f;
        Layer[4].Location[1] += parallaxAmount[1] * 0.3f;
    }

 
#pragma endregion  


#pragma region ÅØ½ºÆ® / AI
    Text.Draw();
    //for (int i = 0; i < 3; ++i)
    //    if (AI[i]) AI[i]->Update();
#pragma endregion
    return true;
}


void Scene2::DebugCollider()
{
    Release = false;
}
void Scene2::DrawCollider()
{
    Release = true;
}

void Scene2::End()
{
    //for (int i = 0; i < 3; ++i)
    //    if (AI[i]) delete AI[i];
}

