/* Start Header**********************************************************************************/
/*
@file    DreamECS.cpp
@author  Ow Jian Wen			jianwen.o@digipen.edu
		 Tan Wei Ling Felicia	weilingfelicia.tan@digipen.edu
@date    08/09/2021
\brief
This file is the wrapper file for ECS
-It is made such that in the future the ECS can be changed easily


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/ECS/DreamECS.hpp"
#include "Engine/Header/ECS/System/ScriptSystem.hpp"

#define DESTROY_ENTITY(entity)\
entityManager->DestroyEntity(entity);\
compManager->DestroyEntity(entity);
//systemManager->EntityDestroyed(entity);


namespace Engine {
	//Coordinator DreamECS::gCoordinator;
	//std::queue<Entity> DreamECS::destroyQueue;

	void DreamECS::Create()
	{
		//gCoordinator.Init();
		compManager = std::make_unique<ComponentManager>();
		entityManager = std::make_unique<EntityManager>();
		sysManager = std::make_unique<SystemManager>();
	}

	Entity DreamECS::CreateEntity()
	{
		//return gCoordinator.createEntity();
		return entityManager->CreateEntity();
	}

	void DreamECS::DuplicateEntityAsInstance(Entity entFrom) {
		Entity entTo = entityManager->CreateEntity();
		//gCoordinator.DuplicateEntityAsInstance(entFrom, entTo);
		compManager->DuplicateEntityAsInstance(entFrom, entTo);
	}

	void DreamECS::DestroyEntity(Entity entity)
	{
		destroyQueue.emplace(entity);
	}

	const std::unordered_set<Entity_id>& DreamECS::GetUsedEntitySet() {
		//return gCoordinator.GetUsedEntitySet();
		return entityManager->GetUsedEntitySet();
	}

	void DreamECS::ClearDestroyQueue() {
		//std::cout << gCoordinator.GetUsedEntitySet().size() << "\n";
		size_t num = destroyQueue.size();
		while (num > 0) {
			Entity& entity = destroyQueue.front();
			//gCoordinator.destroyEntity(entity);

			DESTROY_ENTITY(entity);
			
			destroyQueue.pop();
			--num;
		}
	}

	void DreamECS::ResetECS() {
		//std::unordered_set<Entity> listOfEntity = gCoordinator.GetUsedEntitySet();
		std::unordered_set<Entity_id> listOfEntity = entityManager->GetUsedEntitySet();
		for (auto& entity : listOfEntity) {
			//gCoordinator.destroyEntity(entity);

			DESTROY_ENTITY(entity);
		}

		//gCoordinator.ResetECS();
		entityManager->ResetEntityManager();
	}

}