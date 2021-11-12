
#include "Editor/Header/GUI/GUI_Windows/GUI_HierarchyWindow.hpp"

#include "Editor/Header/GUI/GUI_ClickCheck.hpp"
#include "Engine/Header/ECS/Factory.hpp"
#include "Engine/Header/Event/MouseEvent.hpp"

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
				if (ImGui::Button("+ Create Object##createObjectBtn", { ImGui::GetContentRegionAvail().x ,  0 }))
				{
					ImGui::OpenPopup("##createObjectpopup");
				}
				if (ImGui::BeginPopup("##createObjectpopup"))
				{
					/**
					*	New Game Object
					*/
					if (ImGui::Button("New Object", { ImGui::GetContentRegionAvail().x, 0 }))
					{
						Engine::dreamECSGame->CreateEntity();
					}

					/**
					*	Game Object Placeholder
					*/
					if (ImGui::Button("Create Square##PlaceholderSquare", { ImGui::GetContentRegionAvail().x, 0 }))
					{
						Engine::Factory::InstantiateSquare();
					}

					if (ImGui::Button("Create Circle##PlaceholderCircle", { ImGui::GetContentRegionAvail().x, 0 }))
					{
						Engine::Factory::InstantiateCircle();
					}

					ImGui::EndPopup();
				}

		
				/**
				*	Game Objects Listing
				*/

				//highlight when object is currently selected
				/*ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen
					| ImGuiTreeNodeFlags_OpenOnDoubleClick
					| ImGuiTreeNodeFlags_SpanAvailWidth;*/

				std::set<Engine::Entity_id> setOfUI;

				auto& entity_map = Engine::dreamECSGame->GetUsedConstEntityMap();


				for (auto& [id, entity] : entity_map)
				{
					bool selected = CheckIfExist(entity_selected, id);

					if (Engine::dreamECSGame->GetComponentPTR<Engine::UIComponent>(id) == nullptr) {
						//if (entity.child.empty()) {
						if (selected)
							ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 255, 0, 255));

						if (ImGui::Selectable(entity.name.c_str()))
						{
							ClickCheck(entity_selected, id);
			
						}
						ImGui::OpenPopupOnItemClick("##EntityPop", ImGuiPopupFlags_MouseButtonRight);
						if (selected)
							ImGui::PopStyleColor();

					}

					else
						setOfUI.emplace(id);


				}


				
				
				if (ImGui::BeginPopupContextItem("##EntityPop"))
				{
					/**
					*	Game Object Duplicate
					*/
					if (ImGui::Button("Duplicate##DuplicateGameObject", { ImGui::GetContentRegionAvail().x, 0 }))
					{
						//std::for_each(entity_selected.begin(), entity_selected.end(), [](std::pair<int, Engine::Entity_id> entity) { Engine::dreamECSGame->DuplicateEntityAsInstance(entity.second);  });
						Engine::dreamECSGame->DuplicateEntityAsInstance(GetTarget(entity_selected));
					}

					/**
					*	Parenting
					*/
					if (ImGui::Button("Parent##ParentGameObject", { ImGui::GetContentRegionAvail().x, 0 }))
					{
						Engine::Entity_id parent = GetTarget(entity_selected);
						for (const auto& [index, entity_id] : entity_selected) 
						{
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

					/**
					*	Game Object Delete
					*/
					if (ImGui::Button("Delete##DeleteGameObject", { ImGui::GetContentRegionAvail().x, 0 }))
					{
						if (entity_selected[0] != DEFAULT_ENTITY_ID) {
							//CallFuncForEach(entity_selected.begin(), entity_selected.end(), []() {});
							std::for_each(entity_selected.begin(), entity_selected.end(), [](std::pair<int, Engine::Entity_id> entity) { Engine::dreamECSGame->DestroyEntity(entity.second);  });
							entity_selected.clear();
						}
						//
						// 
						//Engine::DreamECS::GetInstance().DestroyEntity(entity_selected);
					}

					ImGui::EndPopup();
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

						ImGui::OpenPopupOnItemClick("##EntityPop", ImGuiPopupFlags_MouseButtonRight);

						if (selected)
							ImGui::PopStyleColor();

					}
				}

				ImGui::End();
			}
		}
	}
}