/* Start Header**********************************************************************************/
/*
@file    GUIWindow.cpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    26/07/2021
\brief
This file contain the GUIWindow definition


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Debug Tools/Logging.hpp"
#include "Editor/Header/GUI/GUIWindow.hpp"

#include "Engine/Header/Window.hpp"
#include "Engine/Header/Event/EventDispatcher.hpp"
#include "Engine/Header/ECS/DreamECS.hpp"
#include "Engine/Header/ECS/Component/Graphics/TransformComponent.hpp"

#include "Engine/Header/ECS/System/ScriptSystem.hpp"

#include "Engine/Header/Math/MathLib.hpp"

//Create a window with an image
//E.g Game window 
#define CreateImageWindow(windowName, texid, windowBool) \
	if (windowBool) {\
		ImGui::Begin(windowName, &windowBool, window_flags);\
		ImGui::BeginChild("Render");\
		ImVec2 wSize = ImGui::GetWindowSize();\
		\
		ImGui::PushItemWidth(wSize.x);\
		ASPECT_RATIO_FIX(wSize);\
		\
		ImGui::Image((ImTextureID)texid, wSize, ImVec2(0, 1), ImVec2(1, 0));\
		ImGui::EndChild();\
		ImGui::End();\
	}\



namespace Editor {
	namespace GUI_Window {
		/*-------------------------------------------------------------------------------------------------
		Forward declaration (Menus to be used inside dockspace function)
		Menus: Windows
		-------------------------------------------------------------------------------------------------*/
		//Calling other menu functions
		void	GUI_Menus();
		//Menu for files
		void	GUI_FileMenu();
		//Menu to open windows
		void    GUI_WindowsMenu();


		void GUI_Settings_Setup() {
			dockspace_window_flags |= ImGuiWindowFlags_NoTitleBar;
			dockspace_window_flags |= ImGuiWindowFlags_NoMove;
			dockspace_window_flags |= ImGuiWindowFlags_NoResize;
			dockspace_window_flags |= ImGuiWindowFlags_NoBackground;
			dockspace_window_flags |= ImGuiWindowFlags_MenuBar;

			dockspace_dock_flags |= ImGuiDockNodeFlags_PassthruCentralNode;
		}

		void GUI_DockSpace() {
			Math::vec2 winPos = Engine::Window::GetInstance().GetWindowPosition();
			ImGui::SetNextWindowPos(ImVec2{ winPos.x, winPos.y });
			ImGui::SetNextWindowSize(ImVec2{ (float)Engine::Window::GetInstance().GetWidth(),
											 (float)Engine::Window::GetInstance().GetHeight() });


			ImGui::Begin("Dream Engine", &dockspace_bool, dockspace_window_flags);//, & showWindow, ImGuiWindowFlags_NoInputs);
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_dock_flags);

			GUI_Menus();

			ImGui::End();
		}

		/*-------------------------------------------------------------------------------------------------
		Menus: Windows
		-------------------------------------------------------------------------------------------------*/
		void GUI_Menus() {
			if (ImGui::BeginMenuBar()) {
				GUI_FileMenu();
				GUI_WindowsMenu();

				ImGui::EndMenuBar();
			}
		}

		//Menu for files
		void GUI_FileMenu() {
			if (ImGui::BeginMenu("File")) {
				bool quit = false;
				ImGui::MenuItem("Quit", NULL, &quit);
				if (quit) {
					Engine::WindowCloseEvent event;
					Engine::EventDispatcher::SendEvent(event);
				}

				ImGui::EndMenu();
			}
		}

		//Menu to open windows
		void GUI_WindowsMenu() {
			if (ImGui::BeginMenu("Windows")) {

				ImGui::MenuItem("Hierarchy", NULL, &hierarchy_bool);
				ImGui::MenuItem("Inspector", NULL, &inspector_bool);
				ImGui::MenuItem("Game Window", NULL, &gameWin_bool);
				ImGui::MenuItem("Scene Window", NULL, &sceneWin_bool);

				ImGui::EndMenu();
			}
		}
		/*-------------------------------------------------------------------------------------------------
		-------------------------------------------------------------------------------------------------*/

		/*-------------------------------------------------------------------------------------------------
		Windows creation: Hierarchy, Inspector, Game window, Scene window
		-------------------------------------------------------------------------------------------------*/
		void GUI_Hierarchy() {
			if (hierarchy_bool) {
				ImGui::Begin("Hierarchy", &hierarchy_bool, window_flags);
				ImGui::End();
			}
		}

		void GUI_Inspector() {
			if (inspector_bool) {
				ImGui::Begin("Inspector", &inspector_bool, window_flags);

				Engine::TransformComponent* comp;
				Engine::Entity entity_selected = 0;
				float width = 120;
				bool selectEntity = 0;



				//if (check_selection = true) {
				if (Engine::DreamECS::GetInstance().HasComponent<Engine::TransformComponent>(comp, entity_selected))
				{
					ImGui::Checkbox("Transform", &(comp->isActive));
					ImGui::Text("Position");
					ImGui::Text("X: ");
					ImGui::SameLine();
					ImGui::InputFloat("", &comp->position.x, 0.0f);
					ImGui::Text("Y: ");
					ImGui::SameLine();
					ImGui::InputFloat("", &comp->position.y, 0.0f);



					ImGui::Text("Scaling ");
					ImGui::Text("X: ");
					ImGui::SameLine();
					ImGui::InputFloat("", &comp->scale.x, 0.0f);
					ImGui::Text("Y: ");
					ImGui::SameLine();
					ImGui::InputFloat("", &comp->scale.y, 0.0f);
				}

				Engine::ColliderComponent* colComp;
				if (Engine::DreamECS::GetInstance().HasComponent<Engine::ColliderComponent>(colComp, entity_selected))
				{
					ImGui::DragFloat3("float", &colComp->offset_scale.x, 0.0f);
				}
				//const auto& classScriptInstances = Engine::ScriptSystem::csEntityClassInstance.find(entity_selected);
				//if (classScriptInstances != Engine::ScriptSystem::csEntityClassInstance.end()) {
				//	
				////for (auto& [entityId, classScriptInstances] : Engine::ScriptSystem::csEntityClassInstance) {
				//	for (auto& [className, csScriptInstance] : classScriptInstances->second) {
				//		ImGui::Checkbox(className.c_str(), &(csScriptInstance.isActive));
				//		for (auto& [varName, csPublicVariable] : csScriptInstance.csVariableMap) {
				//			ImGui::Text(varName.c_str());
				//			ImGui::SameLine();
				//			switch (csPublicVariable.variableType) {
				//			case Engine::CSType::CHAR:
				//				//ImGui::InputFloat("A", (float*)csPublicVariable.GetVariableDataPTR<char>(), 0);
				//				break;
				//			case Engine::CSType::BOOL:
				//				ImGui::Checkbox("B", &(csPublicVariable.GetVariableData<bool>()));
				//				break;
				//			case Engine::CSType::FLOAT:
				//				ImGui::InputFloat("C", &(csPublicVariable.GetVariableData<float>()), 0);
				//				break;
				//			case Engine::CSType::INT:
				//				ImGui::InputInt("D", &(csPublicVariable.GetVariableData<int>()), 0);
				//				break;
				//			case Engine::CSType::UINT:
				//				//ImGui::InputFloat("E", (float*)csPublicVariable.GetVariableDataPTR<unsigned int>(), 0);
				//				break;
				//			case Engine::CSType::VEC2:
				//				Math::vec2& tem = csPublicVariable.GetVariableData<Math::vec2>();
				//				ImGui::InputFloat("F", &(tem.x), 0);
				//				ImGui::InputFloat("G", &(tem.y), 0);
				//				break;
				//			}
				//			
				//		}
				//	}
				//}





				ImGui::End();
			}
		}

		void GUI_GameWindow(unsigned int& gameWinTex) {
			CreateImageWindow("Game Window", gameWinTex, gameWin_bool);
		}

		void GUI_SceneWindow(unsigned int& sceneWinTex) {
			CreateImageWindow("Scene Window", sceneWinTex, sceneWin_bool);
		}

		/*-------------------------------------------------------------------------------------------------
		-------------------------------------------------------------------------------------------------*/

	}
}