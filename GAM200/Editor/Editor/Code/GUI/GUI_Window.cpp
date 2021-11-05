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
#include "Editor/Header/GUI/GUI_Windows/GUI_ProfilerWindow.hpp"
#include "Editor/Header/GUI/GUI_Windows/GUI_ConsoleWindow.hpp"
#include "Editor/Header/GUI/GUI_Windows/GUI_SceneWindow.hpp"
#include "Editor/Header/GUI/GUI_Windows/GUI_GameWindow.hpp"
#include "Editor/Header/GUI/GUI_Windows/GUI_AssetBrowserWindow.hpp"
#include "Editor/Header/GUI/GUI_Windows/GUI_InspectorWindow.hpp"
#include "Editor/Header/GUI/GUI_Windows/GUI_HierarchyWindow.hpp"
#include "Editor/Header/GUI/GUI_Windows/GUI_StatsWindow.hpp"
#include "Editor/Header/GUI/GUI_ClickCheck.hpp"

#include "Editor/Header/FunctionOverride.hpp"
#include "Editor/Header/Scene/EditorSceneManager.hpp"

#include <Imgui/imgui_internal.h>
#include <map>

#include "Engine/Header/Scene/SceneManager.hpp"
#include "Engine/Header/Management/FileWindowDialog.hpp"
#include "Engine/Header/Management/GameState.hpp"
#include "Engine/Header/Serialize/GameSceneSerializer.hpp"
#include "Engine/Header/Window.hpp"
#include "Engine/Header/Event/EventDispatcher.hpp"
#include "Engine/Header/Event/KeyEvent.hpp"
#include "Engine/Header/ECS/Component/ComponentArray.hpp"
#include "Engine/Header/ECS/Component/Graphics/TransformComponent.hpp"
#include "Engine/Header/Management/TextureManager.hpp"

//#include "Engine/Header/Script/Scripting.hpp"
//#include "Engine/Header/Script/ScriptInternalCall.hpp"
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

#define TEXT_BOX_SIZE 70

namespace Editor {
	namespace GUI_Windows {
		//bool for dockspace (will always be true)
		bool dockspace_bool = true;
		//Flags for the background window for windows to dock to
		ImGuiWindowFlags dockspace_window_flags = 0;
		ImGuiDockNodeFlags dockspace_dock_flags = 0;

		ImGuiWindowFlags window_flags = 0;


		std::map<int, Engine::Entity_id> entity_selected{};

		ImTextureID iconPlay;
		ImTextureID iconStop;

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
		
		static ImVec2	 buttonSize{ 128, 128 };
		// Forward declarations
		//static void ShowMenuBar();
		////static void ShowTextureBrowser();
		//static void ShowSceneBrowser();
		////static void ShowFontBrowser();
		//static bool IconButton(const char* icon, const char* label, const ImVec2& size);

		void    GUI_HeaderPanel();

		void	NewFileUtil();
		void	OpenFileUtil();
		void	SaveAsFileUtil();
		bool	OnKeyEvent(Engine::KeyPressedEvent& e);

		/*-------------------------------------------------------------------------------------------------
		Utilities
		-------------------------------------------------------------------------------------------------*/
		void NewFileUtil() {
			if (Engine::GameState::GetInstance().GetPlaying()) {
				GUI_Windows::GUI_Console_Add(GUI_Windows::ConsoleString{ "Scene is Playing. unable to create new file..." });
				return;
			}

			std::string filePath = Engine::FileWindowDialog::SaveFile("Dream Scene (*.scene)\0*.scene\0");

			if (!filePath.empty()) {
				REMOVE_FROM_FILEPATH;

				Engine::DreamECS::GetInstance().ResetECS();
				Engine::GameSceneSerializer::SerializeScene(filePath);
				Engine::SceneManager::GetInstance().ChangeScene(std::move(filePath));
			}
		}
		
		void OpenFileUtil() {
			std::string filePath = Engine::FileWindowDialog::OpenFile("Dream Scene (*.scene)\0*.scene\0");

			if (!filePath.empty()) {
				REMOVE_FROM_FILEPATH;

				Engine::SceneManager::GetInstance().ChangeScene(std::move(filePath));
			}
		}

		void SaveAsFileUtil() {
			if (Engine::GameState::GetInstance().GetPlaying()) {
				GUI_Windows::GUI_Console_Add(GUI_Windows::ConsoleString{ "Scene is Playing. unable to save as..." });
				return;
			}

			std::string filePath = Engine::FileWindowDialog::SaveFile("Dream Scene (*.scene)\0*.scene\0");

			if (!filePath.empty()) {
				REMOVE_FROM_FILEPATH;

				Engine::GameSceneSerializer::SerializeScene(filePath);
				Engine::SceneManager::GetInstance().ChangeScene(std::move(filePath));
			}
		}

		bool OnKeyEvent(const Engine::KeyPressedEvent& e) {
			bool ctrl = Engine::Input::IsKeyHold(Engine::Input_KeyCode::Control);
			bool shift = Engine::Input::IsKeyHold(Engine::Input_KeyCode::Shift);

			switch (e.GetKeyCode()) {
			case Engine::Input_KeyCode::N: {
				if (ctrl) {
					NewFileUtil();
				}
				break;
			}
			case Engine::Input_KeyCode::O: {
				if (ctrl) {
					OpenFileUtil();
				}
				break;
			}
			case Engine::Input_KeyCode::S: {
				if (ctrl && shift) {
					SaveAsFileUtil();
				}

				else if (ctrl) {
					EditorSceneManager::GetInstance().EditorSceneSave();
				}
				break;
			}
			case Engine::Input_KeyCode::P: {
				if (ctrl) {
					EditorSceneManager::GetInstance().EditorScenePlay();
				}
				break;
			}
			}

			return true;
		}

