/* Start Header**********************************************************************************/
/*
@file    Input.hpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    31/08/2021
\brief
#include "Engine/Header/Input/Input.hpp"
This file has the declaration for Input

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef INPUT_HPP
#define INPUT_HPP

#include "Engine/Header/Input/InputCode.hpp"
#include <unordered_map>
#include "Engine/Header/Math/MathLib.hpp"

namespace Engine {
	class Input {
	public:
		static bool IsKeyPressed(Input_KeyCode keyCode);
		static bool IsMousePressed(Input_MouseCode button);
		static Math::vec2 GetMousePosition();

		static void SetKeyStatus(int key, bool status);
		static void SetMouseStatus(int button, bool status);
		static void SetMousePosition(double xPos, double yPos);

		//Get Input key code with GLFW code
		static Input_KeyCode GetKeyCode(int key);
		//Get Input Mouse code with GLFW code
		static Input_MouseCode GetMouseCode(int button);


	private:
		static Math::vec2 mousePosition;
		static std::unordered_map<int, Input_KeyCode> GLFWtoInputKey;
		static std::unordered_map<Input_KeyCode, bool> InputKeyStatus;

		static std::unordered_map<int, Input_MouseCode> GLFWtoInputMouse;
		static std::unordered_map<Input_MouseCode, bool> InputMouseStatus;
	};
}

#endif