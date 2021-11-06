
#include "Editor/Header/GUI/GUI_Windows/GUI_HierarchyWindow.hpp"

#include "Editor/Header/GUI/GUI_ClickCheck.hpp"

#include "Engine/Header/Input/Input.hpp"

#include "Engine/Header/Commands/Command.hpp"
#include "Engine/Header/Commands/ObjectCommand.hpp"

#include <algorithm>

namespace Editor {
	namespace GUI_Windows {
		void GUI_Hierarchy(bool* hierarchy_bool, std::map<int, Engine::Entity_id>& entity_selected, ImGuiWindowFlags window_flags) {
			if (*hierarchy_bool) {
				ImGui::Begin("Hierarchy", hierarchy_bool, window_flags);

				/**
				*	Game Object Create
				*/
				if (ImGui::Button("+ Create Game Object##CreateGameObject", { ImGui::GetContentRegionAvail().x, 0 }))
				{
					Engine::dreamECSGame->CreateEntity();
					

					//record the object state before change
					std::shared_ptr<ICommand> new_command = std::make_shared<ObjectAddState>();
					new_command->execute();
					Engine::UndoRedoManager::GetInstance().RecordState(new_command);
				}

				if (ImGui::BeginPopupContextWindow())
				{
					/**
					*	Game Object Delete
					*/
					if (ImGui::Button("Delete##DeleteGameObject", { ImGui::GetContentRegionAvail().x, 0 }))
					{
						//CallFuncForEach(entity_selected.begin(), entity_selected.end(), []() {});
						std::for_each(entity_selected.begin(), entity_selected.end(), [](std::pair<int, Engine::Entity_id> entity) { Engine::dreamECSGame->DestroyEntity(entity.second);  });
						entity_selected.clear();
					}

					/**
					*	Game Object Duplicate
					*/
					if (ImGui::Button("Duplicate##DuplicateGameObject", { ImGui::GetContentRegionAvail().x, 0 }))
					{
						//std::for_each(entity_selected.begin(), entity_selected.end(), [](std::pair<int, Engine::Entity_id> entity) { Engine::DreamECS::GetInstance().DuplicateEntityAsInstance(entity.second);  });
						Engine::dreamECSGame->DuplicateEntityAsInstance(GetTarget(entity_selected));
					}

					if (ImGui::Button("Parent##ParentGameObject", { ImGui::GetContentRegionAvail().x, 0 }))
					{
						//std::for_each(entity_selected.begin(), entity_selected.end(), [](std::pair<int, Engine::Entity_id> entity) { Engine::DreamECS::GetInstance().DuplicateEntityAsInstance(entity.second);  });
						Engine::Entity_id parent = GetTarget(entity_selected);
						for (const auto& [index, entity_id] : entity_selected) {
							if (parent == entity_id) continue;
							Engine::dreamECSGame->Parent(parent, entity_id);
						}
					}

					if (ImGui::Button("Unparent##UnparentGameObject", { ImGui::GetContentRegionAvail().x, 0 }))
					{
						for (const auto& [index, entity_id] : entity_selected) {
							Engine::dreamECSGame->Unparent(entity_id);
						}
					}

					ImGui::EndPopup();
				}

				/**
				*	Game Objects Listing
				*/

				//highlight when object is currently selected
				ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen
					| ImGuiTreeNodeFlags_OpenOnDoubleClick
					| ImGuiTreeNodeFlags_SpanAvailWidth;

				std::set<Engine::Entity_id> setOfUI;

				auto& entity_map = Engine::dreamECSGame->GetUsedConstEntityMap();
				for (auto& [id, entity] : entity_map)
				{
					//if (entity.parent != DEFAULT_ENTITY_ID) continue;
					bool selected = CheckIfExist(entity_selected, id);

					if (Engine::dreamECSGame->GetComponentPTR<Engine::UIComponent>(id) == nullptr) {
						//if (entity.child.empty()) {
						if (selected)
							ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 255, 0, 255));
						if (ImGui::Selectable(entity.name.c_str())) {
							ClickCheck(entity_selected, id);
						}
						if (selected)
							ImGui::PopStyleColor();
					}

					else {
						/*if (selected)
							ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 255, 0, 255));
						if (ImGui::CollapsingHeader(entity.name.c_str())) {
							if (selected)
								ImGui::PopStyleColor();
							for (const auto& entityChild : entity.child) {
								const auto& itr = entity_map.find(entityChild);
								if (itr == entity_map.end()) continue;

								selected = CheckIfExist(entity_selected, entityChild);
								if (selected)
									ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 255, 0, 255));
								if (ImGui::Selectable(itr->second.name.c_str())) {
									ClickCheck(entity_selected, entityChild);
								}
								if (selected)
									ImGui::PopStyleColor();
							}
						}*/
						setOfUI.emplace(id);
					}
				}

				if (ImGui::CollapsingHeader("Canvas")) {
					for (auto& id : setOfUI) {
						bool selected = CheckIfExist(entity_selected, id);

						if (selected)
							ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 255, 0, 255));

						const auto& itr = entity_map.find(id);
						if (itr == entity_map.end()) continue;
						if (ImGui::Selectable(itr->second.name.c_str())) {
							ClickCheck(entity_selected, id);
						}

						if (selected)
							ImGui::PopStyleColor();

					}
				}
			

				ImGui::End();
			}
		}
	}
}