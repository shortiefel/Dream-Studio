/* Start Header**********************************************************************************/
/*
@file    GUI_ClickCheck.hpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    28/10/2021
\brief
#include "Editor/Header/GUI/GUI_ClickCheck.hpp"
This file has the function declaration for GUI Click checking


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/


#ifndef CLICK_CHECK_HPP
#define CLICK_CHECK_HPP

#include "Engine/Header/ECS/DreamECS.hpp"
#include <forward_list>

namespace Editor {
	namespace GUI_Windows {
		template<typename Iterator, typename Func>
		void CallFuncForEach(Iterator& start, Iterator& end, Func func) {
			std::forward_list<Engine::Entity_id>::iterator itr = start;
			while (itr != end) {
				func(itr->second);
				itr++;
			}
		}

		//Check to see if Entity is deleted
		void SelectedEntityCheck(std::map<int, Engine::Entity_id>& entity_selected);
		//Get the target to show in inspector
		Engine::Entity_id GetTarget(std::map<int, Engine::Entity_id>& entity_selected);
		//Check for clicks before calling this
		void ClickCheck(std::map<int, Engine::Entity_id>& entity_selected, Engine::Entity_id _target);
		bool CheckIfExist(std::map<int, Engine::Entity_id>& entity_selected, Engine::Entity_id _target);
	}
}

#endif