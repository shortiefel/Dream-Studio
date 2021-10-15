/* Start Header**********************************************************************************/
/*
@file    Ray.hpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
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

namespace Engine {
	struct Ray {
		Math::vec2 pos;
		Math::vec2 dir;

		Ray(Math::vec2 _pos = Math::vec2{}, Math::vec2 _dir = Math::vec2{}) : pos{ _pos }, dir{ _dir } {}
	};
}

#endif