#include "stdafx.h"
#include "AI.h"

AAI::AAI()
{
	Anim.Content = "Wisp";
	Anim.Length = { 50 , 50 };
	Anim.Duration = 0.6f;
}

void AAI::Start()
{
	Anim.Location = { 0 , 0 };
}

void AAI::Update()
{
	//Behaivor(50);

	Anim.Draw();
}

void AAI::End()
{
}

//void AAI::Behaivor(float radius)
//{
//	if (bSucessed)
//	{
//		vector<2> min = { Anim.Location[0] - radius, Anim.Location[1] - radius };
//		vector<2> max = { Anim.Location[0] + radius, Anim.Location[1] + radius };
//		location[0] = GameManager->GetRandom<float>(min[0], max[0]);
//		location[1] = GameManager->GetRandom<float>(min[1], max[1]);;
//		bSucessed = false;
//	}
//	else
//	{
//		vector<2> direction = location - Anim.Location;
//		Anim.Location += normalize(direction) * 200 * Time::Get::Delta();
//		if (length(direction) <= 3.0f) bSucessed = true;
//	}
//}
