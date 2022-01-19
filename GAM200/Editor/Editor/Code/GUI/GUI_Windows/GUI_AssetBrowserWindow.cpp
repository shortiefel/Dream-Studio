/* Start Header**********************************************************************************/
/*
@file    GUI_AssetBrowser.cpp
@author  Goh See Yong, Denise   g.seeyongdenise@digipen.edu	100%
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
#define REMOVE_FROM_SCENEPATH scenePath = scenePath.string().substr(scenePath.string().find_last_of("\\") + 1);\
							 scenePath = scenePath.string().substr(0, scenePath.string().find_last_of("."));

namespace Editor {

	extern const std::filesystem::path _assetPath = "Assets";

	namespace GUI_Windows {
		static std::filesystem::path _currentDirectory = "Assets";

		void OpenScene()
		{
			std::string filePath = Engine::FileWindowDialog::OpenFile("Dream Scene (*.scene)\0*.scene\0", Engine::File_Dialog_Type::Scenes);

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
				ImGui::Begin("Assets Manager", asset_bool, window_flags);
				
				//all assets
				if (_currentDirectory != std::filesystem::path(_assetPath))
				{
					if (ImGui::Button("Back"))
					{
						_currentDirectory = _currentDirectory.parent_path();
					}
				}

				static float padding = 16.0f;
				static float thumbnailSize = 128.0f;
				float cellSize = thumbnailSize + padding;
				int height = 128;
				int width = 10;
				int counter = 0;

				float panelWidth = ImGui::GetContentRegionAvail().x;
				int columnCount = (int)(panelWidth / cellSize);
				if (columnCount < 1)
					columnCount = 1;

				ImGui::Columns(columnCount, 0, false);

				for (auto& directory : std::filesystem::directory_iterator(_currentDirectory))
				{
					const auto& path = directory.path();
					auto relative_path = std::filesystem::relative(path, _assetPath);
					std::string file_name = relative_path.filename().string();
					std::string final_path = "Assets/Textures/";
					final_path += file_name;
					if (_currentDirectory == "Assets\\Textures")
					{
						GLuint textureicon = Engine::ResourceManager::GetInstance().LoadTexture(final_path);
						GLuint directory_icon = Engine::ResourceManager::GetInstance().LoadTexture("Assets/Textures/DirectoryIcon.png", &height, &width, 0, 4);
						std::string filter = file_name.substr(file_name.size() - 3, file_name.size());
						ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));

						if (filter == "png")
						{
							ImGui::ImageButton((ImTextureID)static_cast<uintptr_t>(textureicon), { thumbnailSize , thumbnailSize }, { 0,1 }, { 1 , 0 });
						}
						else
						{
							ImGui::ImageButton((ImTextureID)static_cast<uintptr_t>(directory_icon), { thumbnailSize , thumbnailSize }, { 0,1 }, { 1 , 0 });
						}
						ImGui::PopStyleColor();

					}
					else
					{
						ImGui::PushID(counter);
						GLuint directory_icon = Engine::ResourceManager::GetInstance().LoadTexture("Assets/Textures/DirectoryIcon.png", &height, &width, 0, 4);
						GLuint file_icon = Engine::ResourceManager::GetInstance().LoadTexture("Assets/Textures/FileIcon.png", &height, &width, 0, 4);
						GLuint asset_icon = directory.is_directory() ? directory_icon : file_icon;
						ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
						ImGui::ImageButton((ImTextureID)static_cast<uintptr_t>(asset_icon), { thumbnailSize, thumbnailSize }, { 0, 1 }, { 1, 0 });
						ImGui::PopStyleColor();
						ImGui::PopID();
						counter++;
					}
				
					if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID))
					{
						const wchar_t* itemPath = relative_path.c_str();
						ImGui::Text("%s", file_name.c_str());
						ImGui::SetDragDropPayload("CONTENT_BROWSER_ITEM", itemPath, (wcslen(itemPath) + 1) * sizeof(wchar_t));
						ImGui::EndDragDropSource();
					}
			

					if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
					{
						if (directory.is_directory())
						{
							_currentDirectory /= path.filename();
						}

						std::filesystem::path scenePath = std::filesystem::path(_assetPath) / path;
						if (scenePath.extension().string() != ".scene")
						{
							std::cout << "Unable to load scene file\n";
						}
						else {
							if (!scenePath.filename().string().empty())
							{
								REMOVE_FROM_SCENEPATH;
								scenePath.replace_extension("");
								Engine::SceneManager::GetInstance().ChangeScene(std::move(scenePath.string()));
							}
						}
					}

					//create new folder
					//if (ImGui::BeginPopupContextItem("##AssetPanel"))
					//{
					//	if (ImGui::Button("Create Folder##CreateFolder", { ImGui::GetContentRegionAvail().x, 0 }))
					//	{
					//		std::filesystem::create_directories(_assetPath.string() + " New Folder");
					//	}
					//	ImGui::EndPopup();
					//}

					ImGui::TextWrapped(file_name.c_str());

					ImGui::NextColumn();


				}

				ImGui::Columns(1);

				ImGui::SliderFloat("Thumbnail Size", &thumbnailSize, 16, 512);
				ImGui::SliderFloat("Padding", &padding, 0, 32);

				ImGui::End();
			}
		}
		void LoadAllAssets(const std::string& path)
		{
			const std::filesystem::path dir{ path };
			for (auto& i : std::filesystem::directory_iterator{ dir })
			{
				if (is_directory(i))
				{
					LoadAllAssets(i.path().generic_string());
				}
				else
				{
					if (i.path().extension() == ".png" || i.path().extension() == ".PNG")
					{
						Engine::ResourceManager::GetInstance().LoadTexture(i.path().generic_string());
					}
				}
			}
		}
	}
}