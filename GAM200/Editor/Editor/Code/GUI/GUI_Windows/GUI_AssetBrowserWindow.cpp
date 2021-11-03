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
#include "Engine/Header/Management/FileWindowDialog.hpp"
#include "Engine/Header/Window.hpp"
#include "Engine/Header/Scene/SceneManager.hpp"

#define TEXT_BOX_SIZE 70

#define REMOVE_FROM_FILEPATH size_t pos = filePath.find_last_of("\\");\
							 filePath = filePath.substr(pos + 1);\
							 pos = filePath.find_last_of(".");\
							 filePath = filePath.substr(0, pos);

namespace Editor {

	extern const std::filesystem::path _assetPath = "Assets";
	extern const std::filesystem::path _scenePath = "Assets/Scenes";
	extern const std::filesystem::path _texturePath = "Assets/Textures";

	namespace GUI_Windows {
		static std::filesystem::path _currentDirectory = "Assets";
		
		enum class AssetView {
			TextureBrowser,
			SceneBrowser,
			ScriptBrowser,
			FontBrowser,
			Length
		};

		static AssetView _currentView = AssetView::TextureBrowser;

		static void ShowSceneBrowser()
		{
			if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
			{
				std::string filePath = Engine::FileWindowDialog::OpenFile("Dream Scene (*.scene)\0*.scene\0");

				if (!filePath.empty()) {
					REMOVE_FROM_FILEPATH;

					Engine::SceneManager::GetInstance().ChangeScene(filePath);
				}
			}
		}

		static void ShowTextureBrowser()
		{
			if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
			{
				std::string filePath = Engine::FileWindowDialog::OpenFile("Texture (*.png)\0*.png\0");

				if (!filePath.empty()) {
					REMOVE_FROM_FILEPATH;

					//Engine::SceneManager::GetInstance().ChangeScene(filePath);
				}
			}
		}
		void GUI_AssetBrowser(bool* asset_bool, ImGuiWindowFlags window_flags)
		{
			if (*asset_bool) {
				ImGui::Begin("Project", asset_bool, window_flags);
				
				switch (_currentView)
				{
				case AssetView::TextureBrowser:
					ShowTextureBrowser();
					break;
				case AssetView::SceneBrowser:
					ShowSceneBrowser();
					break;
				default:
					break;
				}
				//all assets
				if (_currentDirectory != std::filesystem::path(_assetPath))
				{
					if (ImGui::Button("Assets"))
					{
						_currentDirectory = _currentDirectory.parent_path();
					}
				}

				if (ImGui::TreeNode("Drag and Drop"))
				{
					if (ImGui::TreeNode("Drag and drop in standard widgets"))
					{
						// ColorEdit widgets automatically act as drag source and drag target.
						// They are using standardized payload strings IMGUI_PAYLOAD_TYPE_COLOR_3F and IMGUI_PAYLOAD_TYPE_COLOR_4F
						// to allow your own widgets to use colors in their drag and drop interaction.
						// Also see 'Demo->Widgets->Color/Picker Widgets->Palette' demo.
						//HelpMarker("You can drag from the color squares.");
						static float col1[3] = { 1.0f, 0.0f, 0.2f };
						static float col2[4] = { 0.4f, 0.7f, 0.0f, 0.5f };
						ImGui::ColorEdit3("color 1", col1);
						ImGui::ColorEdit4("color 2", col2);
						ImGui::TreePop();
					}

					if (ImGui::TreeNode("Drag and drop to copy/swap items"))
					{
						enum Mode
						{
							Mode_Copy,
							Mode_Move,
							Mode_Swap
						};
						static int mode = 0;
						if (ImGui::RadioButton("Copy", mode == Mode_Copy)) { mode = Mode_Copy; } ImGui::SameLine();
						if (ImGui::RadioButton("Move", mode == Mode_Move)) { mode = Mode_Move; } ImGui::SameLine();
						if (ImGui::RadioButton("Swap", mode == Mode_Swap)) { mode = Mode_Swap; }
						static const char* names[9] =
						{
							"Bobby", "Beatrice", "Betty",
							"Brianna", "Barry", "Bernard",
							"Bibi", "Blaine", "Bryn"
						};
						for (int n = 0; n < IM_ARRAYSIZE(names); n++)
						{
							ImGui::PushID(n);
							if ((n % 3) != 0)
								ImGui::SameLine();
							ImGui::Button(names[n], ImVec2(60, 60));

							// Our buttons are both drag sources and drag targets here!
							if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
							{
								// Set payload to carry the index of our item (could be anything)
								ImGui::SetDragDropPayload("DND_DEMO_CELL", &n, sizeof(int));

								// Display preview (could be anything, e.g. when dragging an image we could decide to display
								// the filename and a small preview of the image, etc.)
								if (mode == Mode_Copy) { ImGui::Text("Copy %s", names[n]); }
								if (mode == Mode_Move) { ImGui::Text("Move %s", names[n]); }
								if (mode == Mode_Swap) { ImGui::Text("Swap %s", names[n]); }
								ImGui::EndDragDropSource();
							}
							if (ImGui::BeginDragDropTarget())
							{
								if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DND_DEMO_CELL"))
								{
									IM_ASSERT(payload->DataSize == sizeof(int));
									int payload_n = *(const int*)payload->Data;
									if (mode == Mode_Copy)
									{
										names[n] = names[payload_n];
									}
									if (mode == Mode_Move)
									{
										names[n] = names[payload_n];
										names[payload_n] = "";
									}
									if (mode == Mode_Swap)
									{
										const char* tmp = names[n];
										names[n] = names[payload_n];
										names[payload_n] = tmp;
									}
								}
								ImGui::EndDragDropTarget();
							}
							ImGui::PopID();
						}
						ImGui::TreePop();
					}
					ImGui::TreePop();
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
					if (ImGui::BeginDragDropSource())
					{
						const wchar_t* itemPath = relative_path.c_str();
						ImGui::SetDragDropPayload("CONTENT_BROWSER_ITEM", itemPath, (wcslen(itemPath) + 1) * sizeof(wchar_t));
						ImGui::EndDragDropSource();
					}
					if (_currentDirectory != std::filesystem::path(_scenePath))
					{
						ShowTextureBrowser();
					}
					if (_currentDirectory != std::filesystem::path(_texturePath))
					{
						ShowSceneBrowser();
					}
				
					//for scene
					//if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
					//{
					//	std::string filePath = Engine::FileWindowDialog::OpenFile("Dream Scene (*.scene)\0*.scene\0");

					//	if (!filePath.empty()) {
					//		REMOVE_FROM_FILEPATH;

					//		Engine::SceneManager::GetInstance().ChangeScene(filePath);
					//	}
					//}
					//for (auto& scene_directory : std::filesystem::directory_iterator("Assets/Scenes/"))
					//{
					//	if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
					//	{
					//		std::string filePath = Engine::FileWindowDialog::OpenFile("Dream Scene (*.scene)\0*.scene\0");

					//		if (!filePath.empty()) {
					//			REMOVE_FROM_FILEPATH;

					//			Engine::SceneManager::GetInstance().ChangeScene(filePath);
					//		}
					//	}
					//}

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