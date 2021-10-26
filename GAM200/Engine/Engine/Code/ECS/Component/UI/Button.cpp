/* Start Header**********************************************************************************/
/*
@file    Button.cpp
@author  Tan Wei Ling Felicia weilingfelicia.tan@digipen.edu
@date    26/10/2021
\brief
This file contain the declaration for ButtonComponent


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/ECS/Component/UI/Button.hpp"



namespace Engine {

	ButtonComponent::ButtonComponent(const std::string& label) : ButtonLabel{label}, BState{ButtonState::RELEASED}
	{
		//need fonts
	}

	bool ButtonComponent::OnClick(const Engine::MousePressedEvent& e) 
	{
		BState = ButtonState::PRESSED;
		return true;
	}

	bool ButtonComponent::OnRelease(const Engine::MouseReleasedEvent& e)
	{
		if (BState == ButtonState::RELEASED)
			OnAction();

		BState = ButtonState::RELEASED;
		return true;
	}

	bool ButtonComponent::OnMove(const Engine::MouseMoveEvent& e)
	{
		//need ask jw how do mouse check
		return true;
	}

	void ButtonComponent::OnAction()
	{
		AHandler();
	}

	void ButtonComponent::OnUpdate()
	{

	}

}