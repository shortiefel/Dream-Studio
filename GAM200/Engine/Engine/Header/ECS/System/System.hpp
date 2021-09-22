/* Start Header**********************************************************************************/
/*!
@file			System.hpp
@authors		Tan Wei Ling Felicia	weilingfelicia.tan@digipen.edu
		
@date 26/04/2021

@brief



Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#pragma once

#include "Engine/Header/ECS/ECSGlobal.hpp"
#include <set> //associative container that contains a sorted set of unique object of type Key

namespace Engine {
	class System
	{
	public:
#ifndef NEW_ECS
		std::set<Entity> mEntities;
#endif

		//virtual bool Create() = 0;
		virtual void Destroy() = 0;
	};
}

