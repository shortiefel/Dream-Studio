/* Start Header**********************************************************************************/
/*!
\file EntityManager.hpp
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


#include "Engine/Header/ECS/ECSGlobal.hpp"
#include <queue>
#include <array>

#include <unordered_set>

namespace Engine {
	class EntityManager
	{
	public:
		//EntityManager() //ctor
		//{
		//	Entity entity;

		//	for (entity = 0; entity < MAX_ENTITIES; ++entity)
		//	{
		//		EntityManager::AvailableEntities.push(entity); //adding entity
		//	}
		//}

		Entity CreateEntity(const char* _entityName = DEFAULT_ENTITY_NAME, bool _appendEntityId = false)
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

			Entity entity(entityId, _entityName, _appendEntityId);
			UsedEntities.push_back(entity);
			return entity;
		}

		void DestroyEntity(Entity entity)
		{
#if NEW_ECS
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
#else
			//error checking
			LOG_ASSERT(entity < MAX_ENTITIES && "Entities out of range");
			UsedEntities.erase(entity);
			mSignatures[entity].reset();
			AvailableEntities.push(entity);
			--AliveEntityCount;
#endif
		}
#ifndef NEW_ECS
		void SetSignature(Entity entity, Signature signature)
		{
			//error checking
			LOG_ASSERT(entity < MAX_ENTITIES && "Entities out of range");

			mSignatures[entity] = signature;
		}

		Signature GetSignature(Entity entity)
		{
			//error checking
			LOG_ASSERT(entity < MAX_ENTITIES && "Entities out of range");

			return mSignatures[entity];
		}
#endif
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
#ifndef NEW_ECS
		std::array<Signature, MAX_ENTITIES> mSignatures{}; // Array of signatures for index to correspond to ID
#endif

		uint32_t currentMaxId = 0;
	};
}