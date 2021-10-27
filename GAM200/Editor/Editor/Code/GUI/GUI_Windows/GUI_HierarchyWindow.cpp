
#include "Editor/Header/GUI/GUI_Windows/GUI_HierarchyWindow.hpp"

namespace Editor {
	namespace GUI_Windows {
		void GUI_Hierarchy(bool* hierarchy_bool, Engine::Entity_id& entity_selected, ImGuiWindowFlags window_flags) {
			if (*hierarchy_bool) {
				ImGui::Begin("Hierarchy", hierarchy_bool, window_flags);

				/**
				*	Game Object Create
				*/
				if (ImGui::Button("Create Game Object##CreateGameObject", { ImGui::GetContentRegionAvail().x, 0 }))
				{
					Engine::DreamECS::GetInstance().CreateEntity();
				}

				if (ImGui::BeginPopupContextWindow())
				{
					/**
					*	Game Object Delete
					*/
					if (ImGui::Button("Delete##DeleteGameObject", { ImGui::GetContentRegionAvail().x, 0 }))
					{
						Engine::DreamECS::GetInstance().DestroyEntity(entity_selected);
					}

					/**
					*	Game Object Duplicate
					*/
					if (ImGui::Button("Duplicate##DuplicateGameObject", { ImGui::GetContentRegionAvail().x, 0 }))
					{
						Engine::DreamECS::GetInstance().DuplicateEntityAsInstance(entity_selected);
					}

					ImGui::EndPopup();
				}






				/**
				*	Game Objects Listing
				*/

				//Engine::Entity entity_selected = Engine::Entity{ 0 };
				/*std::vector entity_set = Engine::DreamECS::GetInstance().GetUsedEntitySet();

				std::vector entity_set = Engine::DreamECS::GetInstance().GetUsedEntitySet();*/

				//highlight when object is currently selected
				ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen
					| ImGuiTreeNodeFlags_OpenOnDoubleClick
					| ImGuiTreeNodeFlags_SpanAvailWidth;

				auto& entity_map = Engine::DreamECS::GetInstance().GetUsedEntityMap();
				for (auto& [id, entity] : entity_map)
				{
					if (ImGui::Selectable(entity.name.c_str()))
					{
						entity_selected = id;
					}
				}


				ImGui::End();
			}
		}
	}
}