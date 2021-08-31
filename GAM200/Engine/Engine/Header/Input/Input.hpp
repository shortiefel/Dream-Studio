/* Start Header**********************************************************************************/
/*
@file    Input.hpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    31/08/2021
\brief
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
#include "glm/glm.hpp"

namespace Engine {
	class Input {
	public:
		static bool IsKeyPressed(Input_KeyCode keyCode);
		static bool IsMousePressed(Input_MouseCode button);
		static glm::vec2 GetMousePosition();

		static void SetInputKeyStatus(int key, bool status);
		static void SetInputMouseStatus(int button, bool status);
		static void SetInputMousePosition(double xPos, double yPos);


	private:
		static glm::vec2 mousePosition;
		static std::unordered_map<int, Input_KeyCode> GLFWtoInputKey;
		static std::unordered_map<Input_KeyCode, bool> InputKeyStatus;

		static std::unordered_map<int, Input_MouseCode> GLFWtoInputMouse;
		static std::unordered_map<Input_MouseCode, bool> InputMouseStatus;
	};
}

#endif