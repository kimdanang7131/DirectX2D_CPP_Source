#include "stdafx.h"
#include "MapEditor/MapEditor.h"
#include <string>

#define B_WIDTH2  5200 / 3
#define B_HEIGHT2 1400 / 3

void MapEditor::Start()
{
    Str = "Col/Floor";
    Vector = &Objects;

    Background = { "SCENE3/AfterPlayer", { B_WIDTH2 ,  B_HEIGHT2  },   0, { 0, 0 } };

    Floor_Collisions.push_back({ "Building/Pried", { 100 , 150 }, { 0 } , { 0 } });
    Wall_Collisions.push_back({ "Building/Penintent_Alter", { 122 , 230 }, { 0 } , { 0 } });
    Text = { "", { "HS겨울눈꽃체2.0" , 50 }, { 255, 255, 255 }, { 640, 50 } };
    SnappingValue = 10.0f;
    Value = 0.01f;
    Type = VectorType::Images;

    Create();
}


bool MapEditor::Update()
{
    GameManager->Camera.Set();

    if (Input::Get::Key::Down(VK_F12))
        GameManager->ChangeScene("Scene1");

       
    // F3 누른채로 F2누르면 터짐
      if (Input::Get::Key::Down(VK_F1)) Create();
      if (Input::Get::Key::Down(VK_F2)) Print();
      if (Input::Get::Key::Down(VK_F3)) ChangeImage();

    ChangeTransform();

    if (Input::Get::Key::Down(0x31))
        bSnapping = bSnapping ? false : true;

    Background.Draw();
    ChangeValue();
    ChangeType();
    TextDraw();


    for (int i = 0; i < Objects.size() - 1; ++i)
        Objects[i].Draw();
    for (int i = 0; i < Floor_Collisions.size() - 1; ++i)
        Floor_Collisions[i].Draw();
    for (int i = 0; i < Wall_Collisions.size() - 1; ++i)
        Wall_Collisions[i].Draw();

    Vector->back().Draw();

    return true;
}



void MapEditor::Create()
{
    switch (Type)
    {
    case VectorType::Images:
    {
        Image prev = { nullptr, { 100 , 100 } };
        if (!Vector->empty())
        {
            prev = Vector->back();
        }
        {
            Vector->push_back(Image{ new char , prev.Length, prev.Angle, prev.Location });
            strcpy_s(const_cast<char*>(Vector->back().Content), Str.size() + 1, Str.c_str());
        }
        return;
    }
    case VectorType::Walls: case VectorType::Floors:
    {
        Image prev = Vector->back();
        Vector->push_back(prev);
        return;
    }
    }
}

bool isCameraMove = false;
static vector<2> minmax[2];
static vector<2> vertex;
int count = 0;

void MapEditor::ChangeTransform()
{
    {
        vector<2> Direction = { 0 , 0 };
        
        if (Input('W'))
            Direction[1] += 1;
        if (Input('S'))
            Direction[1] -= 1;
        if (Input('D'))
            Direction[0] += 1;
        if (Input('A'))
            Direction[0] -= 1;

        Vector->back().Location += normalize(Direction) * GetValue();
    }
    {
        //static POINT MousePos =
        //{
        //   Input::Get::Cursor::X() ,
        //   Input::Get::Cursor::Y() 
        //};
        vector<2> Direction = { 0 , 0 };

        if (Input::Get::Key::Down(VK_LBUTTON))
        {
            isCameraMove = false;
            Direction[0] =      static_cast<float>(Input::Get::Cursor::X() - static_cast <long>(640));
            Direction[1] = -1 * static_cast<float>(Input::Get::Cursor::Y() - static_cast <long>(360));
            //printf("x: %.lf , y: %.lf \n", Direction[0], Direction[1]);
            //printf("length X : %.lf , length Y: %.lf\n", GameManager->Camera.Length[0], GameManager->Camera.Length[1]);

            //GameManager->Camera.Location = Direction;
            vertex = { Direction[0],Direction[1] };

          
            if (count == 0)
            {
                minmax[0] = vertex;
            }
            else if (count == 1)
            {
                minmax[1] = vertex;
            }
           
            count++;

            if (count >= 2) // TAB 눌러서 사각형일때만 하자 
            {
                Vector->back().Length[0] = { abs(minmax[0][0] - minmax[1][0]) };
                Vector->back().Length[1] = { 100 };
               // Vector->back().Angle [2] = {  45 };

                Vector->back().Location[0] = { (minmax[0][0] + minmax[1][0]) / 2 };
                Vector->back().Location[1] = { (minmax[0][1] + minmax[1][1]) / 2 };

                printf("x : [%.lf]  \n", Vector->back().Length[0]);


                count = 0;
            }
        

            printf("min : [%.lf , %.lf] , max : [%.lf , %.lf] \n", minmax[0][0], minmax[0][1], minmax[1][0], minmax[1][1]);

        }
        if (Input::Get::Key::Down(VK_RBUTTON))
        {
            isCameraMove = true;
        }
    }
    {
        if (Input('Q'))
            Vector->back().Angle[2] += GetValue();
        if (Input('E'))
            Vector->back().Angle[2] -= GetValue();
    }
    {
        if (Input(VK_UP))
            Vector->back().Length[1] += GetValue();
        if (Input(VK_DOWN))
            Vector->back().Length[1] -= GetValue();
        if (Input(VK_RIGHT))
        {
            Vector->back().Length[0] += GetValue();
        }
        if (Input(VK_LEFT))
        {
            Vector->back().Length[0] -= GetValue();
        }
    }
    if (isCameraMove)
    {
        vector<2> Direction = { 0 , 0 };

        POINT Mouse =
        {
            Input::Get::Cursor::X() - static_cast<long>(640) ,
            Input::Get::Cursor::Y() - static_cast<long>(360)
        };

        if (abs(Mouse.x) - 600 > 0)
            Direction[0] = static_cast<float>(Mouse.x);
        if (abs(Mouse.y) - 320 > 0)
            Direction[1] = -static_cast<float>(Mouse.y);

        GameManager->Camera.Location += normalize(Direction) * 500 * Time::Get::Delta();
    }


    GetCameraVScope();
    GameManager->Camera.Length = { GameManager->Camera.Length[0] + (120 * scope_V) ,GameManager->Camera.Length[1] + (60 *scope_V) };

  
}

