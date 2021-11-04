/* Start Header**********************************************************************************/
/*
@file    GUI_PrefabWindow.cpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    02/11/2021
\brief
#include "Editor/Header/GUI/GUI_Windows/GUI_PrefabWindow.hpp"
This file has the function declaration for GUI Prefab window
The prefab window allow users to


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Editor/Header/GUI/GUI_Windows/GUI_PrefabWindow.hpp"

#include "Engine/Header/Management/FileWindowDialog.hpp"
#include "Engine/Header/Serialize/GameSceneSerializer.hpp"
#include "Engine/Header/ECS/DreamECS.hpp"

#include <string>

namespace Editor {
	namespace GUI_Windows {
		/*void ChangePrefab(std::string filepath) {
			Engine::dreamECSPrefab->ResetECS();
			Engine::GameSceneSerializer::DeserializePrefab(filepath);
		}

		void NewFileUtilPrefab() {
			std::string filePath = Engine::FileWindowDialog::SaveFile("Dream prefab (*.prefab)\0*.prefab\0");

			if (!filePath.empty()) {
				REMOVE_FROM_FILEPATH;

				Engine::dreamECSPrefab->ResetECS();
				Engine::GameSceneSerializer::SerializePrefab(filePath);
				ChangePrefab(std::move(filePath));
			}
		}

		void OpenFileUtilPrefab() {
			std::string filePath = Engine::FileWindowDialog::OpenFile("Dream Prefab (*.prefab)\0*.prefab\0");

			if (!filePath.empty()) {
				REMOVE_FROM_FILEPATH;

				ChangePrefab(std::move(filePath));
			}
		}

		void SaveFileUtilPrefab() {
			std::string filePath = Engine::FileWindowDialog::SaveFile("Dream Prefab (*.prefab)\0*.prefab\0");

			if (!filePath.empty()) {
				REMOVE_FROM_FILEPATH;

				Engine::GameSceneSerializer::SerializePrefab(filePath);
				ChangePrefab(std::move(filePath));
			}
		}

		void SaveAsFileUtilPrefab() {
			std::string filePath = Engine::FileWindowDialog::SaveFile("Dream Prefab (*.prefab)\0*.prefab\0");

			if (!filePath.empty()) {
				REMOVE_FROM_FILEPATH;

				Engine::GameSceneSerializer::SerializePrefab(filePath);
				ChangePrefab(std::move(filePath));
			}
		}*/

		void GUI_Prefab(bool* prefab_bool, ImGuiWindowFlags window_flags) {
			/*if (*prefab_bool) {
				ImGui::Begin("Prefab Customizer", prefab_bool);

				if (ImGui::BeginMenu("File")) {
					if (ImGui::MenuItem("New Scene", "CTRL+N")) {
						NewFileUtilPrefab();
					}

					if (ImGui::MenuItem("Open...", "CTRL+O")) {
						OpenFileUtilPrefab();
					}

					else if (ImGui::MenuItem("Save", "CTRL+S")) {
						SaveFileUtilPrefab();
					}

					else if (ImGui::MenuItem("Save as...", "CTRL+SHIFT+S")) {
						SaveAsFileUtilPrefab();
					}

					ImGui::EndMenu();
				}

				ImGui::End();
			}*/
		}
	}
}