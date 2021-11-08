/* Start Header**********************************************************************************/
/*
@file    Forces.hpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    08/11/2021
@brief
#include "Engine/Header/Physics/Forces.hpp"
This file contain the Forces declaration


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef FORCES_H
#define FORCES_H

#include "Engine/Header/Math/MathLib.hpp"

namespace Engine {
	struct LinearForces {
		Math::vec2 direction = Math::vec2{};
		float magnitude = 0.f;
	};

	struct RotationForces {
		float torque = float{};
		int direction = int{};
	};
}

#endif