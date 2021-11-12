/* Start Header**********************************************************************************/
/*!
@file EntityManager.hpp
@author  Tan Wei Ling Felicia	weilingfelicia.tan@digipen.edu	100%
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

#include <unordered_map>

namespace Engine {
	using EntityMapType = std::unordered_map<Entity_id, Entity>;
	class EntityManager
	{
	public:

		Entity& CreateEntity(const char* _entityName = DEFAULT_ENTITY_NAME, Entity_id _parent = MAX_ENTITIES + 1)
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
			//UsedEntities2.push_back(entity);
			usedEntities.emplace(entityId, entity);
			return usedEntities[entityId];
		}

		void DestroyEntity(Entity_id entity_id)
		{
			//error checking
			LOG_ASSERT(entity_id < MAX_ENTITIES && "Entities out of range");

			/*int index = 0;
			for (index = 0; index < UsedEntities2.size(); index++) {
				if (UsedEntities2[index].id == entity_id) {
					break;
				}
			}
			UsedEntities2.erase(UsedEntities2.begin() + index);*/


			const auto& itr = usedEntities.find(entity_id);
			if (itr != usedEntities.end()) {
				usedEntities.erase(entity_id);
			}
		
			//mSignatures[entity].reset();
			AvailableEntities.push(entity_id);
			--AliveEntityCount;
		}

		/*inline const std::vector<Entity>& GetUsedEntitySet() const {
			return UsedEntities2;
		}*/

		inline const EntityMapType& GetUsedConstEntityMap() const {
			return usedEntities;
		}

		inline EntityMapType& GetUsedEntityMap() {
			return usedEntities;
		}

		inline void ResetEntityManager() {
			//UsedEntities2.clear();
			usedEntities = EntityMapType{};
			currentMaxId = 0;
			AliveEntityCount = 0;
			AvailableEntities = std::queue<Entity_id>();
		}

		inline unsigned int GetUsedEntitySize() const {
			//std::cout << "Map Size: " << AliveEntityCount << "\n";
			return AliveEntityCount;
		}


	private:
		//std::vector<Entity> UsedEntities2{};
		EntityMapType usedEntities{};

		unsigned int AliveEntityCount{}; // Total living entities
		std::queue<Entity_id> AvailableEntities{}; // Queue of unused entity IDs

		uint32_t currentMaxId = 0;
	};
}