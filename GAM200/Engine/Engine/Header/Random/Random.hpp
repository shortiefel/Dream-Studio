/* Start Header**********************************************************************************/
/*
@file    Random.hpp
@author  Ow Jian Wen	jianwen.o@digipen.edu		100%
@date    03/1/2021
\brief
#include "Engine/Header/Random/Random.hpp"
This file has the function declaration for Random


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <random>

namespace Engine {
	class Random {
	public:
		static void Create();
		static float Float();

		// param 1 - starting range, - param 2 - end range, param 3 - return value
		static void Range(int num1, int num2, int* num3);

	private:
		static std::mt19937 s_RandomEngine;
		static std::uniform_int_distribution<std::mt19937::result_type> s_Distribution;
	};
}

#endif