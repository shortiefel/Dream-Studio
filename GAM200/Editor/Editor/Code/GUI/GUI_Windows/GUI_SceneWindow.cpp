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

#include "Engine/Header/ECS/DreamECS.hpp"
#include "Engine/Header/ECS/Component/ComponentArray.hpp"
#include "Engine/Header/ECS/Component/Graphics/TransformComponent.hpp"

namespace Editor {
	namespace GUI_Windows {
		Math::vec2 viewportBounds[2];
		Math::vec2 viewportSize;

		void Entity_PickingCheck() {
			const auto& transformArray = Engine::DreamECS::GetInstance().GetComponentArrayData<Engine::TransformComponent>();
			for (const auto& transform : transformArray) {

			}
		}

		int GUI_GetSceneWindowSizeX() {
			return static_cast<int>(viewportSize.x);
		}

		int GUI_GetSceneWindowSizeY() {
			return static_cast<int>(viewportSize.y);
		}

		//void GUI_SceneWindow(bool* sceneWin_bool, const ImTextureID& sceneWinTex) {
		void GUI_SceneWindow(bool* sceneWin_bool, const Engine::Graphic::FrameBuffer& sceneWinFBO) {
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
				ImVec2 maxBound = ImVec2{ minBound.x + windowSize.x, minBound.y + windowSize.y };
				viewportBounds[0] = Math::vec2{ minBound.x, minBound.y };
				viewportBounds[1] = Math::vec2{ maxBound.x, maxBound.y };
				viewportSize = Math::vec2{ windowSize.x, windowSize.y };

				ImVec2 imousePos = ImGui::GetMousePos();
				Math::vec3 mousePos{ imousePos.x, imousePos.y, 1.f }; //A point
				//auto [mx, my] = ImGui::GetMousePos();
				mousePos.x -= viewportBounds[0].x;
				mousePos.y -= viewportBounds[0].y;
				mousePos.y = viewportSize.y - mousePos.y;

				Math::mat3 camMatrix = EditorSceneCamera::GetTransform();
				//float determinant; 
				Math::mat3 inverseCamMatrix = Math::Inverse(camMatrix);
				std::cout << inverseCamMatrix << " " << camMatrix << "\n";

				int mouseX = (int)mousePos.x;
				int mouseY = (int)mousePos.y;

				if (mouseX >= 0 && mouseX < (int)viewportSize.x &&
					mouseY >= 0 && mouseY < (int)viewportSize.y) {
					//mousePos = camMatrix * mousePos;
					mousePos = Math::mat3(1.f/ viewportSize.x, 0.f, 0.f,
									0.f, 1.f / viewportSize.y, 0.f,
									-1.f / 2.f, -1.f / 2.f, 1.f) * mousePos;
					mousePos = camMatrix * mousePos;
					//std::cout << mousePos.x << " " << mousePos.y << " \n";
					//std::cout << mouseX << " " << mouseY << " \n";
					//sceneWinFBO.GetIndex();
					//Entity_PickingCheck();
					//std::cout << sceneWinFBO.ReadPixel(mouseX, mouseY) << "\n";
				}

				ImGui::EndChild();
				ImGui::End();
			}
		}
	}
}