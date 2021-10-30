/* Start Header**********************************************************************************/
/*
@file    GUI_GameWindow.hpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    21/10/2021
\brief
#include "Editor/Header/GUI/GUI_Windows/GUI_GameWindow.hpp"
This file has the function declaration for GUI game window


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/


#ifndef GAME_WINDOW_HPP
#define GAME_WINDOW_HPP

#include <Imgui/imgui.h>
#include "Engine/Header/Graphic/FrameBuffer.hpp"
#include "Engine/Header/ECS/DreamECS.hpp"

namespace Editor {
	namespace GUI_Windows {
		Math::mat3 GetViewport();
		Math::vec2 GetMousePosition();
		void GUI_GameWindow(bool* gameWin_bool, const Engine::Graphic::FrameBuffer& gameWinFBO, ImGuiWindowFlags window_flags);
		/*int GUI_GetSceneWindowSizeX();
		int GUI_GetSceneWindowSizeY();*/
	}
}

#endif