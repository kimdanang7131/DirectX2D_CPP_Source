#include "stdafx.h"
#include "InputComponent.h"

CInputComponent::CInputComponent(APlayer* owner) :Owner(owner)
{

}

void CInputComponent::Start()
{
}

void CInputComponent::Update()
{
	for (AxisData elem : AxisList)
	{
		if (Input::Get::Key::Press(elem.Key))
			(Owner->*(elem.Func))(elem.Axis);
		if (Input::Get::Key::Up(elem.Key))
			(Owner->*(elem.Func))(0);
	}


	for (std::pair<UINT, void(APlayer::*)()>elem : PressedList)
	{
		if (Input::Get::Key::Down(elem.first))
			(Owner->*(elem.second))();
	}

	for (std::pair<UINT, void(APlayer::*)()>elem : ReleaseList)
	{
		if (Input::Get::Key::Down(elem.first))
			(Owner->*(elem.second))();
	}
	
}

void CInputComponent::End()
{
}

void CInputComponent::BindAxis(AxisData* Axis, UINT count)
{
	for (UINT i = 0; i < count; i++)
		AxisList.push_back(Axis[i]);
}

void CInputComponent::BindAction(UINT Key, ActionType type, void(APlayer::* func)())
{
	if (type == ActionType::PRESSED)
		PressedList.try_emplace(Key, func);
	else
		ReleaseList.try_emplace(Key, func);
}

