/* Start Header**********************************************************************************/
/*
@file    Physics.hpp
@author  Ow Jian Wen	jianwen.o@digipen.edu		100%
@date    26/06/2021
\brief
This file contain the Physics declaration


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include "Engine/Header/Math/MathLib.hpp"

namespace Engine {
	namespace Physics {
		/*
		Moves entity in a constant speed in the direction of the entity up direction
		_position is the transform position to move
		_angle is the angle of transform (in degrees)
		_speed is value after dt is applied
		*/
		void ApplyLinearVelocity(Math::vec2& _position, float _angle, float _speed);

		//void ApplyForces(unsigned int entityId, float fixeddt);
	}

}

#endif