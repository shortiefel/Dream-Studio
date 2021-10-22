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
#include "Editor/Header/GUI/GUI_Windows/GUI_GameWindow.hpp"
#include "Editor/Header/Scene/EditorSceneManager.hpp"
#include "Engine/Header/Scene/SceneManager.hpp"
#include "Engine/Header/Management/AssetManager.hpp"

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


//Create a window with an image
//E.g Game window 
//#define CreateImageWindow(windowName, texid, windowBool) \
//	if (windowBool) {\
//		ImGui::Begin(windowName, &windowBool, window_flags);\
//		ImGui::BeginChild("Render");\
//		ImVec2 wSize = ImGui::GetWindowSize();\
//		\
//		ImGui::PushItemWidth(wSize.x);\
//		ASPECT_RATIO_FIX(wSize);\
//		\
//		ImGui::Image((ImTextureID)texid, wSize, ImVec2(0, 1), ImVec2(1, 0));\
//		ImGui::EndChild();\
//		ImGui::End();\
//	}\



namespace Editor {

	extern const std::filesystem::path _assetPath = "Assets";

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
		//Menu to undo and redo scene
		void    GUI_EditMenu();

		//Internal Variables
		static AssetView _currentView = AssetView::SceneBrowser;
		static ImVec2	 buttonSize{ 128, 128 };
		// Forward declarations
		static void ShowMenuBar();
		//static void ShowTextureBrowser();
		static void ShowSceneBrowser();
		//static void ShowFontBrowser();
		static bool IconButton(const char* icon, const char* label, const ImVec2& size);

		/*-------------------------------------------------------------------------------------------------
		Windows creation: Hierarchy, Inspector, Game window, Scene window
		-------------------------------------------------------------------------------------------------*/
		void    GUI_HeaderPanel();
		void	GUI_Hierarchy();
		void	GUI_Inspector();
		//Show stats like fps and Number of game object
		void	GUI_Stats();
		//Profiler window
		//void	GUI_GameWindow(const ImTextureID& gameWinTex);
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
				GUI_EditMenu();
				GUI_WindowsMenu();

