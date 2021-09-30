/* Start Header**********************************************************************************/
/*
@file    GUIWindow.cpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
		 Goh See Yong, Denise   g.seeyongdenise@digipen.edu
		 Tan Wei Ling Felicia	weilingfelicia.tan@digipen.edu
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
				ImGui::MenuItem("New", "CTRL+N");
				//if ()
				ImGui::MenuItem("Open", "CTRL+O");
				ImGui::MenuItem("Save as", "CTRL+S");
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

				ImGui::MenuItem("Header", NULL, &playStop_bool);
				ImGui::MenuItem("Hierarchy", NULL, &hierarchy_bool);
				ImGui::MenuItem("Inspector", NULL, &inspector_bool);
				ImGui::MenuItem("Game Window", NULL, &gameWin_bool);
				ImGui::MenuItem("Scene Window", NULL, &sceneWin_bool);
				ImGui::MenuItem("Content Browser", NULL, &asset_bool);
				

				ImGui::EndMenu();
			}

			
		}
		/*-------------------------------------------------------------------------------------------------
		-------------------------------------------------------------------------------------------------*/

		/*-------------------------------------------------------------------------------------------------
		Windows creation: Header, Hierarchy, Inspector, Game window, Scene window, Asset Manager
		-------------------------------------------------------------------------------------------------*/
		void GUI_HeaderPanel() {

			if (playStop_bool)
			{
				ImVec2 wSize = ImGui::GetWindowSize();
				ImGui::Begin("##Header", &playStop_bool, window_flags);

				static int clicked = 0;

				ImGui::PushItemWidth(wSize.x / 2);
				ImGui::Button("Play", (ImVec2{ 40, 30 }));
					clicked++; //script to replace
				ImGui::SameLine();
				ImGui::PushItemWidth(wSize.x /2 + 20);
				if (ImGui::Button("Stop", (ImVec2{ 40, 30 })))
					clicked++; //script to replace

				ImGui::End();
			}
		}

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
				Engine::Entity entity_selected = Engine::Entity{ 0 };
				float width = 120;
				bool selectEntity = 0;

				/**
				*	Transform Properties
				*/

				if (ImGui::TreeNode("Transform"))
				{
					ImGui::Spacing();
					if (Engine::DreamECS::GetInstance().HasComponent<Engine::TransformComponent>(comp, entity_selected))
					{
						//Updating of position
						ImGui::Text("Position");
						ImGui::Spacing();
						ImGui::Text("X: ");
						ImGui::SameLine();
						ImGui::InputFloat("##posX", &comp->position.x, 0.0f);
						ImGui::Text("Y: ");
						ImGui::SameLine();
						ImGui::InputFloat("##posY", &comp->position.y, 0.0f);


						//Updating of scaling
						ImGui::Text("Scaling ");
						ImGui::Spacing();
						ImGui::Text("X: ");
						ImGui::SameLine();
						ImGui::InputFloat("##posXscale", &comp->scale.x, 0.0f);
						ImGui::Text("Y: ");
						ImGui::SameLine();
						ImGui::InputFloat("##posYscale", &comp->scale.y, 0.0f);


						ImGui::Text("Rotation ");
						ImGui::Spacing();
						ImGui::SliderAngle("##posRotate", &comp->angle);


					}
					ImGui::TreePop();
	
				}

				/**
				*	Scripts for each component
				*/
				if (ImGui::TreeNode("Script")) {

					ImGui::Text("hello");
				}

				/**
				*	Add New Components
				*/
				
				if (ImGui::Button("Add Component", (ImVec2{ 100, 0 })))
				{
					
				}
				//if (check_selection = true) {
				if (Engine::DreamECS::GetInstance().HasComponent<Engine::TransformComponent>(comp, entity_selected))
				{
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

		void GUI_ContentBrowserPanel()
		{
			if (asset_bool) {
				ImGui::Begin("Content Browser", &asset_bool, window_flags);
				if (_currentDirectory != std::filesystem::path("Assets"))
				{
					if (ImGui::Button("<-"))
					{
						_currentDirectory = _currentDirectory.parent_path();
					}
				}

				static float padding = 16.0f;
				static float thumbnailSize = 128.0f;
				float cellSize = thumbnailSize + padding;

				float panelWidth = ImGui::GetContentRegionAvail().x;
				int columnCount = (int)(panelWidth / cellSize);
				if (columnCount < 1)
					columnCount = 1;

				ImGui::Columns(columnCount, 0, false);

				for (auto& directory : std::filesystem::directory_iterator("Assets"))
				{
					const auto& path = directory.path();
					auto relative_path = std::filesystem::relative(path, _currentDirectory);
					std::string filenameString = relative_path.string();

					ImGui::PushID(filenameString.c_str());
					//auto& texture = Engine::DreamECS::GetInstance().GetComponentType<Texture>();
					//directory.is_directory() ? "Assets/Textures/DirectoryIcon.png" : "Assets/Texures/FileIcon.png";
					//texture->getFilepath();
					ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
					ImGui::Button("Button Image");
					//ImGui::ImageButton((ImTextureID)texture->GetEntityId(), {thumbnailSize, thumbnailSize}, {0, 1}, {1, 0});
					if (ImGui::BeginDragDropSource())
					{
						const wchar_t* itemPath = relative_path.c_str();
						ImGui::SetDragDropPayload("CONTENT_BROWSER_ITEM", itemPath, (wcslen(itemPath) + 1) * sizeof(wchar_t));
						ImGui::EndDragDropSource();
					}
					ImGui::PopStyleColor();
					if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
					{
						if (directory.is_directory())
						{
							_currentDirectory /= path.filename();
						}

					}
					ImGui::TextWrapped(filenameString.c_str());

					ImGui::NextColumn();

					ImGui::PopID();

				}
				ImGui::Columns(1);

				ImGui::SliderFloat("Thumbnail Size", &thumbnailSize, 16, 512);
				ImGui::SliderFloat("Padding", &padding, 0, 32);

				ImGui::End();
			}
		}
		/*-------------------------------------------------------------------------------------------------
		-------------------------------------------------------------------------------------------------*/

	}
}