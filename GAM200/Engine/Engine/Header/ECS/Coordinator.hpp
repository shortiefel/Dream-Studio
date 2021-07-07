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

#include "ECS/Component/ComponentManager.hpp"
#include "ECS/Entity/EntityManager.hpp"
#include "ECS/System/SystemManager.hpp"
#include "ECS/ECSGlobal.hpp"
#include <memory>

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

		void destroyEntity(Entity entity)
		{
			entityManager->DestroyEntity(entity);
			compManager->DestoryEntity(entity);
			sysManager->EntityDestroyed(entity);
		}

		/**
		* Component Manager
		* --> acts as coordinator when registering, adding, removing.
		* --> it will also have a getter for component and the type of component
		* that it is handling
		*/
		template<typename T>
		void RegisterComponent()
		{
			compManager->RegisterCom<T>();
		}

		template<typename T>
		void AddComponent(Entity entity, T com)
		{
			compManager->AddCom<T>(entity, com);
			auto Signature = entityManager->GetSignature(entity); //unique signature key
			Signature.set(compManager->GetterComType<T>(), true); //setting the unique signature key
			entityManager->SetSignature(entity, Signature);

			sysManager->EntitySignatureChanged(entity, Signature); //letting system manager know abt the change in signature on entity
		}

		template<typename T>
		void RemoveComponent(Entity entity)
		{
			compManager->RemoveCom<T>(entity);
			auto Signature = entityManager->GetSignature(entity);
			Signature.set(compManager->GetterComType<T>(), false);
			entityManager->SetSignature(entity, Signature);

			sysManager->EntitySignatureChanged(entity, Signature);
		}

		template<typename T>
		T& GetCom(Entity entity)
		{
			return compManager->GetCom<T>(entity);
		}

		template<typename T>
		ComponentType GetComType()
		{
			return compManager->GetterComType<T>();
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

		template<typename T>
		void setSystemSignature(Signature sign)
		{
			sysManager->SetSignature<T>(sign);
		}

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


#endif // !COORDINATOR_H




