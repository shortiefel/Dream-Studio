/* Start Header**********************************************************************************/
/*
@file    GUI_StatsWindow.cpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    20/10/2021
\brief
#include "Editor/Header/GUI/GUI_Windows/GUI_StatsWindow.hpp"
This file has the function declaration for GUI State window


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Editor/Header/GUI/GUI_Windows/GUI_StatsWindow.hpp"
#include "Engine/Header/ECS/DreamECS.hpp"
#include "Engine/Header/Time/DeltaTime.hpp"
#include "Engine/Header/Graphic/mesh.hpp"

#include <Imgui/imgui.h>

#include <sstream>

namespace Editor {
	namespace GUI_Windows {
		void GUI_Stats(bool* stats_bool) {
			if (*stats_bool) {
				ImGui::Begin("Engine Stats", stats_bool);
				std::stringstream outputSS;
				outputSS << "FPS: ";
				outputSS.precision(2);
				outputSS << std::fixed << Engine::DeltaTime::GetInstance().GetFPS();

				ImGui::Text(outputSS.str().c_str());
				outputSS.str(std::string());

				outputSS << "Entity Count: ";
				outputSS << Engine::dreamECSGame->GetUsedEntitySize();
				ImGui::Text(outputSS.str().c_str());
				outputSS.str(std::string());

				outputSS << "Number of Quads : ";
				outputSS << Engine::GraphicImplementation::Renderer::GetQuadStats().quadCount;
				ImGui::Text(outputSS.str().c_str());
				outputSS.str(std::string());


				outputSS << "Draw Count : ";
				outputSS << Engine::GraphicImplementation::Renderer::GetQuadStats().drawCount;
				ImGui::Text(outputSS.str().c_str());
				outputSS.str(std::string());

				ImGui::End();
			}
		}
	}
}