void MapEditor::ChangeType()
{
    int index = static_cast<int>(Type);
    if (Input::Get::Key::Down(VK_TAB))
    {
        ++index;

        switch (index)
        {
        case 3:  printf("Object  \n"); break;
        case 1:  printf("사각형  \n"); break;
        case 2:  printf("    원  \n"); break;
        }

        if (index > 2) index = 0;
        Type = static_cast<VectorType>(index);
    }
    switch (index)
    {
    case 0: Vector = &Objects; break;
    case 1: Vector = &Floor_Collisions; break;
    case 2: Vector = &Wall_Collisions; break;
    }
}

void MapEditor::ChangeValue()
{
    if (Input::Get::Key::Down(VK_OEM_PLUS))
    {
        if (bSnapping)
            SnappingValue += 10;
        else
            Value += 0.002f;
    }
    if (Input::Get::Key::Down(VK_OEM_MINUS))
    {
        if (bSnapping)
            SnappingValue -= 10;
        else
            Value -= 0.002f;
    }
}




void MapEditor::ChangeImage()
{
    if (Type != VectorType::Images)
    {
        return;
    }
    int input = 0;

    printf("변경할 이미지 이름을 입력하세요. \n");
    printf("Input : ");
    std::cin >> Str;
    strcpy_s(const_cast<char*>(Vector->back().Content), Str.size() + 1, Str.c_str());
    //printf("%s \n", Vector->back().Content);
}


void MapEditor::TextDraw()
{
    std::string str;
    str.append("[ Value : ");

    if (bSnapping)
        str.append(std::to_string(static_cast<int>(SnappingValue)));
    else
        str.append(std::to_string(static_cast<float>(Value * 100)));

    str.append(" ]");

    Text.str = str.c_str();
    Text.Draw();
}



void MapEditor::Print() const
{
    {
        printf("HeaderFile \n");
        if (!Objects.empty())
            printf("Rendering::Image::Component Images[%lld]; \n", Objects.size());
        if (!Floor_Collisions.empty())
            printf("Collision::RectAngle RectAngle_Collisions[%lld]; \n", Floor_Collisions.size());
        if (!Wall_Collisions.empty())
            printf("Collision::Circle Circle_Collisions[%lld]; \n", Wall_Collisions.size());

        std::cout << std::endl;
    }
    {
        printf("CppFile \n");

        if (!Objects.empty())
        {
            int i = 0;
            for (Image const& elem : Objects)
            {

                printf("Images[%i] = { \"%s\" , { %.1f, %.1f } , { 0.0f , 0.0f , %.1f } , { %.1f, %.1f }, 1.0f }; \n",
                    i, elem.Content, elem.Length[0], elem.Length[1], elem.Angle[2], elem.Location[0], elem.Location[1]);
                ++i;
            }
        }
        if (!Floor_Collisions.empty())
        {
            int i = 0;
            for (Image const& elem : Floor_Collisions)
            {

                printf("RectAngle_Collisions[%i] = { \"%s\" , { %.1f, %.1f } , { 0.0f , 0.0f , %.1f } , { %.1f, %.1f }, 1.0f }; \n",
                    i, elem.Content, elem.Length[0], elem.Length[1], elem.Angle[2], elem.Location[0], elem.Location[1]);
                ++i;
            }
        }
        if (!Wall_Collisions.empty())
        {
            int i = 0;
            for (Image const& elem : Wall_Collisions)
            {

                printf("Circle_Collisions[%i] = { \"%s\" , { %.1f, %.1f } , { 0.0f , 0.0f , %.1f } , { %.1f, %.1f }, 1.0f }; \n",
                    i, elem.Content, elem.Length[0], elem.Length[1], elem.Angle[2], elem.Location[0], elem.Location[1]);
                ++i;
            }
        }
    }
}

bool MapEditor::Input(size_t code) const
{
    if (bSnapping)
        return Input::Get::Key::Down(code);
    else
        return Input::Get::Key::Press(code);
}

void MapEditor::End()
{

}

void MapEditor::DebugCollider()
{

}

void MapEditor::DrawCollider()
{

}
