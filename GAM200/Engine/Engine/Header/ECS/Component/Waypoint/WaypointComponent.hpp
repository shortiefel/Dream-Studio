/* Start Header**********************************************************************************/
/*
@file    WaypointComponent.hpp
@author  Ow Jian Wen		jianwen.o@digipen.edu	100%
@date    28/01/2022
\brief
#include "Engine/Header/ECS/Component/Waypoint/WaypointComponent.hpp"
This file contains the WaypointComponent declaration

The waypoints that are set will follow the rotation of the transform


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#pragma once

#include "Engine/Header/ECS/Component/IComponent.hpp"
#include "Engine/Header/Math/MathLib.hpp"

#include <list>

namespace Engine {
	struct WaypointComponent : public IComponent {
		//Inside of numOfWaypoint Eg. 3 4 5 3
		//The number states that the first 3 waypoint belongs to 1 group, next 4 to another, ...
		std::list<unsigned int> numOfWaypoint = std::list<unsigned int>{};
		//Stores the list of waypoints
		std::list<Math::vec2> listOfWaypoint = std::list<Math::vec2>{};

		int section = 0; //How many marker before switch between incoming and outgoing

		bool isActive = true;

		WaypointComponent(Entity_id _ID = DEFAULT_ENTITY_ID, std::list<unsigned int> _num = std::list<unsigned int>{},
			std::list<Math::vec2> _list = std::list<Math::vec2>{});
	};
}
