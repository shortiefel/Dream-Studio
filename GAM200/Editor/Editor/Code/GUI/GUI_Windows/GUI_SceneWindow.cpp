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

#include "Editor/Header/GUI/GUI_Windows/GUI_SceneWindow.hpp"

#include "Editor/Header/Graphic/EditorSceneCamera.hpp"

#include "Engine/Header/Window.hpp"
#include "Engine/Header/Math/MathLib.hpp"
#include "Engine/Header/Graphic/Picking2D.hpp"


#include "Engine/Header/Input/Input.hpp"

namespace Editor {
	namespace GUI_Windows {
		Math::vec2 viewportBounds[2];
		Math::vec2 viewportSize;

		Math::vec3 mousePos;

		int GUI_GetSceneWindowSizeX() {
			return static_cast<int>(viewportSize.x);
		}

		int GUI_GetSceneWindowSizeY() {
			return static_cast<int>(viewportSize.y);
		}

		//void GUI_SceneWindow(bool* sceneWin_bool, const ImTextureID& sceneWinTex) {
		void GUI_SceneWindow(bool* sceneWin_bool, const Engine::Graphic::FrameBuffer& sceneWinFBO, Engine::Entity& entity_selected) {
			if (*sceneWin_bool) {

				//ImGui::Begin("Scene Window", sceneWin_bool, window_flags);
				ImGui::Begin("Scene Window", sceneWin_bool);
				ImGui::BeginChild("Render");
				ImVec2 wSize = ImGui::GetWindowSize();

				ImGui::PushItemWidth(wSize.x);
				ASPECT_RATIO_FIX(wSize);

				//ImGui::Image((ImTextureID)sceneWinTex, wSize, ImVec2(0, 1), ImVec2(1, 0));
				ImGui::Image((ImTextureID)(sceneWinFBO.GetTexture()), wSize, ImVec2(0, 1), ImVec2(1, 0));


				ImVec2 windowSize = ImGui::GetWindowSize();
				ImVec2 minBound = ImGui::GetWindowPos();
				if (windowSize.x > windowSize.y * EditorSceneCamera::GetAR())
					windowSize.x = windowSize.y * EditorSceneCamera::GetAR();
				else
					windowSize.y = windowSize.x / EditorSceneCamera::GetAR();
				
				ImVec2 maxBound = ImVec2{ minBound.x + windowSize.x, minBound.y + windowSize.y };
				viewportBounds[0] = Math::vec2{ minBound.x, minBound.y };
				viewportBounds[1] = Math::vec2{ maxBound.x, maxBound.y };
				viewportSize = Math::vec2{ windowSize.x, windowSize.y };

				ImVec2 imousePos = ImGui::GetMousePos();
				mousePos = Math::vec3{imousePos.x, imousePos.y, 1.f }; //1.f because it is a point
				mousePos.x -= viewportBounds[0].x;
				mousePos.y -= viewportBounds[0].y;
				mousePos.y = viewportSize.y - mousePos.y;

				Math::mat3 camMatrix = EditorSceneCamera::GetTransform();

				Math::mat3 inverseCamMatrix = Math::Inverse(camMatrix);

				int mouseX = (int)mousePos.x;
				int mouseY = (int)mousePos.y;

				if (mouseX >= 0 && mouseX < (int)viewportSize.x &&
					mouseY >= 0 && mouseY < (int)viewportSize.y) {
					if (Engine::Input::IsMousePressed(Engine::Input_MouseCode::Mouse_Left)) {
						/*mousePos = Math::mat3(2.f / viewportSize.x, 0.f, 0.f,
							0.f, 2.f / viewportSize.y, 0.f,
							-1.f, -1.f, 1.f) * mousePos;
							mousePos = inverseCamMatrix * mousePos;
							Entity_PickingCheck(entity_selected);*/
						Engine::Graphic::PickingCheck(entity_selected, mousePos, viewportSize, inverseCamMatrix);
					}
				}

				ImGui::EndChild();
				ImGui::End();
			}
		}
	}
}