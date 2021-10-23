/* Start Header**********************************************************************************/
/*
@file    Picking2D.cpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    23/06/2021
@brief
#include "Engine/Header/Graphic/Picking2D.hpp"
This file include definition for picking checks


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Graphic/Picking2D.hpp"

#include "Engine/Header/Event/OverlapColliderEvent.hpp"
#include "Engine/Header/Event/EventDispatcher.hpp"

namespace Engine {
	namespace Graphic {
		std::set<Entity_id> overlapMap;

		void RecordMouseOverlap(Entity_id entity_id, bool type) {
			if (type) {
				const auto& iter = overlapMap.find(entity_id);
				if (iter != overlapMap.end()) {
					MouseOverlapColliderEvent event(entity_id, MonoFunctionType::MOUSE_OVER);
					EventDispatcher::SendEvent(event);
				}
				else {
					overlapMap.insert(entity_id);
					MouseOverlapColliderEvent event(entity_id, MonoFunctionType::MOUSE_ENTER);
					EventDispatcher::SendEvent(event);
				}
			}
			else {
				const auto& iter = overlapMap.find(entity_id);
				if (iter != overlapMap.end()) {
					overlapMap.erase(iter);
					MouseOverlapColliderEvent event(entity_id, MonoFunctionType::MOUSE_EXIT);
					EventDispatcher::SendEvent(event);
				}
			}
		}
	}
}