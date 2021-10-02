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
#include "Editor/Header/Scene/EditorSceneManager.hpp"

#include <Imgui/imgui_internal.h>

#include "Engine/Header/Management/GameState.hpp"
#include "Engine/Header/Window.hpp"
#include "Engine/Header/Event/EventDispatcher.hpp"
#include "Engine/Header/ECS/DreamECS.hpp"
#include "Engine/Header/ECS/Component/ComponentArray.hpp"
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
				ImGui::Begin("Actions", &playStop_bool, window_flags);

				ImGui::PushItemFlag(ImGuiItemFlags_Disabled, Engine::GameState::GetPlaying());
				ImGui::PushItemWidth(wSize.x / 2);
				if (ImGui::Button("Play", (ImVec2{ 40, 30 }))) {
					EditorSceneManager::GetInstance().Play();
				}
				ImGui::PopItemFlag();

				ImGui::SameLine();
				ImGui::PushItemWidth(wSize.x /2 + 20);
				ImGui::PushItemFlag(ImGuiItemFlags_Disabled, !(Engine::GameState::GetPlaying()));
				if (ImGui::Button("Stop", (ImVec2{ 40, 30 }))) {
					EditorSceneManager::GetInstance().Stop();
				}
				ImGui::PopItemFlag();

				ImGui::End();
			}
		}

		void GUI_Hierarchy() {
			if (hierarchy_bool) {
				ImGui::Begin("Hierarchy", &hierarchy_bool, window_flags);

				/**
				* Game Objects 
				*/

				//if (ImGui::TreeNode("Camera")) {

				//	static ImGuiTreeNodeFlags base_Flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
				//	static bool alignmentPosition = false;

				//	/*ImGui::CheckboxFlags("ImGuiTreeNodeFlags_OpenOnArrow", &base_Flags, ImGuiTreeNodeFlags_OpenOnArrow);
				//	ImGui::CheckboxFlags("ImGuiTreeNodeFlags_OpenOnDoubleClick", &base_Flags, ImGuiTreeNodeFlags_OpenOnDoubleClick);*/

				//	if (alignmentPosition)
				//		ImGui::Unindent(ImGui::GetTreeNodeToLabelSpacing());

				//	/*Engine::Entity entity_selected = Engine::Entity{ 0 };
				//	std::vector entity_set = Engine::DreamECS::GetInstance().GetUsedEntitySet();

				//	for (int i = 0; i < entity_set.size(); i++)
				//	{
				//		ImGui::Text(entity_set[i].name.c_str());
				//		
				//	}*/
				//	ImGui::TreePop();
				//}

				Engine::Entity entity_selected = Engine::Entity{ 0 };
				std::vector entity_set = Engine::DreamECS::GetInstance().GetUsedEntitySet();

				for (int i = 0; i < entity_set.size(); i++)
				{
					ImGui::Text(entity_set[i].name.c_str());

				}

				ImGui::End();
			}
		}

		void GUI_Inspector() {
			if (inspector_bool) {
				ImGui::Begin("Inspector", &inspector_bool, window_flags);

				Engine::Entity entity_selected = Engine::Entity{ 0 };
				float width = 120;
				bool selectEntity = 0;
				
				/**
				*	Transform Properties
				*/
				Engine::TransformComponent* transComp = Engine::DreamECS::GetInstance().GetComponentPTR<Engine::TransformComponent>(entity_selected);
				if (transComp != nullptr) {
					ImGui::Checkbox("##TransformActive", &(transComp->isActive));
					if (ImGui::TreeNode("Transform")) {
						//ImGui::SameLine();
						//ImGui::Checkbox("##TransformActive", &(transComp->isActive));

						ImGui::Spacing();
						//Updating of position
						ImGui::Text("Position");
						ImGui::Spacing();
						ImGui::Text("X: ");
						ImGui::SameLine();
						ImGui::InputFloat("##TransformXPos", &transComp->position.x, 0.0f);
						ImGui::Text("Y: ");
						ImGui::SameLine();
						ImGui::InputFloat("##TransformYPos", &transComp->position.y, 0.0f);


						//Updating of scaling
						ImGui::Text("Scaling ");
						ImGui::Spacing();
						ImGui::Text("X: ");
						ImGui::SameLine();
						ImGui::InputFloat("##TransformXscale", &transComp->scale.x, 0.0f);
						ImGui::Text("Y: ");
						ImGui::SameLine();
						ImGui::InputFloat("##TransformYscale", &transComp->scale.y, 0.0f);


						ImGui::Text("Rotation ");
						ImGui::Spacing();
						ImGui::SliderFloat("##TransformRotate", &transComp->angle, -360.f, 360.f);

						ImGui::TreePop();
					}
				}

				/**
				*	Collider for each component
				*/
				Engine::ColliderComponent* colComp = Engine::DreamECS::GetInstance().GetComponentPTR<Engine::ColliderComponent>(entity_selected);
				if (colComp != nullptr) {
					if (ImGui::TreeNode("Collider")) {
						ImGui::DragFloat3("float", &colComp->offset_scale.x, 0.0f);
						ImGui::TreePop();
					}
				}

				/*if (ImGui::TreeNode("Collider")) {
					Engine::ColliderComponent* colComp;
					if (Engine::DreamECS::GetInstance().HasComponent<Engine::ColliderComponent>(colComp, entity_selected) == 0)
					{
						ImGui::Text("No collider in scene");
					}
					else
					{
						ImGui::DragFloat3("float", &colComp->offset_scale.x, 0.0f);
					}
					ImGui::TreePop();
				}*/
				

				/**
				*	Scripts for each component
				*/
				Engine::ScriptComponent* scriptComp = Engine::DreamECS::GetInstance().GetComponentPTR<Engine::ScriptComponent>(entity_selected);
				if (scriptComp != nullptr) {
					if (ImGui::TreeNode("Script")) {
						auto& scriptsList = scriptComp->klassInstance;

						for (auto& [className, csScriptInstance] : scriptsList) {
							ImGui::Checkbox(className.c_str(), &(csScriptInstance.isActive));
							for (auto& [varName, csPublicVariable] : csScriptInstance.csVariableMap) {
								ImGui::Text(varName.c_str());
								ImGui::SameLine();
								switch (csPublicVariable.variableType) {
								case Engine::CSType::CHAR:
									//ImGui::InputFloat("A", (float*)csPublicVariable.GetVariableDataPTR<char>(), 0);
									break;
								case Engine::CSType::BOOL:
									ImGui::Checkbox("B", &(csPublicVariable.GetVariableData<bool>()));
									break;
								case Engine::CSType::FLOAT:
									ImGui::InputFloat("C", &(csPublicVariable.GetVariableData<float>()), 0);
									break;
								case Engine::CSType::INT:
									ImGui::InputInt("D", &(csPublicVariable.GetVariableData<int>()), 0);
									break;
								case Engine::CSType::UINT:
									//ImGui::InputFloat("E", (float*)csPublicVariable.GetVariableDataPTR<unsigned int>(), 0);
									break;
								case Engine::CSType::VEC2:
									Math::vec2& tem = csPublicVariable.GetVariableData<Math::vec2>();
									ImGui::InputFloat("F", &(tem.x), 0);
									ImGui::InputFloat("G", &(tem.y), 0);
									break;
								}
									
							}
						}
						

						ImGui::TreePop();
					}
				}


				/**
				*	Add New Components
				*/
				
				ImGui::Button("Add Component", (ImVec2{ 100, 0 }));





				ImGui::End();
			}
		}

		void GUI_GameWindow(ImTextureID& gameWinTex) {
			CreateImageWindow("Game Window", gameWinTex, gameWin_bool);
		}

		void GUI_SceneWindow(ImTextureID& sceneWinTex) {
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