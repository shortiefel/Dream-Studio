/* Start Header**********************************************************************************/
/*!
\file System.hpp
\team name
\software name
\authors
NAME							EMAIL									ROLE
Tan Wei Ling Felicia			weilingfelicia.tan@digipen.edu			PRODUCER
Goh	See Yong Denise				2001220@sit.singaporetech.edu.sg
Ow Jian Wen						jianwen123321@hotmail.com				TECHINCAL DIRECTOR
Chia Yi Da						chiayida98@gmail.com
Margaret Teo Boon See			Teo.b@digipen.edu
Wang Ao							Ao.Wang@digipen.edu
Ng Jia Yi						Jiayi.ng@digipen.edu
\date 26/04/2021
\brief

This is to allow iteration in a list of entities with a certain signature of components

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
		//virtual void Destroy() = 0;
	};
}

