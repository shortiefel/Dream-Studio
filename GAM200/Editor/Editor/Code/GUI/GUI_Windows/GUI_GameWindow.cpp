/* Start Header**********************************************************************************/
/*
@file    GUI_SceneWindow.cpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    21/10/2021
\brief
#include "Editor/Header/GUI/GUI_Windows/GUI_SceneWindow.hpp"
This file has the function definition for GUI scene window


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Editor/Header/GUI/GUI_Windows/GUI_GameWindow.hpp"

#include "Engine/Header/ECS/System/CameraSystem.hpp"

#include "Engine/Header/Window.hpp"
#include "Engine/Header/Math/MathLib.hpp"
#include "Engine/Header/Graphic/Picking2D.hpp"

#include "Engine/Header/Input/Input.hpp"

namespace Editor {
	namespace GUI_Windows {
		Math::vec2 game_viewportBounds[2];
		Math::vec2 game_viewportSize;
		Math::vec3 mousePos;

		int GUI_GetGameWindowSizeX() {
			return static_cast<int>(game_viewportSize.x);
		}

		int GUI_GetGameWindowSizeY() {
			return static_cast<int>(game_viewportSize.y);
		}

		Math::mat3 GetViewport() {
			return Math::mat3(2.f / game_viewportSize.x, 0.f, 0.f,
							  0.f, 2.f / game_viewportSize.y, 0.f,
							  -1.f, -1.f, 1.f);
		}

		Math::vec2 GetMousePosition() {
			return Math::vec2{ mousePos.x, mousePos.y };
		}

		void GUI_GameWindow(bool* gameWin_bool, const Engine::Graphic::FrameBuffer& gameWinFBO, ImGuiWindowFlags window_flags) {
			if (*gameWin_bool) {

				//ImGui::Begin("Scene Window", sceneWin_bool, window_flags);
				ImGui::Begin("Game Window", gameWin_bool, window_flags);
				ImGui::BeginChild("Render");
				ImVec2 wSize = ImGui::GetWindowSize();

				ImGui::PushItemWidth(wSize.x);
				ASPECT_RATIO_FIX(wSize);

	
				ImGui::Image((ImTextureID)(gameWinFBO.GetTexture()), wSize, ImVec2(0, 1), ImVec2(1, 0));


				ImVec2 windowSize = ImGui::GetWindowSize();
				ImVec2 minBound = ImGui::GetWindowPos();
				if (windowSize.x > windowSize.y * Engine::CameraSystem::GetInstance().GetAR())
					windowSize.x = windowSize.y * Engine::CameraSystem::GetInstance().GetAR();
				else
					windowSize.y = windowSize.x / Engine::CameraSystem::GetInstance().GetAR();

				ImVec2 maxBound = ImVec2{ minBound.x + windowSize.x, minBound.y + windowSize.y };
				game_viewportBounds[0] = Math::vec2{ minBound.x, minBound.y };
				game_viewportBounds[1] = Math::vec2{ maxBound.x, maxBound.y };
				game_viewportSize = Math::vec2{ windowSize.x, windowSize.y };

				ImVec2 imousePos = ImGui::GetMousePos();
				Math::vec3 _mousePos = Math::vec3{ imousePos.x, imousePos.y, 1.f }; //1.f because it is a point
				_mousePos.x -= game_viewportBounds[0].x;
				_mousePos.y -= game_viewportBounds[0].y;
				_mousePos.y = game_viewportSize.y - _mousePos.y;
				mousePos = _mousePos;

				Math::mat3 camMatrix = Engine::CameraSystem::GetInstance().GetTransform();

				Math::mat3 inverseCamMatrix = Math::Inverse(camMatrix);

				int mouseX = (int)_mousePos.x;
				int mouseY = (int)_mousePos.y;
				
				if (mouseX >= 0 && mouseX < (int)game_viewportSize.x &&
					mouseY >= 0 && mouseY < (int)game_viewportSize.y) {
					
					Engine::Graphic::PickingCheck(mousePos, game_viewportSize, inverseCamMatrix, 
						[&](const Engine::Entity& entity) { Engine::Graphic::RecordMouseOverlap(entity.id, true);  }, 
						[&](const Engine::Entity& entity) { Engine::Graphic::RecordMouseOverlap(entity.id, false); });
				}

				ImGui::EndChild();
				ImGui::End();
			}
		}
	}
}