/* Start Header**********************************************************************************/
/*
@file    Physics.cpp
@author  Ow Jian Wen	jianwen.o@digipen.edu			100%
@date    27/09/2021
\brief
This file contain the Physics definition


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Physics/Physics.hpp"

namespace Engine {
	namespace Physics {
		void ApplyLinearVelocity(Math::vec2& _position, float _angle, float _speed) {
			float radians = Math::radians(_angle + 90.f);
			_position += Math::vec2{ std::cos(radians), std::sin(radians) } *_speed;
		}
	}
}