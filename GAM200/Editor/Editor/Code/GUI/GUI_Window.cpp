/* Start Header**********************************************************************************/
/*
@file    GUIWindow.cpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
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
#include "Engine/Header/ECS/ECSWrapper.hpp"
#include "Engine/Header/ECS/Component/Graphics/TransformComponent.hpp"

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
			Math::vec2 winPos = Engine::Window::GetWindowPosition();
			ImGui::SetNextWindowPos(ImVec2{ winPos.x, winPos.y });
			ImGui::SetNextWindowSize(ImVec2{ (float)Engine::Window::GetWidth(),
											 (float)Engine::Window::GetHeight() });


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
				ImGui::MenuItem("Assets Manager", NULL, &asset_bool);
				ImGui::MenuItem("Content Browser", NULL, &content_bool);

				ImGui::EndMenu();
			}
		}
		/*-------------------------------------------------------------------------------------------------
		-------------------------------------------------------------------------------------------------*/

		/*-------------------------------------------------------------------------------------------------
		Windows creation: Hierarchy, Inspector, Game window, Scene window, Asset Manager
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

				Engine::Transform* comp;
				Engine::Entity entity_selected = 0;
				float width = 120;
				bool selectEntity = 0;



				//if (check_selection = true) {
				if (Engine::DreamECS::HasComponent<Engine::Transform>(comp, entity_selected))
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





				ImGui::End();
			}
		}

		void GUI_GameWindow(unsigned int& gameWinTex) {
			CreateImageWindow("Game Window", gameWinTex, gameWin_bool);
		}

		void GUI_SceneWindow(unsigned int& sceneWinTex) {
			CreateImageWindow("Scene Window", sceneWinTex, sceneWin_bool);
		}

		void GUI_AssetPanel()
		{
			if (asset_bool) {
				ImGui::Begin("Assets Manager", &asset_bool, window_flags);
				ImGui::Text("Asset Path: ");
				ImGui::End();
			}
		}

		void GUI_ContentBrowser()
		{
			if (content_bool) {
				ImGui::Begin("Content Browser", &content_bool, window_flags);
				ImGui::Text("Content");
				ImGui::ArrowButton("down", ImGuiDir_Down);
				ImGui::PushButtonRepeat(true);
				ImGui::PopButtonRepeat();
				ImGui::SameLine();
				ImGui::End();
			}
		}
		/*-------------------------------------------------------------------------------------------------
		-------------------------------------------------------------------------------------------------*/

	}
}