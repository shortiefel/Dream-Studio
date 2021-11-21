/* Start Header**********************************************************************************/
/*
@file    GUI_SceneWindow.hpp
@author  Ow Jian Wen	jianwen.o@digipen.edu		100%
@date    21/10/2021
\brief
#include "Editor/Header/GUI/GUI_Windows/GUI_SceneWindow.hpp"
This file has the function declaration for GUI scene window


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/


#ifndef SCENE_WINDOW_HPP
#define SCENE_WINDOW_HPP

#include <Imgui/imgui.h>
#include "Engine/Header/Graphic/FrameBuffer.hpp"
#include "Engine/Header/ECS/ECSGlobal.hpp"
#include "Engine/Header/Commands/Command.hpp"

#include <map>

namespace Editor {
	namespace GUI_Windows {
		void GUI_SceneSetup();
		void GUI_SceneWindow(bool* sceneWin_bool, Engine::Graphic::FrameBuffer& sceneWinFBO, std::map<int, Engine::Entity_id>& entity_selected, ImGuiWindowFlags window_flags);
		/*int GUI_GetSceneWindowSizeX();
		int GUI_GetSceneWindowSizeY();*/
	}
}

#endif