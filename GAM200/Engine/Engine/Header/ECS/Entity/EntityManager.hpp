/* Start Header**********************************************************************************/
/*!
@file EntityManager.hpp
@authors	Ow Jian Wen			jianwen123321@hotmail.com
			Tan Wei Ling Felicia	weilingfelicia.tan@digipen.edu

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
		//EntityManager() //ctor
		//{
		//	Entity entity;

		//	for (entity = 0; entity < MAX_ENTITIES; ++entity)
		//	{
		//		EntityManager::AvailableEntities.push(entity); //adding entity
		//	}
		//}

		Entity CreateEntity()
		{
			//error checking
			LOG_ASSERT(AliveEntityCount < MAX_ENTITIES && "Too many entities");

			Entity ID;

			if (AvailableEntities.size()) {
				ID = AvailableEntities.front();
				AvailableEntities.pop();
			}

			else {
				ID = currentMaxId;
				++currentMaxId;
			}

			UsedEntities.insert(ID);
			++AliveEntityCount;

			return ID;
		}

		void DestroyEntity(Entity entity)
		{
#if NEW_ECS
			//error checking
			LOG_ASSERT(entity < MAX_ENTITIES && "Entities out of range");
			UsedEntities.erase(entity);
			//mSignatures[entity].reset();
			AvailableEntities.push(entity);
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
		inline const std::unordered_set<Entity>& GetUsedEntitySet() const {
			return UsedEntities;
		}

		inline void ResetEntityManager() {
			UsedEntities.clear();
			currentMaxId = 0;
			AvailableEntities = std::queue<Entity>();
		}


		std::unordered_set<Entity> UsedEntities{};
		uint32_t AliveEntityCount{}; // Total living entities
	private:
		std::queue<Entity> AvailableEntities{}; // Queue of unused entity IDs
#ifndef NEW_ECS
		std::array<Signature, MAX_ENTITIES> mSignatures{}; // Array of signatures for index to correspond to ID
#endif

		uint32_t currentMaxId = 0;
	};
}