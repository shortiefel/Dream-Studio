/* Start Header**********************************************************************************/
/*
@file    Factory.hpp
@author  Chia Yi Da		chiayida98@gmail.com
@date    23/06/2021
@brief
This file contain declaraction of Factory class with it functions


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef FACTORY_HPP
#define FACTORY_HPP

#include "Engine/Header/Math/MathLib.hpp"

namespace Engine 
{
	class Factory 
	{
	public:
		static void Create();
		static void Destroy();
		static void InstantiateSquare(Math::vec2 pos = Math::vec2{ 0.f, 0.f }, Math::vec2 scale = Math::vec2{ 20.f, 20.f });
		static void InstantiateCircle(Math::vec2 pos = Math::vec2{ 0.f, 0.f }, Math::vec2 scale = Math::vec2{ 20.f, 20.f });
	};
}

#endif