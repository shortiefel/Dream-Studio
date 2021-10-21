/* Start Header**********************************************************************************/
/*
@file    Picking2D.hpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    23/06/2021
@brief
#include "Engine/Header/Graphic/Picking2D.hpp"
This file include declaration for picking checks


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef PICKING_2D_H
#define PICKING_2D_H

#include "Engine/Header/Math/MathLib.hpp"
#include "Engine/Header/ECS/DreamECS.hpp"

namespace Engine {
	namespace Graphic {
		void PickingCheck(Engine::Entity& entity_selected, Math::vec3& mousePos, const Math::vec2& viewportSize, const Math::mat3& inverseCamMatrix);
	}
}

#endif