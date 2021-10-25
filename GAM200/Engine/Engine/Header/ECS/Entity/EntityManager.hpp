/* Start Header**********************************************************************************/
/*!
@file EntityManager.hpp
@author  Tan Wei Ling Felicia	weilingfelicia.tan@digipen.edu
@date 26/04/2021
@brief
Entity Manager is in charge of assigning entity IDs and keeping records of which IDs are in use
and not.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#pragma once


#include "Engine/Header/ECS/ECSGlobal.hpp"
#include <queue>
#include <array>

#include <unordered_set>

namespace Engine {
	class EntityManager
	{
	public:

		Entity CreateEntity(const char* _entityName = DEFAULT_ENTITY_NAME, Entity_id _parent = MAX_ENTITIES + 1)
		{
			//error checking
			LOG_ASSERT(AliveEntityCount < MAX_ENTITIES && "Too many entities");

			Entity_id entityId;

			if (AvailableEntities.size()) {
				entityId = AvailableEntities.front();
				AvailableEntities.pop();
			}

			else {
				entityId = currentMaxId;
				++currentMaxId;
			}

			++AliveEntityCount;

			Entity entity(entityId, _entityName, _parent);
			UsedEntities.push_back(entity);
			return entity;
		}

		void DestroyEntity(Entity entity)
		{
			//error checking
			LOG_ASSERT(entity.id < MAX_ENTITIES && "Entities out of range");
			int index = 0;
			for (index = 0; index < UsedEntities.size(); index++) {
				if (UsedEntities[index].id == entity.id) {
					break;
				}
			}
			UsedEntities.erase(UsedEntities.begin() + index);
			//mSignatures[entity].reset();
			AvailableEntities.push(entity.id);
			--AliveEntityCount;

		}

		inline const std::vector<Entity>& GetUsedEntitySet() const {
			return UsedEntities;
		}

		inline void ResetEntityManager() {
			UsedEntities.clear();
			currentMaxId = 0;
			AvailableEntities = std::queue<Entity_id>();
		}


		std::vector<Entity> UsedEntities{};
		uint32_t AliveEntityCount{}; // Total living entities
	private:
		std::queue<Entity_id> AvailableEntities{}; // Queue of unused entity IDs

		uint32_t currentMaxId = 0;
	};
}