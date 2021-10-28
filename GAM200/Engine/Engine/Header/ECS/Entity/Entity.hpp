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
#include <unordered_set>

namespace Engine {

	const std::uint32_t MAX_ENTITIES = 10000;
	using Entity_id = std::uint32_t;

	#define DEFAULT_ENTITY_NAME "Entity"
	#define DEFAULT_ENTITY_ID (Engine::MAX_ENTITIES + 1)

	struct Entity {
#if 1
		Entity_id id{};
		std::string name{};
		Entity_id parent{};
		std::unordered_set<Entity_id> child{};

		Entity(Entity_id _entityId = MAX_ENTITIES + 1, const char* _entityName = "Entity", Entity_id _parent = MAX_ENTITIES + 1) :
			id{ _entityId },
			name{ std::string {_entityName } },
			parent{ _parent } {}
#else
		Entity_id id{};
		std::string name{};
		Entity_id parent{};

		Entity(Entity_id _entityId = MAX_ENTITIES + 1, const char* _entityName = "Entity", Entity_id _parent = MAX_ENTITIES + 1, bool _appendEntityId = false) :
			id{ _entityId },
			name{ (_appendEntityId ? (std::string {_entityName } + std::to_string(_entityId)) : std::string {_entityName }) },
			parent{ _parent } {}
#endif
	};




}