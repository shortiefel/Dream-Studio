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
#include "Editor/Header/GUI/GUI_Window.hpp"
#include "Editor/Header/GUI/GUI_Imgui.hpp"
#include "Editor/Header/GUI/GUI_Windows/GUI_ProfilerWindow.hpp"
#include "Editor/Header/GUI/GUI_Windows/GUI_ConsoleWindow.hpp"
#include "Editor/Header/GUI/GUI_Windows/GUI_SceneWindow.hpp"
#include "Editor/Header/Scene/EditorSceneManager.hpp"

#include <Imgui/imgui_internal.h>

#include "Engine/Header/Management/GameState.hpp"
#include "Engine/Header/Time/DeltaTime.hpp"
#include "Engine/Header/Window.hpp"
#include "Engine/Header/Event/EventDispatcher.hpp"
#include "Engine/Header/ECS/DreamECS.hpp"
#include "Engine/Header/ECS/Component/ComponentArray.hpp"
#include "Engine/Header/ECS/Component/Graphics/TransformComponent.hpp"

#include "Engine/Header/ECS/System/ScriptSystem.hpp"

#include "Engine/Header/Math/MathLib.hpp"

//#include <string>

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
	namespace GUI_Windows {
		//bool for dockspace (will always be true)
		bool dockspace_bool = true;
		//Flags for the background window for windows to dock to
		ImGuiWindowFlags dockspace_window_flags = 0;
		ImGuiDockNodeFlags dockspace_dock_flags = 0;

		ImGuiWindowFlags window_flags = 0;

		Engine::Entity entity_selected = Engine::Entity{ 1 };

		bool hierarchy_bool = true;
		bool inspector_bool = true;
		bool stats_bool = true;
		bool profiler_bool = false;
		bool console_bool = true;
		bool gameWin_bool = true;
		bool sceneWin_bool = true;
		bool asset_bool = true;
		//Will always be on
		bool playStop_bool = true; //Play and stop button

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

		/*-------------------------------------------------------------------------------------------------
		Windows creation: Hierarchy, Inspector, Game window, Scene window
		-------------------------------------------------------------------------------------------------*/
		void    GUI_HeaderPanel();
		void	GUI_Hierarchy();
		void	GUI_Inspector();
		//Show stats like fps and Number of game object
		void	GUI_Stats();
		//Profiler window
		void	GUI_GameWindow(const ImTextureID& gameWinTex);
		//void	GUI_SceneWindow(const ImTextureID& sceneWinTex);
		void    GUI_ContentBrowserPanel();


		void GUI_Settings_Setup() {
			dockspace_window_flags |= ImGuiWindowFlags_NoTitleBar;
			dockspace_window_flags |= ImGuiWindowFlags_NoMove;
			dockspace_window_flags |= ImGuiWindowFlags_NoResize;
			dockspace_window_flags |= ImGuiWindowFlags_NoBackground;
			dockspace_window_flags |= ImGuiWindowFlags_MenuBar;

			dockspace_dock_flags |= ImGuiDockNodeFlags_PassthruCentralNode;

			GUI_Windows::GUI_Console_Create();
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
				ImGui::MenuItem("Hierarchy", NULL, &hierarchy_bool);
				ImGui::MenuItem("Inspector", NULL, &inspector_bool);
				ImGui::MenuItem("Game Window", NULL, &gameWin_bool);
				ImGui::MenuItem("Scene Window", NULL, &sceneWin_bool);
				ImGui::MenuItem("Content Browser", NULL, &asset_bool);
				ImGui::MenuItem("Engine Stats", NULL, &stats_bool);
				ImGui::MenuItem("Profiler", NULL, &profiler_bool);
				ImGui::MenuItem("Console", NULL, &console_bool);

				ImGui::EndMenu();
			}
		}

		int GetSceneSizeX() {
			return GUI_GetSceneWindowSizeX();
		}   
		int GetSceneSizeY() {
			return GUI_GetSceneWindowSizeY();
		}
		/*-------------------------------------------------------------------------------------------------
		-------------------------------------------------------------------------------------------------*/

		/*-------------------------------------------------------------------------------------------------
		Windows creation: Header, Hierarchy, Inspector, Game window, Scene window, Asset Manager
		-------------------------------------------------------------------------------------------------*/
		//void All_Windows(const ImTextureID& gameWinTex, const ImTextureID& sceneWinTex) {
		void All_Windows(const ImTextureID& gameWinTex, const Engine::Graphic::FrameBuffer& sceneWinFBO) {
			GUI_GameWindow(gameWinTex);
			//GUI_SceneWindow(&sceneWin_bool, sceneWinTex);
			GUI_SceneWindow(&sceneWin_bool, sceneWinFBO, entity_selected);
			GUI_Hierarchy();
			GUI_Inspector();
			GUI_Stats();
			GUI_Profiler(&profiler_bool);
			GUI_ContentBrowserPanel();
			GUI_HeaderPanel();
			GUI_Console(&console_bool);
		}

		void GUI_HeaderPanel() {
			//Will always be on so dont need check

			ImVec2 wSize = ImGui::GetWindowSize();
			ImGui::Begin("Actions", &playStop_bool, window_flags);

			ImGui::PushItemFlag(ImGuiItemFlags_Disabled, Engine::GameState::GetInstance().GetPlaying());
			ImGui::PushItemWidth(wSize.x / 2);
			if (ImGui::Button("Play", (ImVec2{ 40, 30 }))) {
				if (!EditorSceneManager::GetInstance().Play()) Engine::GameState::GetInstance().SetPlaying(false);
			}
			ImGui::PopItemFlag();

			ImGui::SameLine();
			ImGui::PushItemWidth(wSize.x / 2 + 20);
			ImGui::PushItemFlag(ImGuiItemFlags_Disabled, !(Engine::GameState::GetInstance().GetPlaying()));
			if (ImGui::Button("Stop", (ImVec2{ 40, 30 }))) {
				EditorSceneManager::GetInstance().Stop();
			}
			ImGui::PopItemFlag();

			ImGui::End();
			
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

				//Engine::Entity entity_selected = Engine::Entity{ 0 };
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

				
				float width = 120;
				bool selectEntity = 0;

				/**
				*	Transform Properties
				*/
				Engine::TransformComponent* transComp = Engine::DreamECS::GetInstance().GetComponentPTR<Engine::TransformComponent>(entity_selected);
				if (transComp != nullptr) {

					ImGui::CheckBox_Dream("##TransformActive", &(transComp->isActive));
					ImGui::SameLine();

					if (ImGui::TreeNode("Transform")) {
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

				/*
				*	Collider for each component
				*/
				Engine::ColliderComponent* colComp = Engine::DreamECS::GetInstance().GetComponentPTR<Engine::ColliderComponent>(entity_selected);
				if (colComp != nullptr) {

					ImGui::CheckBox_Dream("##ColliderActive", &(colComp->isActive));
					ImGui::SameLine();

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
					//if (ImGui::TreeNode("Script")) {
						auto& scriptsList = scriptComp->klassInstance;

						for (auto& [className, csScriptInstance] : scriptsList) {
							//ImGui::Checkbox(className.c_str(), &(csScriptInstance.isActive));
							ImGui::CheckBox_Dream(std::string{ "##ScriptActive" + className }.c_str(), &(csScriptInstance.isActive));
							ImGui::SameLine();

							if (ImGui::TreeNode(std::string{className + " (Script)"}.c_str())) {
								for (auto& [varName, csPublicVariable] : csScriptInstance.csVariableMap) {
									ImGui::Text(varName.c_str());
									ImGui::SameLine();
									switch (csPublicVariable.variableType) {
									case Engine::CSType::CHAR:
										//ImGui::InputFloat("A", (float*)csPublicVariable.GetVariableDataPTR<char>(), 0);
										break;
									case Engine::CSType::BOOL:
										ImGui::Checkbox(std::string{ "##" + varName }.c_str(), &(csPublicVariable.GetVariableData<bool>()));
										break;
									case Engine::CSType::FLOAT:
										ImGui::InputFloat(std::string{ "##" + varName }.c_str(), &(csPublicVariable.GetVariableData<float>()), 0);
										break;
									case Engine::CSType::INT:
										ImGui::InputInt(std::string{"##" + varName}.c_str(), & (csPublicVariable.GetVariableData<int>()), 0);
										break;
									case Engine::CSType::UINT:
										//ImGui::InputFloat("E", (float*)csPublicVariable.GetVariableDataPTR<unsigned int>(), 0);
										break;
									case Engine::CSType::VEC2:
										Math::vec2& tem = csPublicVariable.GetVariableData<Math::vec2>();
										ImGui::InputFloat(std::string{ "##" + varName }.c_str(), &(tem.x), 0);
										ImGui::InputFloat(std::string{ "##" + varName }.c_str(), &(tem.y), 0);
										break;
									}
								}

								ImGui::TreePop();
							}
						}


						//ImGui::TreePop();
					//}
				}


				/**
				*	Add New Components
				*/

				
				const char* items[] = { "AAAA", "BBBB", "CCCC", "DDDD", "EEEE", "FFFF", "GGGG", "HHHH", "IIIIIII", "JJJJ", "KKKKKKK" };
				static int item_current = 1;
				ImGui::Combo("Combo", &item_current, items, IM_ARRAYSIZE(items));

				//if (ImGui::Button("Add Component", (ImVec2{ 100, 0 }))) {
				//	//addComponentBool = true;
				//}


				static bool addComponentBool = false;
				if (ImGui::CollapsingHeader("Add Component", &addComponentBool)) {
					if (ImGui::Button("Transform")) {
						printf("Add Transform\n");
					}

					else if (ImGui::Button("Texture")) {
						printf("Add Texture\n");
					}

					else if (ImGui::Button("Camera")) {
						printf("Add Camera\n");
					}

					else if (ImGui::Button("Rigidbody")) {
						printf("Add Rigidbody\n");
					}

					else if (ImGui::Button("Collider")) {
						printf("Add Collider\n");
					}

					ImGui::EndMenu();
				}

				ImGui::End();
			}
		}

		void GUI_Stats() {
			if (stats_bool) {
				ImGui::Begin("Engine Stats", &stats_bool);
				std::stringstream outputSS;
				outputSS << "FPS: ";
				outputSS.precision(2);
				outputSS << std::fixed << Engine::DeltaTime::GetInstance().GetFPS();
				
				ImGui::Text(outputSS.str().c_str());
				outputSS.str(std::string());

				outputSS << "Entity Count: ";
				outputSS << Engine::DreamECS::GetInstance().GetComponentArraySize<Engine::TransformComponent>();
				ImGui::Text(outputSS.str().c_str());



				ImGui::End();
			}
		}

		void GUI_GameWindow(const ImTextureID& gameWinTex) {
			CreateImageWindow("Game Window", gameWinTex, gameWin_bool);
		}

		//void GUI_SceneWindow(const ImTextureID& sceneWinTex) {
		//	//CreateImageWindow("Scene Window", sceneWinTex, sceneWin_bool);

		//	

		//	
		//}

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