				ImGui::EndMenuBar();

			}

		}

		//Menu for files
		void GUI_FileMenu() {
			if (ImGui::BeginMenu("File")) {
				bool quit = false;
				if (ImGui::MenuItem("New Scene", "CTRL+N"))
				{
					Engine::SceneManager::GetInstance().ChangeScene("test1");
				}
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

		//Menu to undo and redo scene
		void GUI_EditMenu() {
			if (ImGui::BeginMenu("Edit")) {

				ImGui::MenuItem("Undo", "CTRL+Z");
				ImGui::MenuItem("Redo", "CTRL+Y");


				ImGui::EndMenu();
			}

		}

		/*int GetSceneSizeX() {
			return GUI_GetSceneWindowSizeX();
		}   
		int GetSceneSizeY() {
			return GUI_GetSceneWindowSizeY();
		}*/
		/*-------------------------------------------------------------------------------------------------
		-------------------------------------------------------------------------------------------------*/

		/*-------------------------------------------------------------------------------------------------
		Windows creation: Header, Hierarchy, Inspector, Game window, Scene window, Asset Manager
		-------------------------------------------------------------------------------------------------*/
		//void All_Windows(const ImTextureID& gameWinTex, const ImTextureID& sceneWinTex) {
		void All_Windows(const Engine::Graphic::FrameBuffer& gameWinFBO, const Engine::Graphic::FrameBuffer& sceneWinFBO) {
			GUI_GameWindow(&gameWin_bool, gameWinFBO, entity_selected);
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

						//deleteComponent
						if (ImGui::Button("Delete Component##DeleteTransform", { ImGui::GetContentRegionAvail().x, 0 }))
							Engine::DreamECS::GetInstance().RemoveComponent<Engine::TransformComponent>(entity_selected);

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

						//deleteComponent
						if (ImGui::Button("Delete Component##DeleteCollider", { ImGui::GetContentRegionAvail().x, 0 }))
							Engine::DreamECS::GetInstance().RemoveComponent<Engine::ColliderComponent>(entity_selected);

						ImGui::TreePop();
					}
				}

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

							if (ImGui::TreeNode(std::string{ className + " (Script)" }.c_str())) {
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
										ImGui::InputInt(std::string{ "##" + varName }.c_str(), &(csPublicVariable.GetVariableData<int>()), 0);
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

								//deleteComponent
								if (ImGui::Button("Delete Component##DeleteScript", { ImGui::GetContentRegionAvail().x, 0 }))
									Engine::DreamECS::GetInstance().RemoveComponent<Engine::ScriptComponent>(entity_selected);

								ImGui::TreePop();
							}
						}
				}


				/**
				*	Add New Components
				*/

				if (ImGui::Button("Add Component##addcomponentbtn", { ImGui::GetContentRegionAvail().x, 0 }))
				{
					ImGui::OpenPopup("##addcomponentpopup");
				}
				if (ImGui::BeginPopup("##addcomponentpopup"))
				{
					float AvailWidth = ImGui::GetContentRegionAvail().x;
					ImGui::PushItemWidth(AvailWidth);

					if (ImGui::Selectable("Transform##addTransformcom"))
						Engine::DreamECS::GetInstance().AddComponent<Engine::TransformComponent>(entity_selected);
					if (ImGui::Selectable("Collider##addTCollidercom"))
						Engine::DreamECS::GetInstance().AddComponent<Engine::ColliderComponent>(entity_selected);
					if (ImGui::Selectable("Script##addScriptcom"))
						Engine::DreamECS::GetInstance().AddComponent<Engine::ScriptComponent>(entity_selected);
					if (ImGui::Selectable("Camera##addCameracom"))
						Engine::DreamECS::GetInstance().AddComponent<Engine::CameraComponent>(entity_selected);

					ImGui::EndPopup();
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

		/*void GUI_GameWindow(const ImTextureID& gameWinTex) {
			CreateImageWindow("Game Window", gameWinTex, gameWin_bool);
		}*/

		//void GUI_SceneWindow(const ImTextureID& sceneWinTex) {
		//	//CreateImageWindow("Scene Window", sceneWinTex, sceneWin_bool);

		//	

		//	
		//}

		static void ShowMenuBar()
		{
			ImGui::BeginGroup();

			std::array<const char*, 128> assetViews = { "Texture Browser", "Scene Browser", "Script Browser", "Font Browser" };
			//ImGui::UndoableCombo<AssetView>(m_CurrentView, "Asset View", assetViews.data(), (int)AssetView::Length);
			ImGui::EndGroup();
			ImGui::Separator();
		}

		static bool IconButton(const char* icon, const char* label, const ImVec2& size)
		{
			ImGui::BeginGroup();
			//ImGui::PushFont(Settings::EditorStyle::s_LargeIconFont);
			bool res = ImGui::Button(icon, ImVec2(size.x, size.y));
			ImGui::PopFont();

			ImVec2 textSize = ImGui::CalcTextSize(label);
			ImGui::SetCursorPos(ImGui::GetCursorPos());
			ImGui::Text(label);
			ImGui::EndGroup();
			return res;
		}

		static void ShowSceneBrowser()
		{
			if (_currentDirectory != std::filesystem::path(_assetPath))
			{
				if (ImGui::Button("Assets"))
				{
					_currentDirectory = _currentDirectory.parent_path();
				}
			}
			//int sceneCount = 0;
			for (auto& directory : std::filesystem::directory_iterator("Assets/Scenes"))
			{
				const auto& path = directory.path();
				auto relative_path = std::filesystem::relative(path, "Assets/Scenes");
				std::string filenameString = relative_path.string();

				ImGui::PushID(filenameString.c_str());
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
				ImGui::ImageButton((ImTextureID)directory.is_character_file(), { 128, 128 }, { 0, 1 }, { 1, 0 });
				ImGui::PopStyleColor();
				//ImGui::PushID(sceneCount++);
				if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
				{
					if (relative_path == "Scenes\test2.scene")
					{
						Engine::SceneManager::GetInstance().ChangeScene("test2");
					}

					else if (relative_path.string() == "Scenes\test3.scene")
					{
						Engine::SceneManager::GetInstance().ChangeScene("test3");
					}

					else
					{
						Engine::SceneManager::GetInstance().ChangeScene("test1");
					}

				}
				ImGui::TextWrapped(filenameString.c_str());

				ImGui::NextColumn();

				ImGui::PopID();

			}
			ImGui::Columns(1);
		}

		void GUI_ContentBrowserPanel()
		{
			if (asset_bool) {
				ImGui::Begin("Project", &asset_bool, window_flags);
				if (ImGui::TreeNode("Create")) {
					ImGui::Spacing();
					if (ImGui::Button("Folder", (ImVec2{ 100, 30 })))
					{
						//ImGui::SameLine();
						ImGui::Text("Folder created.");
					}

					ImGui::SameLine();
					if (ImGui::Button("New Scene", (ImVec2{ 100, 30 }))) {

						//add new scene
						Engine::SceneManager::GetInstance().ChangeScene("test1");
					}
					ImGui::TreePop();
				}

				ShowMenuBar();
				ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetStyleColorVec4(ImGuiCol_FrameBgActive));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImGui::GetStyleColorVec4(ImGuiCol_FrameBgHovered));
				ImGui::PushStyleColor(ImGuiCol_Text, ImGui::GetStyleColorVec4(ImGuiCol_Text));
				ImGui::PushStyleColor(ImGuiCol_TextDisabled, ImGui::GetStyleColorVec4(ImGuiCol_TextDisabled));

				switch (_currentView)
				{
					//case AssetView::TextureBrowser:
					//	ShowTextureBrowser();
					//	break;
				case AssetView::SceneBrowser:
					ShowSceneBrowser();
					break;
					//case AssetView::ScriptBrowser:
					//	ShowScriptBrowser();
					//	break;
					//case AssetView::FontBrowser:
					//	ShowFontBrowser();
					//	break;
				default:
					//Log::Warning("Unkown asset view: %d", (int)m_CurrentView);
					break;
				}

				ImGui::PopStyleColor(4);

				//all assets
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
					ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
					ImGui::ImageButton((ImTextureID)directory.is_directory(), { thumbnailSize, thumbnailSize }, { 0, 1 }, { 1, 0 });
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