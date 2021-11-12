/* Start Header**********************************************************************************/
/*!
@file ECSGlobal.hpp
@author  Tan Wei Ling Felicia	weilingfelicia.tan@digipen.edu
@date 26/04/2021

@brief

Entity struct


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/



#include <cstdint>
#include <string>
#include <set>

namespace Engine {

	const std::uint32_t MAX_ENTITIES = 10000;
	using Entity_id = std::uint32_t;

	#define DEFAULT_ENTITY_NAME "Entity"
	#define DEFAULT_ENTITY_ID (Engine::MAX_ENTITIES + 1)

	struct Entity {
		Entity_id id{};
		std::string name{};
		Entity_id parent{};
		std::set<Entity_id> child{};

		Entity(Entity_id _entityId = MAX_ENTITIES + 1, const char* _entityName = "Entity", Entity_id _parent = MAX_ENTITIES + 1) :
			id{ _entityId },
			name{ std::string {_entityName } },
			parent{ _parent } {}
	};




}