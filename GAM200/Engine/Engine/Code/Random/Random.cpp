/* Start Header**********************************************************************************/
/*
@file    Random.cpp
@author  Ow Jian Wen	jianwen.o@digipen.edu			100%
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

namespace Engine {
	std::mt19937 Random::s_RandomEngine;
	std::uniform_int_distribution<std::mt19937::result_type> Random::s_Distribution;

	void Random::Create() { 
		s_RandomEngine.seed(std::random_device()()); 
	}

	float Random::Float() { 
		return (float)s_Distribution(s_RandomEngine) / (float)std::numeric_limits<uint32_t>::max(); 
	}


	void Random::Range(int num1, int num2, int* num3) {
		if (num1 > num2) {
			int tem = num1;
			num1 = num2;
			num2 = tem;
		}
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> dist(num1, num2);
		*num3 = dist(rng);
	}
}