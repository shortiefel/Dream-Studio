/* Start Header**********************************************************************************/
/*
@file    Random.cpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    03/1/2021
\brief
#include "Engine/Header/Random/Random.hpp"
This file has the function definition for Random


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Random/Random.hpp"

#include <random>

namespace Engine {
	void Random::Range(int num1, int num2, int* num3) {
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> dist(num1, num2);
		*num3 = dist(rng);
	}
}