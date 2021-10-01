/* Start Header**********************************************************************************/
/*
@file    debugdraw.hpp
@author  Chia Yi Da		chiayida98@gmail.com
@date    23/09/2021
\brief
This file contains the declaration of functions that allows users to 
draw debug lines for game objects

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef DEBUG_DRAW_H
#define DEBUG_DRAW_H

#include "Engine/Header/ECS/Component/Graphics/TransformComponent.hpp"
#include "Engine/Header/ECS/Component/Physics/ColliderComponent.hpp"

namespace Engine {
	namespace GraphicImplementation {
		// Draw collision outlines of object, red color
		void DebugDrawCollider(Entity const& entity, TransformComponent const& transform, const Math::mat3 camMatrix);

		// draw outlines of object (Different color)
	}
}


#endif // DEBUG_DRAW_H