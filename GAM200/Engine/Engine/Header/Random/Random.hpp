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

namespace Engine {
	class Random {
	public:
		static void Range(int num1, int num2, int* num3);
	};
}

#endif