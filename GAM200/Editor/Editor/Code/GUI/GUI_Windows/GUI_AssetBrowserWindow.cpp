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

#include "Engine/Header/Debug Tools/Logging.hpp"
#include "Editor/Header/GUI/GUI_Windows/GUI_AssetBrowserWindow.hpp"
#include "Engine/Header/Management/AssetManager.hpp"
#include "Engine/Header/Management/FileWindowDialog.hpp"
#include "Engine/Header/Window.hpp"
#include "Engine/Header/Scene/SceneManager.hpp"
#include "Engine/Header/Scene/Scene.hpp"

#define TEXT_BOX_SIZE 70

namespace Editor {

	extern const std::filesystem::path _assetPath = "Assets";

	namespace GUI_Windows {
		static std::filesystem::path _currentDirectory = "Assets";
	

		void OpenScene()
		{
				std::string filePath = Engine::FileWindowDialog::OpenFile("Dream Scene (*.scene)\0*.scene\0");

					if (!filePath.empty()) {
						REMOVE_FROM_FILEPATH;

						Engine::SceneManager::GetInstance().ChangeScene(filePath);
					}		
		}

		void OpenScene(const std::filesystem::path& path)
		{
			if (path.extension().string() != ".scene")
			{
				LOG_INSTANCE("Cannot load scene file");
				return;
			}

			std::string newScene = std::string{};
			

		}
		void GUI_AssetBrowser(bool* asset_bool, ImGuiWindowFlags window_flags)
		{
			if (*asset_bool) {
				ImGui::Begin("Project", asset_bool, window_flags);
				
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
				int height = 128;
				int width = 10;

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
					auto directory_icon = Engine::TextureManager::GetInstance().LoadTexture("Assets/Textures/DirectoryIcon.png", &height, &width, 0, 4);
					auto file_icon = Engine::TextureManager::GetInstance().LoadTexture("Assets/Textures/FileIcon.png", &height, &width, 0, 4);
					auto asset_icon = directory.is_directory() ? directory_icon : file_icon;
					ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
					ImGui::ImageButton((ImTextureID)asset_icon, { thumbnailSize, thumbnailSize }, { 0, 1 }, { 1, 0 });
					const wchar_t* itemPath = relative_path.c_str();
					if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID))
					{
						const wchar_t* itemPath = relative_path.c_str();
						ImGui::Text("I'm Dragging.");
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