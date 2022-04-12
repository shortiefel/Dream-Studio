/* Start Header**********************************************************************************/
/*
@file    GUI_ClickCheck.cpp
@author  Ow Jian Wen	jianwen.o@digipen.edu		100%
@date    28/10/2021
\brief
#include "Editor/Header/GUI/GUI_ClickCheck.hpp"
This file has the function definition for GUI Click checking


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Editor/Header/GUI/GUI_ClickCheck.hpp"

#include "Engine/Header/Input/Input.hpp"
#include <iostream>

#define MAX_SELECTION 3
namespace Editor {
	namespace GUI_Windows {
		int order = 0;
		int selected = 0;

		void SelectedEntityCheck(std::map<int, Engine::Entity_id>& entity_selected) {
			auto& entityMap = Engine::dreamECSGame->GetUsedEntityMap();

			//Remove if entity is deleted
			for (auto& [index, entity_id] : entity_selected) {
				if (entity_id == DEFAULT_ENTITY_ID) continue;
				const auto& itr = entityMap.find(entity_id);
				if (itr == entityMap.end()) {
					entity_id = DEFAULT_ENTITY_ID;
				}
			}
		}

		Engine::Entity_id GetTarget(std::map<int, Engine::Entity_id>& entity_selected) {
			return entity_selected[selected];
		}

		void ClickCheck(std::map<int, Engine::Entity_id>& entity_selected, Engine::Entity_id _target) {
			if (Engine::Input::IsKeyHold(Engine::Input_KeyCode::Control)) {
				//for (auto& [id, entity_id] : entity_selected) {
				//	std::cout << entity_id;
				//	if (_target == entity_id) std::cout << " is selected ";
				//	std::cout << "\n";
				//}
				//std::cout <<  "\n";
				entity_selected[order] = _target;
				selected = order;
				order++;
				if (order >= MAX_SELECTION) order = 0;
			}
			else {
				entity_selected.clear();
				order = 0;
				selected = order;
				entity_selected[order] = _target;
				order++;
			}
		}

		bool CheckIfExist(std::map<int, Engine::Entity_id>& entity_selected, Engine::Entity_id _target) {
			for (const auto& [index, entity_id] : entity_selected) {
				if (entity_id == DEFAULT_ENTITY_ID) continue;
				if (entity_id == _target) return true;
			}
			return false;
		}
		
	}
}