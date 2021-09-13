/* Start Header**********************************************************************************/
/*!
\file Coordinator.hpp
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

This file contain the coordinator where it coordinates with the Entity, Component, System and Event
in a single space.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/


#ifndef COORDINATOR_H
#define COORDINATOR_H

#include "Engine/Header/ECS/Component/ComponentManager.hpp"
#include "Engine/Header/ECS/Entity/EntityManager.hpp"
#include "Engine/Header/ECS/System/SystemManager.hpp"
#include "Engine/Header/ECS/ECSGlobal.hpp"
#include <memory>

namespace Engine {
	class Coordinator
	{
	public:
		void Init()
		{
			//std::make_unique constructs the type T and wrap it in unique_ptr
			compManager = std::make_unique<ComponentManager>();
			entityManager = std::make_unique<EntityManager>();
			sysManager = std::make_unique<SystemManager>();
		}


		/**
		* Entity Manager
		* --> acts as coordinator when creating and destroying entity
		*/
		Entity createEntity()
		{
			return entityManager->CreateEntity();
		}

		void DuplicateEntity(Entity entFrom, Entity entTo) {
			compManager->DuplicateComponents(entFrom, entTo);
		}

		void destroyEntity(Entity entity)
		{
			entityManager->DestroyEntity(entity);
			compManager->DestroyEntity(entity);
#ifndef NEW_ECS
			sysManager->EntityDestroyed(entity);
#endif
		}

		inline const std::unordered_set<Entity>& GetUsedEntitySet() const {
			return entityManager->GetUsedEntitySet();
		}

		void ResetECS()
		{
			entityManager->ResetEntityManager();
		}

		/**
		* Component Manager
		* --> acts as coordinator when registering, adding, removing.
		* --> it will also have a getter for component and the type of component
		* that it is handling
		*/
		template<typename T>
		void RegisterComponent() {
			compManager->RegisterCom<T>();
		}

		template<typename T>
		void AddComponent(T com) {
#if NEW_ECS
			auto ptr = compManager->GetComTest<T>(com.GetEntityId());
			LOG_ASSERT(!ptr && "Unable add the same component for one entity");
			if (ptr) return;
			compManager->AddComponent<T>(com);
			//auto Signature = entityManager->GetSignature(entity); //unique signature key
			//Signature.set(compManager->GetterComType<T>(), true); //setting the unique signature key
			//entityManager->SetSignature(entity, Signature);

			//sysManager->EntitySignatureChanged(entity, Signature); //letting system manager know abt the change in signature on entity
#else
			auto ptr = compManager->GetComTest<T>(entity);
			LOG_ASSERT(!ptr && "Unable add the same component for one entity");
			if (ptr) return;
			compManager->AddComponent<T>(entity, com);
			auto Signature = entityManager->GetSignature(entity); //unique signature key
			Signature.set(compManager->GetterComType<T>(), true); //setting the unique signature key
			entityManager->SetSignature(entity, Signature);

			sysManager->EntitySignatureChanged(entity, Signature); //letting system manager know abt the change in signature on entity
#endif
		}

		template<typename T>
		void RemoveComponent(Entity entity)
		{
#if NEW_ECS
			auto ptr = compManager->GetComTest<T>(entity);
			LOG_ASSERT(ptr && "Unable remove an entity that does not exist");
			if (!ptr) return;
			compManager->RemoveCom<T>(entity);
			/*auto Signature = entityManager->GetSignature(entity);
			Signature.set(compManager->GetterComType<T>(), false);
			entityManager->SetSignature(entity, Signature);

			sysManager->EntitySignatureChanged(entity, Signature);*/
#else
			auto ptr = compManager->GetComTest<T>(entity);
			LOG_ASSERT(ptr && "Unable remove an entity that does not exist");
			if (!ptr) return;
			compManager->RemoveCom<T>(entity);
			auto Signature = entityManager->GetSignature(entity);
			Signature.set(compManager->GetterComType<T>(), false);
			entityManager->SetSignature(entity, Signature);

			sysManager->EntitySignatureChanged(entity, Signature);
#endif
		}

		template<typename T>
		T& GetCom(Entity entity)
		{
			return compManager->GetCom<T>(entity);
		}

		template<typename T>
		T* GetComTest(Entity entity)
		{
			return compManager->GetComTest<T>(entity);
		}

		//Check only (data is not given)
		template<typename T>
		bool HasComCheck(Entity entity)
		{
			T* com;
			return compManager->HasCom<T>(com, entity);
		}

		//Check and retrieve data
		template<typename T>
		bool HasCom(T*& com, Entity entity)
		{
			return compManager->HasCom<T>(com, entity);
		}

		template<typename T>
		ComponentType GetComType()
		{
			return compManager->GetterComType<T>();
		}

		template<typename T>
		std::array<T, MAX_ENTITIES>& GetComponentArrayData() {
			return compManager->GetComponentArrayData<T>();
		}

		/**
		* System Manager
		* --> acts as cooordinator for registering and setting of system signature
		*/
		template<typename T>
		std::shared_ptr<T> RegSystem()
		{
			return sysManager->SystemReg<T>();
		}

#ifndef NEW_ECS
		template<typename T>
		void setSystemSignature(Signature sign)
		{
			sysManager->SetSignature<T>(sign);
		}
#endif

		/**
		* Event Manager
		* --> acts as coordinator to listen, and send event
		*/


	private:
		//std::unique
		//Eliminates all except the first element from every consecutive group of equivalent elements from the range [first, last) 
		//and returns a past-the-end iterator for the new logical end of the range.
		std::unique_ptr<ComponentManager>compManager;
		std::unique_ptr<EntityManager>entityManager;
		std::unique_ptr<SystemManager>sysManager;

	};
}

#endif // !COORDINATOR_H