		/*-------------------------------------------------------------------------------------------------
		Windows creation: Hierarchy, Inspector, Game window, Scene window
		-------------------------------------------------------------------------------------------------*/

		void GUI_Settings_Setup() {
			dockspace_window_flags |= ImGuiWindowFlags_NoTitleBar;
			dockspace_window_flags |= ImGuiWindowFlags_NoMove;
			dockspace_window_flags |= ImGuiWindowFlags_NoResize;
			dockspace_window_flags |= ImGuiWindowFlags_NoBackground;
			dockspace_window_flags |= ImGuiWindowFlags_MenuBar;

			dockspace_dock_flags |= ImGuiDockNodeFlags_PassthruCentralNode;

			GUI_Windows::GUI_Console_Create();

			GUI_Windows::GUI_SceneSetup();

			Engine::KeyPressedEvent::RegisterFunction(OnKeyEvent);

			Override_Function();

			int heightIcon = 25;
			int widthIcon = 25;
			unsigned int* tex_ptr = reinterpret_cast<unsigned int*>(&iconPlay);
			*tex_ptr = Engine::TextureManager::GetInstance().LoadTexture("Assets/Textures/PlayButton.png", &heightIcon, &widthIcon, 0, 4);
			unsigned int* tex2_ptr = reinterpret_cast<unsigned int*>(&iconStop);
			*tex2_ptr = Engine::TextureManager::GetInstance().LoadTexture("Assets/Textures/StopButton.png", &heightIcon, &widthIcon, 0, 4);
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
				if (ImGui::MenuItem("New Scene", "CTRL+N")) {
						NewFileUtil();
				}

				if (ImGui::MenuItem("Open...", "CTRL+O")) {
					OpenFileUtil();
				}

				else if (ImGui::MenuItem("Save", "CTRL+S")) {
					EditorSceneManager::GetInstance().EditorSceneSave();
				}

				else if (ImGui::MenuItem("Save as...", "CTRL+SHIFT+S")) {
					SaveAsFileUtil();
				}

				if (ImGui::MenuItem("Quit", NULL)) {
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
				ImGui::MenuItem("Asset Browser", NULL, &asset_bool);
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
		void All_Windows(const Engine::Graphic::FrameBuffer& gameWinFBO, const Engine::Graphic::FrameBuffer& sceneWinFBO) {
			GUI_HeaderPanel();
			GUI_GameWindow(&gameWin_bool, gameWinFBO, window_flags);
			GUI_SceneWindow(&sceneWin_bool, sceneWinFBO, entity_selected, window_flags);
			GUI_Hierarchy(&hierarchy_bool, entity_selected, window_flags);
			GUI_Inspector(&inspector_bool, TEXT_BOX_SIZE, GetTarget(entity_selected), window_flags);
			GUI_Stats(&stats_bool);
			GUI_Profiler(&profiler_bool);
			GUI_AssetBrowser(&asset_bool, window_flags);
			GUI_Console(&console_bool, window_flags);

			SelectedEntityCheck(entity_selected);
		}

		void GUI_HeaderPanel() {
			//Will always be on so dont need check

			/**
			*	WIDTH
			*/
			float halfWidth = ImGui::GetContentRegionAvail().x / 0.3484f;
			

			ImVec2 wSize = ImGui::GetWindowSize();
			ImGui::Begin("Actions", &playStop_bool, window_flags);

			ImGui::PushItemWidth(wSize.x);
			ImGui::PushItemFlag(ImGuiItemFlags_Disabled, Engine::GameState::GetInstance().GetPlaying());

			ImGui::SameLine(halfWidth);
			if (ImGui::ImageButton(iconPlay, { 25, 25 }, { 0,1 }, { 1, 0 })) {

				if (!EditorSceneManager::GetInstance().Play()) Engine::GameState::GetInstance().SetPlaying(false);
			}
			ImGui::PopItemFlag();

			ImGui::SameLine();
			ImGui::PushItemWidth(wSize.x / 2);
			ImGui::PushItemFlag(ImGuiItemFlags_Disabled, !(Engine::GameState::GetInstance().GetPlaying()));
			if (ImGui::ImageButton(iconStop, { 25, 25 }, { 0,1 }, { 1, 0 })) {
				EditorSceneManager::GetInstance().Stop();
			}
			ImGui::PopItemFlag();



			ImGui::End();

		}


		//static void ShowMenuBar()
		//{
		//	ImGui::BeginGroup();

		//	std::array<const char*, 128> assetViews = { "Texture Browser", "Scene Browser", "Script Browser", "Font Browser" };
		//	//ImGui::UndoableCombo<AssetView>(m_CurrentView, "Asset View", assetViews.data(), (int)AssetView::Length);
		//	ImGui::EndGroup();
		//	ImGui::Separator();
		//}

		//static bool IconButton(const char* icon, const char* label, const ImVec2& size)
		//{
		//	ImGui::BeginGroup();
		//	//ImGui::PushFont(Settings::EditorStyle::s_LargeIconFont);
		//	bool res = ImGui::Button(icon, ImVec2(size.x, size.y));
		//	ImGui::PopFont();

		//	ImVec2 textSize = ImGui::CalcTextSize(label);
		//	ImGui::SetCursorPos(ImGui::GetCursorPos());
		//	ImGui::Text(label);
		//	ImGui::EndGroup();
		//	return res;
		//}
		

		/*-------------------------------------------------------------------------------------------------
		-------------------------------------------------------------------------------------------------*/

	}
}