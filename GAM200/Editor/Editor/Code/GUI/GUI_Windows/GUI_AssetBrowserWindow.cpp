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

		void GUI_AssetBrowser(bool* asset_bool, ImGuiWindowFlags window_flags)
		{
			if (asset_bool) {
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
					ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
					ImGui::ImageButton((ImTextureID)directory_icon, { thumbnailSize, thumbnailSize }, { 0, 1 }, { 1, 0 });
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

				ImGui::End();
			}
		}
	}
}