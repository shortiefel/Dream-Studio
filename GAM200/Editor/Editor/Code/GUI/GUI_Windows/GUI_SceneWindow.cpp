/* Start Header**********************************************************************************/
/*
@file    GUI_SceneWindow.cpp
@author  Ow Jian Wen	jianwen.o@digipen.edu		100%
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
#include "Editor/Header/GUI/GUI_ClickCheck.hpp"
#include "Editor/Header/GUI/GUI_Guizmo.hpp"

#include "Engine/Header/Window.hpp"
#include "Engine/Header/Math/MathLib.hpp"
#include "Engine/Header/Graphic/Picking2D.hpp"
#include "Engine/Header/ECS/System/TransformCalculationSystem.hpp"


#include "Engine/Header/Event/MouseEvent.hpp"
#include "Engine/Header/Event/KeyEvent.hpp"
#include "Engine/Header/Input/Input.hpp"

#define HEIGHT_CHANGE_SPEED 3.f
#define POS_CHANGE_SPEED EditorSceneCamera::GetHeight() * .01f

#include "Engine/Header/Scene/SceneManager.hpp"
#include "Engine/Header/Management/FileWindowDialog.hpp"
#include "Engine/Header/Management/GameState.hpp"
#include "Engine/Header/Serialize/GameSceneSerializer.hpp"

#include <filesystem>
#include <ImGuizmo.h>
#define REMOVE_FROM_SCENEPATH scenePath = scenePath.string().substr(scenePath.string().find_last_of("\\") + 1);\
							 scenePath = scenePath.string().substr(0, scenePath.string().find_last_of("."));

namespace Editor {
	extern const std::filesystem::path _assetPath;
	namespace GUI_Windows {
		Math::vec2 scene_viewportBounds[2];
		Math::vec2 scene_viewportSize;

		ImGuizmo::OPERATION mCurrentGizmoOperation(ImGuizmo::TRANSLATE);

		//Allow changes to be made when window is focused or hovered
		bool makeChange = false;

		bool inside = false;

		bool keyPressedGuizmo(const Engine::KeyPressedEvent& e) {
			//If not within screen return
			if (!makeChange) return false;

			Engine::Input_KeyCode keyCode = e.GetKeyCode();
			switch (keyCode) {
			case Engine::Input_KeyCode::R:
				mCurrentGizmoOperation = ImGuizmo::ROTATE;
				break;
			case Engine::Input_KeyCode::T:
				mCurrentGizmoOperation = ImGuizmo::TRANSLATE;
				break;
			case Engine::Input_KeyCode::S:
				mCurrentGizmoOperation = ImGuizmo::SCALE;
				break;
			}

			return true;
		}

		bool moving(const Engine::MouseMoveEvent& e) {
			if (!inside || !Engine::Input::IsMouseHold(Engine::Input_MouseCode::Mouse_Middle)) return false;

			//Movement is flipped
			//mouse move left, camera move right
			if (e.GetLeft()) {
				EditorSceneCamera::changePosition(Math::vec2{ POS_CHANGE_SPEED, 0.f });
			}
			else if (e.GetRight()) {
				EditorSceneCamera::changePosition(Math::vec2{ -POS_CHANGE_SPEED, 0.f });
			}
			if (e.GetUp()) {
				EditorSceneCamera::changePosition(Math::vec2{ 0.f, -POS_CHANGE_SPEED });
			}
			else if (e.GetDown()) {
				EditorSceneCamera::changePosition(Math::vec2{ 0.f, POS_CHANGE_SPEED } );
			}

			return true;
		}

		bool scrolling(const Engine::MouseScrolledEvent& e) {
			if (!inside) return false;

			Math::vec2 mouseScroll = e.GetScroll();

			if (mouseScroll.y > 0)  EditorSceneCamera::changeHeight(-HEIGHT_CHANGE_SPEED);
			else if (mouseScroll.y < 0) EditorSceneCamera::changeHeight(HEIGHT_CHANGE_SPEED);

			return true;
		}

		void GUI_SceneSetup() {
			Engine::MouseScrolledEvent::RegisterFunction(scrolling);
			Engine::MouseMoveEvent::RegisterFunction(moving);
			Engine::KeyPressedEvent::RegisterFunction(keyPressedGuizmo);
		}

		//void GUI_SceneWindow(bool* sceneWin_bool, const ImTextureID& sceneWinTex) {
		void GUI_SceneWindow(bool* sceneWin_bool, Engine::Graphic::FrameBuffer& sceneWinFBO, std::map<int, Engine::Entity_id>& entity_selected, ImGuiWindowFlags window_flags) {
			inside = false;

			if (*sceneWin_bool) {
				//ImGui::Begin("Scene Window", sceneWin_bool, window_flags);
				ImGui::Begin("Scene Window", sceneWin_bool, window_flags);
				ImGui::BeginChild("Render");
				makeChange = ImGui::IsWindowFocused() || ImGui::IsWindowHovered();

				ImVec2 wSize = ImGui::GetWindowSize();

				//sceneWinFBO.Resize(static_cast<GLsizei>(wSize.x), static_cast<GLsizei>(wSize.y));
				ImGui::PushItemWidth(wSize.x);
				ASPECT_RATIO_FIX(wSize);

				ImGui::Image((ImTextureID)(sceneWinFBO.GetTexture()), wSize, ImVec2(0, 1), ImVec2(1, 0));

				if (ImGui::BeginDragDropTarget())
				{
					ImGui::Text("I'm Dropping.");
					if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM"))
					{
						const wchar_t* path = (const wchar_t*)payload->Data;
						std::filesystem::path scenePath = std::filesystem::path(_assetPath) / path;

						if (scenePath.extension().string() != ".scene")
						{
							std::cout << "Unable to load scene file\n";
							//std::exit(EXIT_FAILURE);
						}
						
						if (!scenePath.filename().string().empty())
						{
							REMOVE_FROM_SCENEPATH;
							scenePath.replace_extension("");
							Engine::SceneManager::GetInstance().ChangeScene(std::move(scenePath.string()));
						}
					
					}
					ImGui::EndDragDropTarget();
				}

				ImVec2 windowSize = ImGui::GetWindowSize();
				ImVec2 minBound = ImGui::GetWindowPos();
				
				if (windowSize.x > windowSize.y * EditorSceneCamera::GetAR())
					windowSize.x = windowSize.y * EditorSceneCamera::GetAR();
				else
					windowSize.y = windowSize.x / EditorSceneCamera::GetAR();

				//Either guizmo or the object picking is being used
				bool guizmoPressed = false;
				const Engine::Entity_id entity_id = GetTarget(entity_selected);
				if (!EntityId_Check(entity_id)) {
					Engine::TransformComponent* tc = Engine::dreamECSGame->GetComponentPTR<Engine::TransformComponent>(entity_id);

					if (tc != nullptr) {
						ImGuizmo::SetOrthographic(true);
						ImGuizmo::SetDrawlist();
						ImGuizmo::SetRect(minBound.x, minBound.y, windowSize.x, windowSize.y);
						ImGuizmo::SetGizmoSizeClipSpace(EditorSceneCamera::GetHeight() / 4.f);

						const Math::mat4 cameraView = EditorSceneCamera::GetTransformMat4();
						const Math::mat4 cameraProjection{};

						float transArr[3]{ tc->localPosition.x, tc->localPosition.y, 0.f };
						float rotArr[3]{ 0.f, 0.f, tc->angle };
						float scaleArr[3]{ tc->scale.x, tc->scale.y, 1.f };
						Math::mat4 transform;
						ImGuizmo::RecomposeMatrixFromComponents(transArr, rotArr, scaleArr, Math::value_ptr(transform));

						ImGuizmo::Manipulate(Math::value_ptr(cameraView), Math::value_ptr(cameraProjection),
							mCurrentGizmoOperation, ImGuizmo::LOCAL, Math::value_ptr(transform));

						if (ImGuizmo::IsUsing()) {
							guizmoPressed = true;
							ImGuizmo::DecomposeMatrixToComponents(Math::value_ptr(transform), transArr, rotArr, scaleArr);

							tc->localPosition = Math::vec2{ transArr[0], transArr[1] };
							Engine::TransformCalculationSystem::GetInstance().Update();

							float angleDiff = rotArr[2] - tc->angle;
							tc->angle += angleDiff;

							tc->scale = Math::vec2{ scaleArr[0], scaleArr[1] };
						}
					}
				}
				
				ImVec2 maxBound = ImVec2{ minBound.x + windowSize.x, minBound.y + windowSize.y };
				scene_viewportBounds[0] = Math::vec2{ minBound.x, minBound.y };
				scene_viewportBounds[1] = Math::vec2{ maxBound.x, maxBound.y };
				scene_viewportSize = Math::vec2{ windowSize.x, windowSize.y };

				ImVec2 imousePos = ImGui::GetMousePos();
				Math::vec3 mousePos = Math::vec3{imousePos.x, imousePos.y, 1.f }; //1.f because it is a point
				mousePos.x -= scene_viewportBounds[0].x;
				mousePos.y -= scene_viewportBounds[0].y;
				mousePos.y = scene_viewportSize.y - mousePos.y;

				Math::mat3 inverseCamMatrix = EditorSceneCamera::GetInverseTransform();

				int mouseX = (int)mousePos.x;
				int mouseY = (int)mousePos.y;

				if (!guizmoPressed &&
					mouseX >= 0 && mouseX < (int)scene_viewportSize.x &&
					mouseY >= 0 && mouseY < (int)scene_viewportSize.y) {
					inside = true;

					if (Engine::Input::IsMousePressed(Engine::Input_MouseCode::Mouse_Left)) {
						/*mousePos = Math::mat3(2.f / viewportSize.x, 0.f, 0.f,
							0.f, 2.f / viewportSize.y, 0.f,
							-1.f, -1.f, 1.f) * mousePos;
							mousePos = inverseCamMatrix * mousePos;
							Entity_PickingCheck(entity_selected);*/
						//Engine::Graphic::PickingCheck(entity_selected, mousePos, scene_viewportSize, inverseCamMatrix);
						Engine::Graphic::PickingCheck(mousePos, scene_viewportSize, inverseCamMatrix, [&](const Engine::Entity_id& entity_id) { ClickCheck(entity_selected, entity_id); }, [&](const Engine::Entity_id&) {  });
					}
				}

				ImGui::EndChild();
				ImGui::End();
			}
		}
	}
}