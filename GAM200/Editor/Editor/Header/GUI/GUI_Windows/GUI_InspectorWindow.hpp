/* Start Header**********************************************************************************/
/*
@file    GUI_InspectorWindow.hpp
@author   Tan Wei Ling Felicia		weilingfelicia.tan@digipen.edu	100%
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


#pragma once

#include <Imgui/imgui.h>
#include "Engine/Header/ECS/DreamECS.hpp"

namespace Editor {
	namespace GUI_Windows {
		void GUI_Inspector(bool* inspector_bool, float textSize, const Engine::Entity_id& entity_selected, ImGuiWindowFlags window_flags);
		struct Animation2D
		{
			Math::vec2 Min{};
			Math::vec2 Max{};
			float timer{ 1.0f };
			
		};
	}
}