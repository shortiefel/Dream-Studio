/* Start Header**********************************************************************************/
/*!
\file EntityManager.hpp
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


			UsedEntities.emplace_back(ID);
			++AliveEntityCount;

			return ID;
		}

		void DestroyEntity(Entity entity)
		{
			//error checking
			LOG_ASSERT(entity < MAX_ENTITIES && "Entities out of range");

			mSignatures[entity].reset();
			AvailableEntities.push(entity);
			--AliveEntityCount;
		}

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

		inline const std::vector<Entity>& GetUsedEntityVector() const {
			return UsedEntities;
		}

		inline void ResetEntityManager()  {
			UsedEntities.clear();
			currentMaxId = 0;
		}


		std::vector<Entity> UsedEntities{};
		uint32_t AliveEntityCount{}; // Total living entities
	private:
		std::queue<Entity> AvailableEntities{}; // Queue of unused entity IDs
		std::array<Signature, MAX_ENTITIES> mSignatures{}; // Array of signatures for index to correspond to ID

		uint32_t currentMaxId = uint32_t{};
	};
}