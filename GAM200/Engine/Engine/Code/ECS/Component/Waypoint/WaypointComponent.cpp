/* Start Header**********************************************************************************/
/*
@file    WaypointComponent.cpp
@author  Ow Jian Wen		jianwen.o@digipen.edu	100%
@date    28/01/2022
\brief
This file contains the WaypointComponent definition


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Debug Tools/Logging.hpp"

#include "Engine/Header/ECS/Component/Waypoint/WaypointComponent.hpp"


namespace Engine {
	WaypointComponent::WaypointComponent(Entity_id _ID, std::list<unsigned int> _num, std::list<Math::vec2> _list) :
		IComponent{ _ID }, numOfWaypoint{_num }, listOfWaypoint{ _list } {}
}
