/* Start Header**********************************************************************************/
/*!
@file ECSGlobal.hpp
@author  Tan Wei Ling Felicia	weilingfelicia.tan@digipen.edu
@date 26/04/2021

@brief

Entity and component definition/names


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef ECS_GLOBAL
#define ECS_GLOBAL

//#include <iostream>
//#include <bitset>
#include <cstdint>
#include <string>

#include "Engine/Header/ECS/Entity/Entity.hpp"

//Check whether entity is in used
#define EntityId_Check(entity_id)\
(entity_id > Engine::MAX_ENTITIES)

namespace Engine {
	//ECS Components 
	//using Entity = std::uint32_t;

	//const Entity DEFAULT_ENTITY = MAX_ENTITIES + 1;
	#define DEFAULT_ENTITY Entity{}

	using ComponentType = std::uint8_t;
	const ComponentType MAX_COMPONENTS = 48;
	//using Signature = std::bitset<MAX_COMPONENTS>;
}

#endif