/* Start Header**********************************************************************************/
/*!
\file Global.hpp
\team name
\software name
\authors
NAME							EMAIL									ROLE
Tan Wei Ling Felicia			weilingfelicia.tan@digipen.edu			PRODUCER
Goh	See Yong Denise				g.seeyongdenise@digipen.edu
Ow Jian Wen						jianwen.o@digipen.edu					TECHINCAL DIRECTOR
Chia Yi Da						chiayida98@gmail.com
Margaret Teo Boon See			Teo.b@digipen.edu
Wang Ao							Ao.Wang@digipen.edu
Ng Jia Yi						Jiayi.ng@digipen.edu
\date 26/04/2021

\brief

Entity Manager is in charge of assigning entity IDs and keeping records of which IDs are in use
and not.


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#pragma once

//#include <iostream>
#include <bitset>
#include <cstdint>

//Check whether entity is in used
#define Entity_Check(entity)\
(entity > MAX_ENTITIES)

#define NEW_ECS 1

namespace Engine {
	//ECS Components 
	using Entity = std::uint32_t;
	const Entity MAX_ENTITIES = 10000;
	//Values is used to check whether entity is in used
	//instead of bit comparision
	const Entity DEFAULT_ENTITY = MAX_ENTITIES + 1;
	using ComponentType = std::uint8_t;
	const ComponentType MAX_COMPONENTS = 48;
	using Signature = std::bitset<MAX_COMPONENTS>;


}