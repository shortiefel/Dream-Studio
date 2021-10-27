/* Start Header**********************************************************************************/
/*
@file    GUI_AssetBrowser.cpp
@author  Goh See Yong, Denise   g.seeyongdenise@digipen.edu
@date    26/07/2021
\brief
This file contain the GUI Asset browser definition


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Editor/Header/GUI/GUI_Windows/GUI_AssetBrowserWindow.hpp"
#include "Engine/Header/Management/AssetManager.hpp"

#include "Engine/Header/Scene/SceneManager.hpp"

namespace Editor {

	extern const std::filesystem::path _assetPath = "Assets";

	namespace GUI_Windows {
		static std::filesystem::path _currentDirectory = "Assets";

		enum class AssetView {
			TextureBrowser,
			SceneBrowser,
			ScriptBrowser,
			FontBrowser,
			Length
		};

		static AssetView _currentView = AssetView::SceneBrowser;
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
					if (filenameString == "Assets/Scenes/test2.scene")
					{
						Engine::SceneManager::GetInstance().ChangeScene("test2");
					}

					else if (relative_path.string() == "Scenes/test3.scene")
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

		void GUI_AssetBrowser(bool* asset_bool, ImGuiWindowFlags window_flags)
		{
			if (*asset_bool) {
				ImGui::Begin("Project", asset_bool, window_flags);
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

				//ShowMenuBar();
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
				if (_currentDirectory != std::filesystem::path(_assetPath))
				{
					if (ImGui::Button("Assets"))
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

				for (auto& directory : std::filesystem::directory_iterator(_currentDirectory))
				{
					const auto& path = directory.path();
					auto relative_path = std::filesystem::relative(path, _assetPath);
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
	}
}