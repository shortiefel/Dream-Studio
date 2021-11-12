/* Start Header**********************************************************************************/
/*
@file    Ray.hpp
@author  Ow Jian Wen	jianwen.o@digipen.edu		100%
@date    15/10/2021
\brief
This file contain the Ray declaration


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef RAY_HPP
#define RAY_HPP

#include "Engine/Header/Math/MathLib.hpp"

#define RAY_LENGTH 10000.f

namespace Engine {
	struct Ray {
		Math::vec2 pos;
		Math::vec2 dir;
		float length;

		Ray(Math::vec2 _pos = Math::vec2{}, Math::vec2 _dir = Math::vec2{}, float _length = RAY_LENGTH) : pos{ _pos }, dir{ _dir }, length{ _length } {}
	};
}

#endif